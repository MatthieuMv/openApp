/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ShuntingYard
*/

// std::regex
#include <regex>

#include <openApp/Core/Log.hpp>
#include <openApp/Language/ShuntingYard.hpp>
#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/Nodes.hpp>

static const std::regex NameMatch("([[:alpha:]][[:alnum:]]*)(.[[:alpha:]][[:alnum:]]*)*", std::regex::optimize);
static const std::regex ValueMatch("\".*\"|[[]|true|false|-?[[:digit:]]*[.]?[[:digit:]]+", std::regex::optimize);

void oA::Lang::ShuntingYard::ProcessString(Item &root, const String &name, const String &expr, Mode mode, const String &context, bool verbose, UInt tab)
{
    Lexer::TokenList tokens;
    Lexer::ProcessString(expr, tokens, context);

    ProcessTokenList(root, name, tokens, mode, context, verbose, tab);
}

void oA::Lang::ShuntingYard::ProcessTokenList(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context, bool verbose, UInt tab)
{
    if (tokens.empty())
        return;
    ShuntingYard(root, name, tokens, mode, context, verbose, tab).process();
}

oA::Lang::ShuntingYard::ShuntingYard(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context, bool verbose, UInt tab)
    :  _expr(std::make_unique<ExpressionGroupNode>()), _root(root), _tokens(tokens), _context(context), _name(name), _mode(mode), _tab(tab), _verbose(verbose)
{
    if (!_tokens.empty())
        _line = _tokens.front().second;
    if (_mode == Expression || _mode == Function)
        _target = _root.getPtr(_name);
    else
        _target = _root.findExpr(_name);
    if (!_target)
        throw AccessError("ShuntingYard", "Couldn't find target @" + _name + getErrorContext(_line));
}

void oA::Lang::ShuntingYard::process(void)
{
    auto it = _tokens.begin();

    _target->clearTree();
    collectGroup(it, *_expr, String());
    buildTarget();
    if (_verbose) {
        cout << _target->toString() << endl;
        _target->show(++_tab);
    }
}

void oA::Lang::ShuntingYard::processToken(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    if (IsOperator(it->first))
        return processOperator(it, root);
    else if (IsStatement(it->first))
        return processStatement(it, root);
    else if (isIncrementOperator(it->first))
        return processIncrementOperator(it);
    else if (std::regex_match(it->first, ValueMatch))
        return processValue(it);
    else if (std::regex_match(it->first, NameMatch))
        return processName(it);
    else
        throw LogicError("ShuntingYard", "Couldn't identify expression token @" + it->first + "@" + getErrorContext(it->second));
}

bool oA::Lang::ShuntingYard::isIncrementOperator(const oA::String &token)
{
    if (token.size() < 3)
        return false;
    else if (auto ch = token.front(); (ch == '+' || ch == '-') && ch == *++token.begin())
        return true;
    else if (auto ch = token.back(); (ch == '+' || ch == '-') && ch == *++token.rbegin())
        return true;
    return false;
}

oA::Lang::ASTNodePtr &oA::Lang::ShuntingYard::pushToOpStack(Operator type)
{
    _lastType = ASTNode::Operator;
    return _opStack.emplace_back(std::make_unique<OperatorNode>(type));
}

oA::Lang::ASTNodePtr &oA::Lang::ShuntingYard::pushToStack(ASTNodePtr &&ptr)
{
    _lastType = ptr->getType();
    return _stack.emplace_back(std::move(ptr));
}

void oA::Lang::ShuntingYard::processOperator(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    const auto &model = GetOperator(it->first);

    _lastOp = model.type;
    switch (model.type) {
    case End:
        buildStack(root);
        break;
    case LeftParenthese:
        pushToOpStack(LeftParenthese);
        break;
    case RightParenthese:
        popOpStack(LeftParenthese, it->second);
        break;
    case TernaryElse:
        break;
    case LeftBrace:
        collectGroup(++it, root.emplaceAs<GroupNode>(), "}");
        break;
    case Comma:
        buildStack(root.emplaceAs<GroupNode>());
        collectSingleGroup(it, *root.children.back());
        break;
    case Call:
        pushToStack(std::make_unique<OperatorNode>(Call));
        break;
    case LeftBracket:
        processValue(it);
        break;
    case Substraction:
        processSubstractionOperator(model);
        break;
    default:
        processOperatorLogic(model);
        pushToOpStack(model.type);
        break;
    }
}

