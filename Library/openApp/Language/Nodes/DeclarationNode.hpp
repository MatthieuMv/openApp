/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** DeclarationNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>
#include <openApp/Language/Lexer.hpp>

namespace oA::Lang { struct DeclarationNode; }

struct oA::Lang::DeclarationNode : public ASTNode
{
    enum DeclarationType {
        AssignmentDeclaration,
        PropertyDeclaration,
        FunctionDeclaration,
        EventDeclaration
    };

    String name;
    DeclarationType type;
    Lexer::TokenList tokens;

    DeclarationNode(String &&declarationName, DeclarationType declarationType) : name(std::move(declarationName)), type(declarationType) {}

    virtual ~DeclarationNode(void) = default;
    
    virtual NodeType getType(void) const { return Declaration; }

    String getDeclarationSymbol(void) const noexcept {
        switch (type) {
        case AssignmentDeclaration:
            return "Assignment";
        case PropertyDeclaration:
            return "Property";
        case FunctionDeclaration:
            return "Function";
        case EventDeclaration:
            return "Event";
        default:
            return String();
        }
    }
};
