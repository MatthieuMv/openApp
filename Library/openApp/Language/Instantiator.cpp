/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Instantiator
*/

#include <openApp/Core/Path.hpp>
#include <openApp/Core/Log.hpp>
#include <openApp/App/ItemFactory.hpp>
#include <openApp/Language/Instantiator.hpp>
#include <openApp/Language/Nodes.hpp>
#include <openApp/Language/Parser.hpp>

oA::ItemPtr oA::Lang::Instantiator::ProcessFile(const String &path, bool verbose, bool showItem)
{
    auto ptr = Instantiator(verbose).process(path);

    if (verbose)
        cout << endl;
    if (showItem) {
        ptr->show();
        cout << endl;
    }
    return ptr;
}

oA::ItemPtr oA::Lang::Instantiator::ProcessString(const String &string, const String &context, bool verbose, bool showItem)
{
    auto ptr = Instantiator(verbose).process(string, context);

    if (verbose)
        cout << endl;
    if (showItem) {
        ptr->show();
        cout << endl;
    }
    return ptr;
}

oA::ItemPtr oA::Lang::Instantiator::process(const String &path)
{
    if (!Path::Exists(path))
        throw AccessError("Instantiator", "Can't process invalid file path @" + path + "@");
    openFileContext(Path::GetCanonicalPath(path));
    processNode(*unit().tree);
    return closeContext();
}

oA::ItemPtr oA::Lang::Instantiator::process(const String &string, const String &context)
{
    auto &ctx = _contexts.emplace_front();

    ctx.unit = std::make_shared<Unit>();
    ctx.unit->path = context;
    ctx.unit->tree = Parser::ParseString(string, context);
    processNode(*unit().tree);
    return closeContext();
}

void oA::Lang::Instantiator::openFileContext(String &&path)
{
    auto &ctx = _contexts.emplace_front();
    auto it = _units.findIf([&path](const auto &unit) { return unit->path == path; });

    if (it != _units.end())
        ctx.unit = *it;
    else {
        ctx.unit = _units.emplace_back(std::make_shared<Unit>());
        ctx.unit->tree = Parser::ParseFile(path);
        ctx.unit->path = std::move(path);
    }
}

oA::ItemPtr oA::Lang::Instantiator::closeContext(void)
{
    auto root = std::move(context().root);
    auto unresolved = std::move(context().unresolved);

    _contexts.erase(_contexts.begin());
    for (auto it = unresolved.begin(); it != unresolved.end(); it = unresolved.erase(it)) {
        try {
            (*it)();
        } catch (...) {
            if (!hasContext())
                throw;
            context().unresolved.emplace_front(*it);
        }
    }
    return root;
}

void oA::Lang::Instantiator::processNode(const ASTNode &node)
{
    switch (node.getType()) {
    case ASTNode::Root:
        return processRoot(node);
    case ASTNode::Import:
        return processImport(dynamic_cast<const ImportNode &>(node));
    case ASTNode::Class:
        return processClass(dynamic_cast<const ClassNode &>(node));
    case ASTNode::Declaration:
        return processDeclaration(dynamic_cast<const DeclarationNode &>(node));
    default:
        throw LogicError("Instantiator", "Invalid unit tree node" + getErrorContext());
    }
}

void oA::Lang::Instantiator::processRoot(const ASTNode &node)
{
    for (const auto &child : node.children) {
        processNode(*child);
    }
}

void oA::Lang::Instantiator::processImport(const ImportNode &node)
{
    context().imports.emplace_back(node.directory);
}

void oA::Lang::Instantiator::processClass(const ClassNode &node)
{
    ItemPtr ptr;
    auto path = searchClassPath(node.name);
    bool isKnownItem = ItemFactory::Exists(node.name);
    auto &ctx = context();

    if (_verbose)
        cout << Repeat(_tab++) << "   " << "@" << node.name << "@ {" << endl;
    if (!isKnownItem && path.empty())
        throw LogicError("Instantiator", "Couldn't find path of class @" + node.name + "@");
    else if (path.empty() || path == unit().path) {
        if (!isKnownItem)
            throw LogicError("Instantiator", "Infinite instantiation loop detected on Item @" + node.name + "@");
        ptr = ItemFactory::Instanciate(node.name);
        for (auto &it : _contexts) {
            if (!it.target)
                continue;
            it.target->appendChild(ptr);
            break;
        }
    } else
        ptr = process(path);
    if (!ctx.root)
        ctx.root = ptr;
    auto oldTarget = ctx.target ? std::move(ctx.target) : ctx.root;
    ctx.target = std::move(ptr);
    processRoot(node);
    ctx.target = std::move(oldTarget);
    if (_verbose)
        cout << Repeat(--_tab) << "   " << "}" << endl;
}

oA::String oA::Lang::Instantiator::searchClassPath(const String &name)
{
    auto filename = name, path = unit().path;
    auto pos = path.find_last_of('/');

    filename.tryAppend(".oA");
    if (pos != path.npos) {
        path.erase(pos + 1);
        path += filename;
        if (Path::Exists(path))
            return path;
    }
    if (Path::Exists(filename))
        return filename;
    for (const auto &import : context().imports) {
        path = import + filename;
        if (Path::Exists(path))
            return path;
    }
    return String();
}

