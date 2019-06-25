/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Lexer
*/

#pragma once

#include <openApp/Types/Error.hpp>
#include <openApp/Types/String.hpp>
#include <openApp/Types/Stream.hpp>
#include <openApp/Core/GetLine.hpp>
#include <openApp/Language/Tree.hpp>

namespace oA { template<typename T> class Lexer; }

/**
 * @brief This class abstract few Lexer functionalities used in OALexer and ExpressionLexer
 *
 * @tparam T Type of target Tree's node
 */
template<typename T>
class oA::Lexer
{
public:
    using LexTree = Tree<T>;

    /**
     * @brief Construct a new private Lexer object
     *
     * @param stream Stream to extract from from
     * @param target Target Tree
     */
    Lexer(IStream &stream, LexTree &target) : _ss(stream), _target(&target) {
        target.childs.clear();
    }

    /**
     * @brief Destroy the Lexer object
     */
    virtual ~Lexer(void) = default;

    /**
     * @brief Start Lexing process to override
     *
     * @param end End match of processing
     * @return true Lexer reached end
     * @return false Lexer didn't reached end
     */
    virtual bool process(const String &end) = 0;

    /**
     * @brief Read a single token
     *
     * @return true Read success
     * @return false Read failed
     */
    bool readToken(String &token) { return (_ss >> token).operator bool(); }

    /**
     * @brief Read a single internal token
     *
     * @return true Read success
     * @return false Read failed
     */
    bool readToken(void) { return readToken(_token); }

    /**
     * @brief Capture a bracket expression
     *
     * @param target Where to store capture
     */
    void captureExpression(String &target) {
        char c = 0;
        for (c = _ss.get(); c && std::isspace(c) && c != '\n'; c = _ss.get());
        if (c == '\n')
            return;
        else if (c == '{') {
            target.clear();
            GetLine(_ss, target, '}');
        } else {
            String tmp;
            target.push_back(c);
            GetLine(_ss, tmp);
            target += tmp;
        }
    }

protected:
    IStream &_ss; // Internal stream
    String _token; // Internal current token
    LexTree *_target; // Internal current node pointer
};