void oA::Lang::ShuntingYard::processOperatorLogic(const OperatorModel &model)
{
    if (_opStack.empty())
        return;
    const auto *other = &GetOperator(dynamic_cast<OperatorNode &>(*_opStack.back()).op);
    while (model.precedence < other->precedence || (model.precedence == other->precedence && model.associativity == LeftToRight)) {
        _stack.emplace_back(std::move(_opStack.back()));
        _opStack.pop_back();
        if (_opStack.empty())
            break;
        other = &GetOperator(dynamic_cast<OperatorNode &>(*_opStack.back()).op);
    }
}

void oA::Lang::ShuntingYard::processSubstractionOperator(const OperatorModel &model)
{
    if (_lastType == ASTNode::Root || _lastType == ASTNode::Statement)
        _stack.emplace_back(std::make_unique<ValueNode>(0));
    if (_lastType == ASTNode::Operator) {
        if (_lastOp == Substraction) {
            dynamic_cast<OperatorNode &>(*_opStack.back()).op = Addition;
            _lastOp = Addition;
            return;
        } else
            _stack.emplace_back(std::make_unique<ValueNode>(0));
    }
    processOperatorLogic(model);
    pushToOpStack(Substraction);
}

void oA::Lang::ShuntingYard::processIncrementOperator(Lexer::TokenList::const_iterator &it)
{
    Operator op;
    String name;

    if (it->first.front() == '+' || it->first.front() == '-') {
        op = it->first.front() == '+' ? PrefixIncrement : PrefixDecrement;
        name = it->first.substr(2);
    } else {
        op = it->first.back() == '+' ? SufixIncrement : SufixDecrement;
        name = it->first.substr(0, it->first.length() - 2);
    }
    auto &node = pushToStack(std::make_unique<OperatorNode>(op));
    node->emplace(findReference(name, it->second));
    _lastOp = op;
}

void oA::Lang::ShuntingYard::processName(Lexer::TokenList::const_iterator &it)
{
    auto dot = it->first.find_last_of('.');

    if (dot != String::npos) {
        String last = it->first.substr(dot + 1);
        if (IsFunction(last))
            return processFunction(it, last, it->first.substr(0, dot));
    } else if (IsFunction(it->first))
        return processFunction(it);
    processReference(it);
}

void oA::Lang::ShuntingYard::processReference(Lexer::TokenList::const_iterator &it)
{
    auto node = findReference(it->first, it->second);

    if (_mode == Expression)
        _target->depends(dynamic_cast<ReferenceNode &>(*node).ptr);
    pushToStack(std::move(node));
    auto tmp = it;
    if (++tmp != _tokens.end() && tmp->first == "((")
        throw LogicError("ShuntingYard", "openApp doesn't support arguments for @property call@" + getErrorContext(tmp->second));
}

oA::Lang::ASTNodePtr oA::Lang::ShuntingYard::findReference(const String &name, Int line)
{
    auto &loc = locals();
    auto tmp = loc.find(name);

    if (tmp != loc.end())
        return ASTNodePtr(std::make_unique<LocalNode>(tmp->second));
    auto expr = _root.findExpr(name);
    if (!expr)
        throw AccessError("ShuntingYard", "Couldn't find reference @" + name + "@" + getErrorContext(line));
    return ASTNodePtr(std::make_unique<ReferenceNode>(std::move(expr)));
}

void oA::Lang::ShuntingYard::processFunction(Lexer::TokenList::const_iterator &it)
{
    const auto &model = GetFunction(it->first);

    processFunctionArguments(
        it,
        *pushToStack(std::make_unique<FunctionNode>(model.type)),
        model
    );
}