void oA::Lang::Instantiator::processDeclaration(const DeclarationNode &node)
{
    ShuntingYard::Mode mode;
    auto &target = context().target;

    if (!target)
        throw LogicError("Instantiator", "Can't process @declaration@ of null root object" + getErrorContext(node.line));
    if (processSpecialDeclaration(node))
        return;
    mode = prepareDeclaration(node);
    try {
        ShuntingYard::ProcessTokenList(*target, node.name, node.tokens, mode, unit().path, _verbose, _tab);
    } catch (...) {
        if (_verbose)
            cout << "@unresolved@" << endl;
        context().unresolved.emplace_back([this, &node, mode, item = target, ctx = unit().path](void) mutable {
            if (!item->get(node.name).hasTree())
                ShuntingYard::ProcessTokenList(*item, node.name, node.tokens, mode, ctx);
        });
    }
}

oA::Lang::ShuntingYard::Mode oA::Lang::Instantiator::prepareDeclaration(const DeclarationNode &node)
{
    if (_verbose)
        cout << Repeat(_tab) << "   ";
    switch (node.type) {
    case DeclarationNode::AssignmentDeclaration:
        if (_verbose)
            cout << "#" << node.name << "#: ";
        return ShuntingYard::Expression;
    case DeclarationNode::PropertyDeclaration:
        if (_verbose)
            cout << "#" << node.name << "#: ";
        context().target->append(node.name);
        return ShuntingYard::Expression;
    case DeclarationNode::FunctionDeclaration:
        if (_verbose)
            cout << "function #" << node.name << "#: ";
        context().target->append(node.name);
        return ShuntingYard::Function;
    case DeclarationNode::EventDeclaration:
        if (_verbose)
            cout << "event #" << node.name << "#: ";
        return ShuntingYard::Event;
    default:
        return ShuntingYard::Expression;
    }
}

bool oA::Lang::Instantiator::processSpecialDeclaration(const DeclarationNode &node)
{
    static const oA::UMap<String, void(Instantiator::*)(const DeclarationNode &)> Specials = {
        { "id",             &Instantiator::processID            },
        { "relativeSize",   &Instantiator::processRelativeSize  },
        { "relativePos",    &Instantiator::processRelativePos   }
    };
    auto it = Specials.find(node.name);

    if (it == Specials.end())
        return false;
    if (node.type != DeclarationNode::AssignmentDeclaration)
        throw LogicError("Instantiator", "Invalid use of reserved keyword @" + node.name + "@" + getErrorContext(node.line));
    if (_verbose)
        cout << Repeat(_tab) << "   " << '#' << node.name << "#: ";
    (this->*it->second)(node);
    return true;
}

void oA::Lang::Instantiator::processID(const DeclarationNode &node)
{
    if (node.tokens.size() != 1)
        throw LogicError("Instantiator", "Invalid item @id@" + getErrorContext(node.line));
    context().target->setID(node.tokens.front().first);
    if (_verbose)
        cout << context().target->getID() << endl;
}

void oA::Lang::Instantiator::processRelativeSize(const DeclarationNode &node)
{
    auto it = node.tokens.begin();
    auto x = 0.0f, y = 0.0f;
    auto &target = context().target;

    if (it == node.tokens.end())
        throw LogicError("Instantiator", "Invalid use of special property @relativeSize@" + getErrorContext(node.line));
    x = it->first.toFloat();
    if (++it == node.tokens.end() || it->first != "," || ++it == node.tokens.end())
        throw LogicError("Instantiator", "Invalid use of special property @relativeSize@" + getErrorContext(node.line));
    y = it->first.toFloat();
    try {
        target->setExpression("width", "parent.width * " + ToString(x), "relativeSize");
        target->setExpression("height", "parent.height * " + ToString(y), "relativeSize");
        if (_verbose)
            cout << x << ", " << y << endl;
    } catch (...) {
        if (_verbose)
            cout << "@unresolved@" << endl;
        context().unresolved.emplace_back([item = target, ctx = unit().path, x, y, line = node.line](void) mutable {
            try {
                if (!item->get("width").hasTree())
                    item->setExpression("width", "parent.width * " + ToString(x), "relativeSize");
                if (!item->get("height").hasTree())
                    item->setExpression("height", "parent.height * " + ToString(y), "relativeSize");
            } catch (const Error &e) {
                throw LogicError("Instantiator", "Invalid @relativeSize@ | @" + ctx + "@ line #" + ToString(line) + "#\n\t-> " + e.what());
            }
        });
    }
}

void oA::Lang::Instantiator::processRelativePos(const DeclarationNode &node)
{
    auto it = node.tokens.begin();
    auto x = 0.0f, y = 0.0f;
    auto &target = context().target;

    if (it == node.tokens.end())
        throw LogicError("Instantiator", "Invalid use of special property @relativePos@" + getErrorContext(node.line));
    x = it->first.toFloat();
    if (++it == node.tokens.end() || it->first != "," || ++it == node.tokens.end())
        throw LogicError("Instantiator", "Invalid use of special property @relativePos@" + getErrorContext(node.line));
    y = it->first.toFloat();
    try {
        target->setExpression("x", "parent.width * " + ToString(x) + "- width / 2", "relativePos");
        target->setExpression("y", "parent.height * " + ToString(y) + " - height / 2", "relativePos");
        if (_verbose)
            cout << x << ", " << y << endl;
    } catch (...) {
        if (_verbose)
            cout << "@unresolved@" << endl;
        context().unresolved.emplace_back([item = target, ctx = unit().path, x, y, line = node.line](void) mutable {
            try {
                if (!item->get("x").hasTree())
                    item->setExpression("x", "parent.width * " + ToString(x) + "- width / 2", "relativePos");
                if (!item->get("y").hasTree())
                    item->setExpression("y", "parent.height * " + ToString(y) + " - height / 2", "relativePos");
            } catch (const Error &e) {
                throw LogicError("Instantiator", "Invalid @relativePos@ | @" + ctx + "@ line #" + ToString(line) + "#\n\t-> " + e.what());
            }
        });
    }
}