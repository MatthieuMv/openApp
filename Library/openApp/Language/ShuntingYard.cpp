/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ShuntingYard
*/

// std::regex
#include <regex>

#include <openApp/Language/ShuntingYard.hpp>
#include <openApp/Language/Lexer.hpp>
#include <openApp/Language/Nodes.hpp>
#include <openApp/Core/Log.hpp>

static const std::regex ReferenceMatch("[[:alpha:]][[:alnum:]]*", std::regex::optimize);
static const std::regex ValueMatch("\".*\"|[[]|true|false|-?[[:digit:]]*[.]?[[:digit:]]+", std::regex::optimize);
static const std::regex IncrementOperatorMatch("([+][+][[:alpha:]][[:alnum:]]*)|(--[[:alpha:]][[:alnum:]]*)|([[:alpha:]][[:alnum:]]*[+][+])|([[:alpha:]][[:alnum:]]*--)", std::regex::optimize);

void oA::Lang::ShuntingYard::ProcessString(Item &root, const String &name, const String &expr, Mode mode, const String &context)
{
    Lexer::TokenList tokens;
    Lexer::ProcessString(expr, tokens, context);

    ProcessTokenList(root, name, tokens, mode, context);
}

void oA::Lang::ShuntingYard::ProcessTokenList(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context)
{
    if (tokens.empty())
        return;
    ShuntingYard(root, name, tokens, mode, context).process();
}

oA::Lang::ShuntingYard::ShuntingYard(Item &root, const String &name, const Lexer::TokenList &tokens, Mode mode, const String &context)
    :  _expr(std::make_unique<ExpressionGroupNode>()), _root(root), _tokens(tokens), _context(context), _name(name), _mode(mode)
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
    for (auto it = _tokens.begin(); it != _tokens.end(); ++it)
        processToken(it, *_expr);
    buildStack(*_expr);
    buildTarget();
}

void oA::Lang::ShuntingYard::processToken(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    if (IsOperator(it->first))
        processOperator(it, root);
    else if (IsStatement(it->first))
        processStatement(it, root);
    else if (std::regex_match(it->first, IncrementOperatorMatch))
        processIncrementOperator(it);
    else if (std::regex_match(it->first, ReferenceMatch))
        processReference(it);
    else if (std::regex_match(it->first, ValueMatch))
        processValue(it);
    else
        throw LogicError("ShuntingYard", "Couldn't indentify expression token @" + it->first + "@" + getErrorContext(it->second));
}

