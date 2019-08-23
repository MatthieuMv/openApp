/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Instantiator
*/

#pragma once

#include <openApp/Containers/Stack.hpp>
#include <openApp/Containers/List.hpp>
#include <openApp/App/Item.hpp>
#include <openApp/Language/ShuntingYard.hpp>

namespace oA::Lang
{
    class Instantiator;

    class ImportNode;
    class ClassNode;
    class DeclarationNode;
}

/**
 * @brief This class process a file architecture (recurisvely find implicit links) and instantiate an Item pointer
 */
class oA::Lang::Instantiator
{
public:
    struct Unit
    {
        String path;
        ASTNodePtr tree;
    };

    using UnitPtr = Shared<Unit>;

    struct Context
    {
        UnitPtr unit;
        ItemPtr root;
        ItemPtr target;
        Vector<String> imports;
        Vector<oA::Function<void(void)>> unresolved;
    };

    /**
     * @brief Instanciate an openApp class file (.oA)
     *
     * @param path File path
     * @return ItemPtr Resulting Item pointer
     */
    static ItemPtr ProcessFile(const String &path, bool verbose = false, bool showItem = false);

    /**
     * @brief Instanciate an openApp class string
     *
     * @param string File content
     * @param context File name
     * @return ItemPtr Resulting Item pointer
     */
    static ItemPtr ProcessString(const String &string, const String &context = "Root", bool verbose = false, bool showItem = false);

private:
    Stack<Context> _contexts;
    Vector<UnitPtr> _units;
    Uint _tab = 0;
    bool _verbose = false;

    Instantiator(bool verbose) : _verbose(verbose) {}

    /**
     * @brief Process a file
     *
     * @param path File path
     * @return ItemPtr Resulting Item
     */
    ItemPtr process(const String &path);

    /**
     * @brief Process a string
     *
     * @param string Content
     * @param context File name
     * @return ItemPtr Resulting Item
     */
    ItemPtr process(const String &string, const String &context);

    /**
     * @brief Open a new Context with a valid path
     *
     * @param path Context's path
     */
    void openFileContext(String &&path);

    /**
     * @brief Close current context and return its root Item
     *
     * @return ItemPtr Root Item
     */
    ItemPtr closeContext(void);

    /**
     * @brief Process a Context's Unit tree node
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
     * @brief Search a file path given the class name
     *
     * @param name Class' name
     * @return String Path (empty if non-existent)
     */
    String searchClassPath(const String &name);

    /**
     * @brief Process declaration node
     *
     * @param node Node to process
     */
    void processDeclaration(const DeclarationNode &node);

    /**
     * @brief Prepare a declaration
     *
     * @param node Node
     * @return ShuntingYard::Mode ShuntingYard mode
     */
    ShuntingYard::Mode prepareDeclaration(const DeclarationNode &node);

    /**
     * @brief Process special declaration node if it exists
     *
     * @param node Node to process
     * @return true Node was a special node and has been instantied
     * @return false Node wasn't a special node
     */
    bool processSpecialDeclaration(const DeclarationNode &node);

    /**
     * @brief Process ID
     *
     * @param node Node to process
     */
    void processID(const DeclarationNode &node);

    /**
     * @brief Process relative size
     *
     * @param node Node to process
     */
    void processRelativeSize(const DeclarationNode &node);

    /**
     * @brief Process relative pos
     *
     * @param node Node to process
     */
    void processRelativePos(const DeclarationNode &node);

    /**
     * @brief Tell if there is any context loaded
     *
     * @return true There is at least 1 context opened
     * @return false No context is opened
     */
    bool hasContext(void) const noexcept { return !_contexts.empty(); }

    /**
     * @brief Get current context
     *
     * @return Context& Current Context
     */
    Context &context(void) { return _contexts.top(); }

    /**
     * @brief Get current context
     *
     * @return const Context& Current Context
     */
    const Context &context(void) const { return _contexts.top(); }

    /**
     * @brief Tell if the current Context has a Unit loaded
     *
     * @return true Context has Unit
     * @return false Context has not Unit
     */
    bool hasUnit(void) const { return hasContext() && context().unit; }

    /**
     * @brief Return Context's unit
     *
     * @return Unit& Current Unit
     */
    Unit &unit(void) { return *context().unit; }

    /**
     * @brief Return Context's unit
     *
     * @return const Unit& Current Unit
     */
    const Unit &unit(void) const { return *context().unit; }

    /**
     * @brief Get the Error Context object of current context
     *
     * @return String Error message
     */
    String getErrorContext(void) const { return " | @" + unit().path + '@'; }

    /**
     * @brief Get the Error Context object of current context
     *
     * @return String Error message
     */
    String getErrorContext(Uint line) const { return getErrorContext() + " line #" + ToString(line) + '#'; }
};