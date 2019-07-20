/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Instantiator
*/

#pragma once

#include <openApp/Containers/Stack.hpp>
#include <openApp/App/Item.hpp>
#include <openApp/Language/ASTNode.hpp>
#include <openApp/Language/Nodes/ImportNode.hpp>
#include <openApp/Language/Nodes/ClassNode.hpp>
#include <openApp/Language/Nodes/DeclarationNode.hpp>
#include <openApp/Language/Nodes/ClassNode.hpp>

namespace oA::Lang { class Instantiator; }

/**
 * @brief This class process a file architecture (recurisvely find implicit links) and instantiate an Item pointer 
 */
class oA::Lang::Instantiator
{
public:
    /**
     * @brief Instanciate an openApp class file (.oA)
     * 
     * @param path File path
     * @return ItemPtr Resulting Item pointer
     */
    static ItemPtr ProcessFile(const String &path);

    /**
     * @brief Instanciate an openApp class string
     * 
     * @param string String to instanciate
     * @param context String context (equal to filename)
     * @return ItemPtr Resulting Item pointer
     */
    //static ItemPtr ProcessString(const String &string, const String &context = "Root");

    using UnitMap = UMap<String, ASTNodePtr>;
    using Unit = Pair<const String, ASTNodePtr>;

    /**
     * @brief This class hold a context's data
     */
    struct Context
    {
        Context(Unit &contextUnit) : unit(contextUnit) {}

        Unit &unit;
        ItemPtr root;
        Vector<Function<void(void)>> unresolved;
    };

private:
    UnitMap _units;
    Vector<String> _imports;
    Stack<Context> _contexts;

    /**
     * @brief Construct a new Instantiator object
     */
    Instantiator(void) = default;

    /**
     * @brief Process a file / class name
     * 
     * @param name Name / Path of the class
     */
    ItemPtr processName(const String &name);

    /**
     * @brief Get the Path of a name
     * 
     * @param name Name to search
     * @return String Path
     */
    String getNamePath(const String &name) const noexcept;

    /**
     * @brief Process an Unit with a given path
     * 
     * @param path Unit path
     */
    ItemPtr processUnit(const String &path);

    /**
     * @brief Process a node
     * 
     * @param node Node to process
     */
    void processNode(const ASTNode &node);

    /**
     * @brief Process a root node
     * 
     * @param node Node to process
     */
    void processRoot(const ASTNode &node);

    /**
     * @brief Process an import node
     * 
     * @param node Node to process
     */
    void processImport(const ImportNode &node);

    /**
     * @brief Process class node
     * 
     * @param node Node to process
     */
    void processClass(const ClassNode &node);

    /**
     * @brief Process declaration node
     * 
     * @param node Node to process
     * @param resolve If false will catch errors and put call in unresolved list
     */
    void processDeclaration(const DeclarationNode &node);

    /**
     * @brief Resolve every unresolved function of the instantiator
     */
    void resolveUnresolved(void) { context().unresolved.apply([](const auto &fct) { fct(); }); }

    /**
     * @brief Check if a context exists
     * 
     * @return true There is at least a context
     * @return false There is no context 
     */
    bool hasContext(void) const noexcept { return !_contexts.empty(); }

    /**
     * @brief Return current context
     * 
     * @return Context& Current context
     */
    Context &context(void) { return _contexts.top(); }

    /**
     * @brief Return current unit
     * 
     * @return Unit& Current unit
     */
    Unit &unit(void) { return context().unit; }

    /**
     * @brief Return current root
     * 
     * @return ItemPtr& Current root
     */
    ItemPtr &root(void) { return context().root; }

    /**
     * @brief Push a new Context to the stack
     * 
     * @param unit Unit of the context
     */
    void pushContext(Unit &unit) { _contexts.emplace(unit); }

    /**
     * @brief Pop a Context from the stack and return its internal item pointer
     * 
     * @return ItemPtr Item pointer
     */
    ItemPtr popContext(void) { auto item(std::move(root())); _contexts.pop(); return item; }

    /**
     * @brief Get the Error Context object of current context
     * 
     * @return String Error message
     */
    String getErrorContext(void) { return " | @" + unit().first + '@'; }
};