void oA::Lang::ShuntingYard::processOperator(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    const auto &model = GetOperator(it->first);

    switch (model.type) {
    case End:
        buildStack(root);
        break;
    case LeftParenthese:
        _opStack.emplace_back(std::make_unique<OperatorNode>(LeftParenthese));
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
    default:
        processOperatorLogic(model);
        _opStack.emplace_back(std::make_unique<OperatorNode>(model.type));
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
    auto &node = _stack.emplace_back(std::make_unique<OperatorNode>(op));
    node->emplace(findReference(name, it->second));
}

void oA::Lang::ShuntingYard::processReference(Lexer::TokenList::const_iterator &it)
{
    auto node = findReference(it->first, it->second);

    if (_mode == Expression)
        _target->depends(*dynamic_cast<ReferenceNode &>(*node).ptr);
    _stack.emplace_back(std::move(node));
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

void oA::Lang::ShuntingYard::processValue(Lexer::TokenList::const_iterator &it)
{
    auto &node = dynamic_cast<ValueNode &>(*_stack.emplace_back(std::make_unique<ValueNode>()));

    parseValue(it, node.value);
}

void oA::Lang::ShuntingYard::parseValue(Lexer::TokenList::const_iterator &it, Var &var)
{
    switch (it->first.front()) {
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
    auto &target = var.getAs<Container>();

    for (; it != _tokens.end() && it->first != "}"; ++it) {
        if (!std::regex_match(it->first, ValueMatch))
            throw LogicError("SuntingYard", "Invalid container declaration token @" + it->first + "@" + getErrorContext(line));
        parseValue(it, target.emplace_back());
        if (++it == _tokens.end() || (it->first != "," && it->first != "]"))
            throw LogicError("SuntingYard", "Invalid container declaration token @" + it->first + "@" + getErrorContext(line));
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
    if (++it == _tokens.end() || it->first != "(" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @if@ statement" + getErrorContext(line));
    collectGroup(it, node.emplaceAs<GroupNode>(), ")");
    if (++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @if@ statement" + getErrorContext(line));
    collectExpressionGroup(it, node);
    if (it != _tokens.end() && ++it != _tokens.end() && it->first == "else")
        parseElse(it, node);
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
        collectExpressionGroup(it, root.emplaceAs<GroupNode>());
}

void oA::Lang::ShuntingYard::parseSwitch(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &node = root.emplaceAs<StatementNode>(Switch);

    ++_state.inSwitch;
    if (++it == _tokens.end() || it->first != "(" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @switch@ statement" + getErrorContext(line));
    collectGroup(it, node.emplaceAs<GroupNode>(), ")");
    if (++it == _tokens.end() || it->first != "{" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @switch@ statement" + getErrorContext(line));
    collectGroup(it, node, "}");
    --_state.inSwitch;
}

void oA::Lang::ShuntingYard::parseCase(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    parseCaseName(it, root);
    for (auto &group = root.emplaceAs<GroupNode>(); it != _tokens.end() && it->first != "case" && it->first != "default" && it->first != "}"; ++it)
        processToken(it, group);
    buildStack(*root.children.back());
    if (it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @case@ statement" + getErrorContext(line));
    if (it->first == "case")
        parseCase(it, root);
    else if (it->first == "default")
        parseDefault(it, root);
    else if (it->first == "}")
        --it;
}

void oA::Lang::ShuntingYard::parseCaseName(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    if (_state.inSwitch <= 0 || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @case@ statement" + getErrorContext(line));
    if (std::regex_match(it->first, ValueMatch))
        parseValue(it, root.emplaceAs<ValueNode>().value);
    else if (std::regex_match(it->first, ReferenceMatch))
        root.emplace(findReference(it->first, it->second));
    else
        throw LogicError("ShuntingYard", "Invalid @case@ statement" + getErrorContext(line));
    if (++it == _tokens.end() || it->first != ":")
        throw LogicError("ShuntingYard", "Invalid @case@ statement" + getErrorContext(line));
    ++it;
}

void oA::Lang::ShuntingYard::parseDefault(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;

    if (++it == _tokens.end() || it->first != ":" || ++it == _tokens.end())
        throw LogicError("ShuntingYard", "Invalid @default@ statement" + getErrorContext(line));
    for (auto &group = root.emplaceAs<GroupNode>(); it != _tokens.end() && it->first != "case" && it->first != "default" && it->first != "}"; ++it)
        processToken(it, group);
    if (it->first == "}")
        --it;
    buildStack(*root.children.back());
}

void oA::Lang::ShuntingYard::parseWhile(Lexer::TokenList::const_iterator &it, ASTNode &root)
{
    auto line = it->second;
    auto &node = root.emplaceAs<StatementNode>(While);

    ++_state.inLoop;
    if (++it == _tokens.end() || it->first != "(")
        throw LogicError("ShuntingYard", "Invalid @while@ statement" + getErrorContext(line));
    collectGroup(it, node.emplaceAs<GroupNode>(), ")");
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

    if (++it == _tokens.end() || !std::regex_match(it->first, ReferenceMatch))
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

    if (++it == _tokens.end() || it->first != "var" || ++it == _tokens.end() || !std::regex_match(it->first, ReferenceMatch))
        throw LogicError("ShuntingYard", "Invalid @local variable@ declaration" + getErrorContext(it->second));
    auto &var = locals()[it->first] = 0;
    if (++it != _tokens.end() && it->first == "=")
        parseValue(it, var);
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
    auto old = it->second;

    for (auto line = it->second; it != _tokens.end() && old == line; line = (++it)->second)
        processToken(it, root);
    buildStack(root);
}

void oA::Lang::ShuntingYard::collectGroup(Lexer::TokenList::const_iterator &it, ASTNode &root, const String &end)
{
    auto line = it->second;

    for (; it != _tokens.end() && it->first != end; ++it)
        processToken(it, root);
    if (it == _tokens.end())
        throw LogicError("ShuntingYard", "Excepted token @" + end + "@ in group" + getErrorContext(line));
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
            break;
        default:
            throw LogicError("ShuntingYard", "Can't build invalid node" + getErrorContext(_line));
        }
    }
    if (_stack.size() != 1) {
        _stack.apply([](const auto &node) { ASTNode::ShowTree(*node, 1); });
        throw LogicError("ShuntingYard", "Invalid expression" + getErrorContext(_line));
    }
    root.emplace(std::move(_stack.front()));
    _stack.clear();
}

void oA::Lang::ShuntingYard::buildOperator(Vector<ASTNodePtr>::iterator &it)
{
    static const auto hasVarReference = [](const ASTNode &node) {
        return node.children[0]->getType() == ASTNode::Reference || node.children[0]->getType() == ASTNode::Local
                || (node.children[0]->getType() == ASTNode::Operator && dynamic_cast<const OperatorNode &>(node).op != At);
    };
    const auto &model = GetOperator(dynamic_cast<OperatorNode &>(**it).op);

    if ((*it)->children.empty() && !peekStackArguments(it, **it, model.args))
        throw LogicError("ShuntingYard", "Not enough arguments to process operator @" + GetOperatorSymbol(model.type) + "@" + getErrorContext(_line));
    switch (model.type) {
    case Assign:
    case AdditionAssign:
    case SubstractionAssign:
    case MultiplicationAssign:
    case DivisionAssign:
    case ModuloAssign:
    case PrefixIncrement:
    case PrefixDecrement:
    case SufixIncrement:
    case SufixDecrement:
        if (!hasVarReference(**it))
            throw LogicError("ShuntingYard", "An assignment can't have a @non-reference type@ as left argument" + getErrorContext(_line));
        break;
    case At:
        if (!hasVarReference(**it))
            throw LogicError("ShuntingYard", "Container access can't have a @non-reference type@ as left argument" + getErrorContext(_line));
        break;
    case Call:
        if ((*it)->children[0]->getType() != ASTNode::Reference)
            throw LogicError("ShuntingYard", "A call can't have a @non-reference type@ as left argument" + getErrorContext(_line));
        break;
    default:
        break;
    }
}

bool oA::Lang::ShuntingYard::peekStackArguments(Vector<ASTNodePtr>::iterator &it, ASTNode &target, Uint args) noexcept
{
    auto tmp = args;

    for (; tmp > 0 && it != _stack.begin(); --tmp)
        --it;
    if (tmp)
        return false;
    for (; args > 0; --args) {
        target.emplace(std::move(*it));
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
    oA::Expression expr;

    if (_mode == Expression || _mode == Function)
        _target->setTree(std::move(_expr));
    else {
        expr.setTree(std::move(_expr));
        _target->connectEvent(std::move(expr));
    }
    if (_mode == Expression)
        _target->compute();
}