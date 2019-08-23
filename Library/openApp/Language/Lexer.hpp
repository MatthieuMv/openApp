/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#pragma once

#include <openApp/Types/String.hpp>
#include <openApp/Types/Stream.hpp>
#include <openApp/Containers/Pair.hpp>
#include <openApp/Containers/List.hpp>

namespace oA::Lang { class Lexer; }

/**
 * @brief This class is used to process .oA files into tokens
 */
class oA::Lang::Lexer
{
public:
    /**
     * @brief List of token paired with the line in source
     */
    using TokenList = List<Pair<String, Int>>;

    /**
     * @brief Convert a file into a list of tokens
     *
     * @param path File path
     * @param tokens Tokens container
     */
    static void ProcessFile(const String &path, TokenList &tokens);

    /**
     * @brief Convert a file into a list of tokens
     *
     * @param string File content
     * @param tokens Tokens container
     * @param context Name of the context (filename)
     */
    static void ProcessString(const String &string, TokenList &tokens, const String &context = "Root");

    /**
     * @brief Show content of token list into oA::cout
     *
     * @param list Token list
     */
    static void ShowTokenList(const TokenList &list);

private:
    const String &_context;
    IStream &_ss;
    TokenList &_tokens;
    Int _line = 1;

    /**
     * @brief Construct a new Lexer object
     *
     * @param context Filename
     * @param stream Stream
     * @param tokens Tokens container
     */
    Lexer(const String &context, IStream &stream, TokenList &tokens);

    /**
     * @brief Process internal stream and fill tokens container
     */
    void process(void);

    /**
     * @brief Process a single character
     *
     * @param c Character to process
     */
    void processChar(char c);

    /**
     * @brief Process a string
     *
     * @param res String containing the first character of the string
     */
    void processString(String &&res);

    /**
     * @brief Process a number
     *
     * @param res String containing the first character of the number
     */
    void processNumber(String &&res);

    /**
     * @brief Process a comment
     *
     * @param end Token of end comment
     */
    void processComment(bool multiline);

    /**
     * @brief Process an operator
     *
     * @param res String containing the first character of the operator
     */
    void processOperator(String &&res);

    /**
     * @brief Process an in/decrement operator
     *
     * @param res Operator
     */
    void processIncrement(String &res);

    /**
     * @brief Process a word and try to identify it
     *
     * @param res String containing the first character of the word
     */
    void processWord(String &&res);

    /**
     * @brief Process a word followed by a function call
     *
     * @param res String containing the first character of the function call
     */
    void processFunctionCall(String &&res);

    /**
     * @brief Process function call arguments
     */
    void processFunctionArgs(void);

    /**
     * @brief Process a word followed by an index access
     *
     * @param res String containing the first character of the index access
     */
    void processIndexAccess(String &&res);

    /**
     * @brief Check internal stream' state
     *
     * @return true Stream is ready
     * @return false Stream end reached
     */
    bool isEnd(void) const { return !_ss.good(); }

    /**
     * @brief Peek a single character from stream
     *
     * @return char Resulting char
     */
    char peek(void) { return _ss.peek(); }

    /**
     * @brief Extract a single character from stream
     *
     * @return char Resulting char
     */
    char get(void) { char c = _ss.get(); return (c == '\n' ? ++_line, c : c); }

    /**
     * @brief Build an error context String object
     *
     * @param line Line which triggered the error (-1 for current)
     * @return String Resulting error message
     */
    String getErrorContext(Int line = -1) const noexcept { return " | @" + _context + "@ line #" + ToString(line < 0 ? _line : line) + "#"; }

    /**
     * @brief Copy a string into token list
     *
     * @param token String to copy
     */
    void pushToken(const String &token) { _tokens.emplace_back(std::make_pair(token, _line)); }

    /**
     * @brief Move a string into token list
     *
     * @param token String to move
     */
    void pushToken(String &&token) { _tokens.emplace_back(std::make_pair(std::move(token), _line)); }
};