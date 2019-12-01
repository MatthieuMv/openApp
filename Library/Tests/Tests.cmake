cmake_minimum_required(VERSION 3.0.0)
project(openApp VERSION 1.0.0)

include(${oALibraryDir}/openApp/openApp.cmake)

set(oATestsDir ${oALibraryDir}/Tests)

set(oATestsSources
    ${oATestsDir}/tests_Error.cpp
    ${oATestsDir}/tests_String.cpp
    ${oATestsDir}/tests_ContainerHelper.cpp
    ${oATestsDir}/tests_Log.cpp
    ${oATestsDir}/tests_V2.cpp
    ${oATestsDir}/tests_V3.cpp
    ${oATestsDir}/tests_Color.cpp
    ${oATestsDir}/tests_LightChrono.cpp
    ${oATestsDir}/tests_Chrono.cpp
    ${oATestsDir}/tests_Path.cpp
    ${oATestsDir}/tests_Signal.cpp
    ${oATestsDir}/tests_Property.cpp
    ${oATestsDir}/tests_PropertyHandler.cpp
    ${oATestsDir}/tests_Var.cpp
    ${oATestsDir}/tests_Item.cpp
    ${oATestsDir}/tests_ItemHandler.cpp
    ${oATestsDir}/tests_ItemFactory.cpp
    ${oATestsDir}/tests_GetLine.cpp
    ${oATestsDir}/tests_Lexer.cpp
    ${oATestsDir}/tests_ASTNode.cpp
    ${oATestsDir}/tests_Operator.cpp
    ${oATestsDir}/tests_Statement.cpp
    ${oATestsDir}/tests_OperatorNode.cpp
    ${oATestsDir}/tests_StatementNode.cpp
    ${oATestsDir}/tests_DeclarationNode.cpp
    ${oATestsDir}/tests_GroupNode.cpp
    ${oATestsDir}/tests_ExpressionGroupNode.cpp
    ${oATestsDir}/tests_ShuntingYard.cpp
)