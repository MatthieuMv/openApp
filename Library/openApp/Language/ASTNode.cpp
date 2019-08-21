/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ASTNode
*/

#include <openApp/Containers/UMap.hpp>
#include <openApp/Core/Log.hpp>
#include <openApp/Language/Nodes.hpp>

void oA::Lang::ASTNode::ShowTree(const ASTNode &root, Int tab)
{
    cout << Repeat(tab++) << "   ";
    switch (root.getType()) {
        case Root:
            cout << "@Root:@ ";
            break;
        case Import:
            cout << "@Import:@  " << dynamic_cast<const ImportNode &>(root).directory;
            break;
        case Class:
            cout << "@Class:@  " << dynamic_cast<const ClassNode &>(root).name;
            break;
        case Declaration:
            {
                auto &dec = dynamic_cast<const DeclarationNode &>(root);
                cout << "@" << dec.getDeclarationSymbol() << "@: #" << dec.name << ":##";
                for (auto &token : dec.tokens)
                    cout << ' ' << token.first;
            }
            break;
        case ExpressionGroup:
            cout << "@Expression Group:@";
            break;
        case Group:
            cout << "@Group:@ ";
            break;
        case Reference:
            cout << "@Reference:@ "  << dynamic_cast<const ReferenceNode &>(root).ptr->toString();
            break;
        case Local:
            cout << "@Local:@  " << dynamic_cast<const LocalNode &>(root).local.toString();
            break;
        case Value:
            cout << "@Value:@  " << dynamic_cast<const ValueNode &>(root).value.toString();
            break;
        case Operator:
            cout << "@Operator:@  " << GetOperatorSymbol(dynamic_cast<const OperatorNode &>(root).op);
            break;
        case Statement:
            cout << "@Statement:@  " << GetStatementSymbol(dynamic_cast<const StatementNode &>(root).statement);
            break;
    }
    cout << endl;
    for (const auto &child : root.children)
        ShowTree(*child, tab);
    --tab;
}