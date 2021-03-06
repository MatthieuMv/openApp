cmake_minimum_required(VERSION 3.0.0)
project(openApp VERSION 1.0.0)

set(oALibraryDir ..)
set(oATestsDir ${oALibraryDir}/Tests)

include(${oALibraryDir}/openApp/openApp.cmake)

set(TestsSources
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

set(CMAKE_CXX_STANDARD 17)


if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -coverage")
endif ()

link_libraries(criterion)

include_directories(${oALibraryDir})

add_executable(run_tests ${TestsSources} ${oASources})