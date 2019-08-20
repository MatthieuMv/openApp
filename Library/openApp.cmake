cmake_minimum_required(VERSION 3.0.0)
project(openApp)

# This file need the variable 'oAPath' to be set !

set(oARoot ${oAPath}/openApp)
set(oATypes ${oARoot}/Types)
set(oACore ${oARoot}/Core)
set(oAContainers ${oARoot}/Containers)
set(oAApp ${oARoot}/App)
set(oANetwork ${oARoot}/Network)
set(oALanguage ${oARoot}/Language)

set(Types
    ${oATypes}/Error.hpp
    ${oATypes}/Function.hpp
    ${oATypes}/String.hpp
    ${oATypes}/String.cpp
    ${oATypes}/Scalars.hpp
    ${oATypes}/Stream.hpp
    ${oATypes}/FStream.hpp
    ${oATypes}/SStream.hpp
    ${oATypes}/V2.hpp
    ${oATypes}/V3.hpp
    ${oATypes}/Thread.hpp
    ${oATypes}/Memory.hpp
    ${oATypes}/Mutex.hpp
    ${oATypes}/Color.hpp
    ${oATypes}/Color.cpp
    ${oATypes}/Variant.hpp
)

set(Core
    ${oACore}/Chrono.hpp
    ${oACore}/Console.hpp
    ${oACore}/Log.hpp
    ${oACore}/Log.cpp
    ${oACore}/LogUtils.hpp
    ${oACore}/Path.hpp
    ${oACore}/Path.cpp
    ${oACore}/Signal.hpp
    ${oACore}/Property.hpp
    ${oACore}/Property.cpp
    ${oACore}/GetLine.hpp
    ${oACore}/GetLine.cpp
    ${oACore}/Var.hpp
    ${oACore}/Var.cpp
)

set(Containers
    ${oAContainers}/Array.hpp
    ${oAContainers}/ContainerHelper.hpp
    ${oAContainers}/Deque.hpp
    ${oAContainers}/List.hpp
    ${oAContainers}/Map.hpp
    ${oAContainers}/Pair.hpp
    ${oAContainers}/Queue.hpp
    ${oAContainers}/Stack.hpp
    ${oAContainers}/Tuple.hpp
    ${oAContainers}/UMap.hpp
    ${oAContainers}/Vector.hpp
)

set(App
    ${oAApp}/App.hpp
    ${oAApp}/App.cpp
    ${oAApp}/Item.hpp
    ${oAApp}/Item.cpp
    ${oAApp}/ItemFactory.hpp
    ${oAApp}/ItemFactory.cpp
    ${oAApp}/ItemHandler.hpp
    ${oAApp}/ItemHandler.cpp
    ${oAApp}/PropertyHandler.hpp
    ${oAApp}/PropertyHandler.cpp
    ${oAApp}/RenderContexts.hpp
    ${oAApp}/IRenderer.hpp
    ${oAApp}/Event.hpp
    ${oAApp}/Events/KeyboardEvent.hpp
    ${oAApp}/Events/MotionEvent.hpp
    ${oAApp}/Events/MouseEvent.hpp
    ${oAApp}/Events/WheelEvent.hpp
    ${oAApp}/Events/WindowEvent.hpp
    ${oAApp}/Widgets/Window.hpp
    ${oAApp}/Widgets/Rectangle.hpp
    ${oAApp}/Widgets/Image.hpp
    ${oAApp}/Widgets/EventArea.hpp
    ${oAApp}/Widgets/Button.hpp
    ${oAApp}/Widgets/ImageButton.hpp
)

set(Language
    ${oALanguage}/Operator.hpp
    ${oALanguage}/Operator.cpp
    ${oALanguage}/Statement.hpp
    ${oALanguage}/Statement.cpp
    ${oALanguage}/Lexer.hpp
    ${oALanguage}/Lexer.cpp
    ${oALanguage}/Parser.hpp
    ${oALanguage}/Parser.cpp
    ${oALanguage}/ASTNode.hpp
    ${oALanguage}/ASTNode.cpp
    ${oALanguage}/Instantiator.hpp
    ${oALanguage}/Instantiator.cpp
    ${oALanguage}/ShuntingYard.hpp
    ${oALanguage}/ShuntingYard.cpp
    ${oALanguage}/Nodes.hpp
    ${oALanguage}/Nodes/ImportNode.hpp
    ${oALanguage}/Nodes/ClassNode.hpp
    ${oALanguage}/Nodes/DeclarationNode.hpp
    ${oALanguage}/Nodes/GroupNode.hpp
    ${oALanguage}/Nodes/ReferenceNode.hpp
    ${oALanguage}/Nodes/LocalNode.hpp
    ${oALanguage}/Nodes/ValueNode.hpp
    ${oALanguage}/Nodes/OperatorNode.hpp
    ${oALanguage}/Nodes/OperatorNode.cpp
    ${oALanguage}/Nodes/StatementNode.hpp
    ${oALanguage}/Nodes/StatementNode.cpp
)

set(Network
)

set(oASources
    ${Types}
    ${Core}
    ${Containers}
    ${App}
    ${Network}
    ${Language}
)