void oA::Lang::ShuntingYard::processFunction(Lexer::TokenList::const_iterator &it, const String &symbol, const String &object)
{
    const auto &model = GetFunction(symbol);
    auto &node = *pushToStack(std::make_unique<FunctionNode>(model.type));

    node.emplace(findReference(object, it->second));
    processFunctionArguments(
        it,
        node,
        model
    );
}

void oA::Lang::ShuntingYard::processFunctionArguments(Lexer::TokenList::const_iterator &it, ASTNode &root, const FunctionModel &model)
{
    auto line = it->second;

    if (++it == _tokens.end() || (it->first != "()" && it->first != "(("))
        throw LogicError("ShuntingYard", "Invalid use of reserved function keyword @" + GetFunctionSymbol(model.type) + "@" + getErrorContext(line));
    if (it->first == "()") {
        if (model.args > 0)
           throw LogicError("ShuntingYard", "Function @" + GetFunctionSymbol(model.type) + "@ requires " + ToString(model.args) + " arguments (actual: 0)" + getErrorContext(line));
        return;
    }
    peekFunctionArguments(++it, root);
    if (model.args != -1 && model.args != static_cast<Int>(root.children.size()))
           throw LogicError("ShuntingYard", "Function @" + GetFunctionSymbol(model.type) + "@ requires " + ToString(model.args) + " arguments (actual: " + ToString(root.children.size()) + ")" + getErrorContext(line));
}

void oA::Lang::ShuntingYard::peekFunctionArguments(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    Vector<ASTNodePtr> stack, opStack;
    auto line = it->second;
    auto opened = 1;

    _stack.swap(stack);
    _opStack.swap(opStack);
    for (; it != _tokens.end(); ++it) {
        if (it->first == "((")
            ++opened;
        else if (it->first == "))")
            --opened;
        if (!opened)
            break;
        else if (it->first == ",")
            buildStack(root);
        else
            processToken(it, root);
    }
    if (opened)
        throw LogicError("ShuntingYard", "Invalid function call @arguments@" + getErrorContext(line));
    buildStack(root);
    _stack.swap(stack);
    _opStack.swap(opStack);
}

void oA::Lang::ShuntingYard::processValue(Lexer::TokenList::const_iterator &it)
{
    auto &node = dynamic_cast<ValueNode &>(*pushToStack(std::make_unique<ValueNode>()));

    parseValue(it, node.value);
}

void oA::Lang::ShuntingYard::parseValue(Lexer::TokenList::const_iterator &it, Var &var)
{
    switch (it->first.front()) {
    case 't':
        var = true;
        break;
    case 'f':
        var = false;
        break;
    case '"':
        var = it->first.substr(1, it->first.length() - 2);
        break;
    case '[':
        parseContainerValue(++it, var);
        break;
    default:
        if (!it->first.isNumber())
            throw LogicError("ShuntingYard", "Token @" + it->first + "@ is not a value" + getErrorContext(it->second));
        var = it->first.toFloat();
        break;
    }
}

void oA::Lang::ShuntingYard::parseValue(const String &value, Var &var, Int line)
{
    if (value.front() == '"') {
        var = value.substr(1, value.length() - 2);
        return;
    } else if (!value.isNumber())
        throw LogicError("ShuntingYard", "Token @" + value + "@ is not a value" + getErrorContext(line));
    var = value.toFloat();
}

void oA::Lang::ShuntingYard::parseContainerValue(Lexer::TokenList::const_iterator &it, Var &var)
{
    auto line = it->second;
    var = Container();

    for (; it != _tokens.end() && it->first != "]"; ++it) {
        if (!std::regex_match(it->first, ValueMatch))
            throw LogicError("SuntingYard", "Invalid container declaration token @" + it->first + "@" + getErrorContext(line));
        Var value;
        parseValue(it, value);
        var.push(std::move(value));
        if (++it == _tokens.end())
            throw LogicError("SuntingYard", "Invalid container declaration token @" + it->first + "@" + getErrorContext(line));
        else if (it->first == "]")
            break;
        else if (it->first != ",")
            throw LogicError("SuntingYard", "Invalid container declaration token @" + it->first + "@, excpected @,@" + getErrorContext(line));
    }
}

void oA::Lang::ShuntingYard::processStatement(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    const auto &statement = GetStatement(it->first);

    switch (statement.type) {
    case If:
        return parseIf(it, root);
    case Else:
        return parseElse(it, root);
    case Switch:
        return parseSwitch(it, root);
    case Case:
        return parseCase(it, root);
    case Default:
        return parseDefault(it, root);
    case While:
        return parseWhile(it, root);
    case For:
        return parseFor(it, root);
    case Break:
        return parseBreak(it);
    case Return:
        return parseReturn(it);
    case Variable:
        return parseVariable(it, root);
    case StaticVariable:
        return parseStaticVariable(it);
    }
}

void oA::Lang::ShuntingYard::parseIf(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &node = root.emplaceAs<StatementNode>(If);

    ++_state.inCondition;
    if (++it == _tokens.end() || it->first != "(")
        throw LogicError("ShuntingYard", "Invalid @if@ statement" + getErrorContext(line));
    collectGroup(++it, node.emplaceAs<GroupNode>(), ")");
    collectExpressionGroup(++it, node);
    if (it != _tokens.end() && ++it != _tokens.end() && it->first == "else")
        parseElse(it, node);
    else
        --it;
    --_state.inCondition;
}

void oA::Lang::ShuntingYard::parseElse(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    if (_state.inCondition <= 0)
        throw LogicError("ShuntingYard", "Invalid @else@ statement" + getErrorContext(line));
    if (++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @else@ statement" + getErrorContext(line));
    if (it->first == "if")
        parseIf(it, root.emplaceAs<GroupNode>());
    else
        collectExpressionGroup(it, root);
}

void oA::Lang::ShuntingYard::parseSwitch(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &node = root.emplaceAs<StatementNode>(Switch);

    ++_state.inSwitch;
    if (++it == _tokens.end() || it->first != "(")
        throw LogicError("ShuntingYard", "Invalid @switch@ statement" + getErrorContext(line));
    collectGroup(++it, node.emplaceAs<GroupNode>(), ")");
    node.emplaceAs<GroupNode>();
    if (++it == _tokens.end() || it->first != "{" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @switch@ statement" + getErrorContext(line));
    while (it != _tokens.end() && it->first != "}") {
        if (it->first == "case")
            parseCase(it, node);
        else if (it->first == "default")
            parseDefault(it, node);
        else
            throw LogicError("ShuntingYard", "Invalid @switch@ statement" + getErrorContext(line));
    }
    --_state.inSwitch;
}

static const oA::Vector<oA::String> CaseEnds = {
    "case", "default", "}"
};

void oA::Lang::ShuntingYard::parseCase(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &caseNode = *root.children[1];

    if (_state.inSwitch <= 0 || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid case statement" + getErrorContext(line));
    parseCaseName(it, caseNode);
    collectGroup(it, caseNode.emplaceAs<GroupNode>(), CaseEnds);
}

void oA::Lang::ShuntingYard::parseCaseName(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    if (std::regex_match(it->first, ValueMatch))
        parseValue(it, root.emplaceAs<ValueNode>().value);
    else if (std::regex_match(it->first, NameMatch))
        root.emplace(findReference(it->first, it->second));
    else
        throw LogicError("ShuntingYard", "Invalid @case@ statement" + getErrorContext(line));
    if (++it == _tokens.end() || it->first != ":" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @case@ statement" + getErrorContext(line));
}

void oA::Lang::ShuntingYard::parseDefault(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    if (_state.inSwitch <= 0 || ++it == _tokens.end() || it->first != ":" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @default@ statement" + getErrorContext(line));
    else if (root.children.size() != 2)
        throw LogicError("ShuntingYard", "Default case already declared" + getErrorContext(line));
    collectGroup(it, root.emplaceAs<GroupNode>(), CaseEnds);
}

void oA::Lang::ShuntingYard::parseWhile(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &node = root.emplaceAs<StatementNode>(While);

    ++_state.inLoop;
    if (++it == _tokens.end() || it->first != "(")
        throw LogicError("ShuntingYard", "Invalid @while@ statement" + getErrorContext(line));
    collectGroup(++it, node.emplaceAs<GroupNode>(), ")");
    if (++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @while@ statement" + getErrorContext(line));
    collectExpressionGroup(it, node);
    --_state.inLoop;
}

void oA::Lang::ShuntingYard::parseFor(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &node = root.emplaceAs<StatementNode>(For);

    ++_state.inLoop;
    if (++it == _tokens.end() || it->first != "(")
        throw LogicError("ShuntingYard", "Invalid @for@ statement" + getErrorContext(line));
    collectGroup(++it, node.emplaceAs<GroupNode>(), ";");
    collectGroup(it, node.emplaceAs<GroupNode>(), ";");
    collectGroup(it, node.emplaceAs<GroupNode>(), ")");
    if (++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @for@ statement" + getErrorContext(line));
    collectExpressionGroup(it, node);
    --_state.inLoop;
}

void oA::Lang::ShuntingYard::parseBreak(Lexer::TokenList::const_iterator &it)
{
    if (_state.inLoop <= 0 && _state.inSwitch <= 0)
        throw LogicError("ShuntingYard", "Invalid @break@ statement" + getErrorContext(it->second));
    _stack.emplace_back(std::make_unique<StatementNode>(Break));
}

void oA::Lang::ShuntingYard::parseReturn(Lexer::TokenList::const_iterator &it)
{
    auto line = it->second;
    auto &node = *_stack.emplace_back(std::make_unique<StatementNode>(Return));

    if (++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @return@ statement" + getErrorContext(line));
    collectGroup(it, node);
}

void oA::Lang::ShuntingYard::parseVariable(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    if (++it == _tokens.end() || !std::regex_match(it->first, NameMatch))
        throw LogicError("ShuntingYard", "Invalid @local variable@ declaration" + getErrorContext(it->second));
    auto &var = locals()[it->first] = 0;
    if (++it != _tokens.end() && it->first == "=") {
        root.emplaceAs<OperatorNode>(Assign);
        parseValue(it, var);
    }
    if (it == _tokens.end() || it->first != ";")
        throw LogicError("ShuntingYard", "Excepted end of declaration token @;@" + getErrorContext(line));
}

void oA::Lang::ShuntingYard::parseStaticVariable(Lexer::TokenList::const_iterator &it)
{
    auto line = it->second;

    if (++it == _tokens.end() || it->first != "var" || ++it == _tokens.end() || !std::regex_match(it->first, NameMatch))
        throw LogicError("ShuntingYard", "Invalid @local variable@ declaration" + getErrorContext(it->second));
    auto &var = locals()[it->first] = 0;
	if (++it != _tokens.end() && it->first == "=") {
		parseValue(++it, var);
		++it;
	}
    if (it == _tokens.end() || it->first != ";")
        throw LogicError("ShuntingYard", "Excepted end of declaration token @;@" + getErrorContext(line));
}

void oA::Lang::ShuntingYard::collectExpressionGroup(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    if (it->first == "{")
        collectGroup(++it, root.emplaceAs<GroupNode>(), "}");
    else {
        collectGroup(it, root.emplaceAs<GroupNode>());
        --it;
    }
}

void oA::Lang::ShuntingYard::collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    for (auto old = it->second; it != _tokens.end() && old == it->second; ++it) {
        processToken(it, root);
    }
    buildStack(root);
}

void oA::Lang::ShuntingYard::collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root, const String &end)
{
    auto firstLine = it->second;

    for (auto line = it->second; it != _tokens.end() && it->first != end; ++it) {
        if (line != it->second) {
            auto tmp = it;
            --tmp;
            if (tmp->first != "\\" && tmp->first != ";")
                buildStack(root);
            line = it->second;
        }
        processToken(it, root);
    }
    if (!end.empty() && it == _tokens.end())
        throw LogicError("ShuntingYard", "Excepted token @" + end + "@ in group" + getErrorContext(firstLine));
    buildStack(root);
}

void oA::Lang::ShuntingYard::collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root, const Vector<String> &ends)
{
    auto firstLine = it->second;

    for (auto line = it->second; it != _tokens.end(); ++it) {
        if (ends.findIf([&it](const auto &end) { return it->first == end; }) != ends.end())
            break;
        if (line != it->second) {
            auto tmp = it;
            --tmp;
            if (tmp->first != "\\" && tmp->first != ";")
                buildStack(root);
            line = it->second;
        }
        processToken(it, root);
    }
    if (it == _tokens.end())
        throw LogicError("ShuntingYard", "Unexpected end of group" + getErrorContext(firstLine));
    buildStack(root);
}

void oA::Lang::ShuntingYard::collectSingleGroup(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto old = it->second;

    for (auto line = it->second; it != _tokens.end() && old == line && it->first != ";"; line = (++it)->second)
        processToken(it, root);
    buildStack(root);
}

void oA::Lang::ShuntingYard::buildStack(ASTNode &root)
{
    popOpStack();
    if (_stack.empty())
        return;
    for (auto it = _stack.begin(); it != _stack.end(); ++it) {
        switch ((*it)->getType()) {
        case ASTNode::Operator:
            buildOperator(it);
            break;
        case ASTNode::Local:
        case ASTNode::Reference:
        case ASTNode::Value:
        case ASTNode::Statement:
        case ASTNode::Function:
            break;
        default:
            throw LogicError("ShuntingYard", "Can't build invalid node" + getErrorContext(_line));
        }
    }
    if (_stack.size() != 1)
        throw LogicError("ShuntingYard", "Invalid expression" + getErrorContext(_line));
    root.emplace(std::move(_stack.front()));
    _stack.clear();
}

void oA::Lang::ShuntingYard::buildOperator(Vector<ASTNodePtr>::iterator &it)
{
    auto &node = **it;
    const auto &model = GetOperator(dynamic_cast<OperatorNode &>(node).op);

    if ((*it)->children.empty() && !peekStackArguments(it, node, model.args)) {
        _stack.apply([](const auto &elem) { ASTNode::ShowTree(*elem); });
        throw LogicError("ShuntingYard", "Not enough arguments to process operator @" + GetOperatorSymbol(model.type) + "@" + getErrorContext(_line));
    }
    if (model.type == Call && node.children[0]->getType() != ASTNode::Reference) {
        ASTNode::ShowTree(node);
        throw LogicError("ShuntingYard", "Invalid use of @call@ operator" + getErrorContext(_line));
    }
}

bool oA::Lang::ShuntingYard::peekStackArguments(Vector<ASTNodePtr>::iterator &it, ASTNode &target, UInt args) noexcept
{
    auto i = args;

    for (; i > 0 && it != _stack.begin(); --i)
        --it;
    if (i)
        return false;
    for (; args > 0; --args) {
        target.children.insert(target.children.begin() + i++, std::move(*it));
        it = _stack.erase(it);
    }
    return true;
}

void oA::Lang::ShuntingYard::popOpStack(void) noexcept
{
    while (!_opStack.empty()) {
        _stack.emplace_back(std::move(_opStack.back()));
        _opStack.pop_back();
    }
}

void oA::Lang::ShuntingYard::popOpStack(Operator end, Int line)
{
    while (!_opStack.empty()) {
        auto &op = dynamic_cast<OperatorNode &>(*_opStack.back());
        if (op.op != end) {
            _stack.emplace_back(std::move(_opStack.back()));
            _opStack.pop_back();
            continue;
        }
        _opStack.pop_back();
        return;
    }
    throw LogicError("ShuntingYard", "Excepted operator @" + GetOperatorSymbol(end) + "@" + getErrorContext(line));
}

void oA::Lang::ShuntingYard::buildTarget(void)
{
    if (_mode == Event) {
        oA::PropertyPtr property(std::make_shared<Property>());
        property->setTree(std::move(_expr));
        _target->connectEvent(std::move(property));
        return;
    }
    _target->setTree(std::move(_expr));
    if (_mode == Expression)
        _target->compute();
}
