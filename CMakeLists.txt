cmake_minimum_required(VERSION 3.0.0)
project(openApp VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SRC Sources)
set(INC Includes)
set(HCORE ${INC}/Core)
set(HAPP ${INC}/App)
set(SCORE ${SRC}/Core)
set(SAPP ${SRC}/App)
set(RENDER Renderer)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -fPIC -std=c++17")
include_directories(${INC})

set(HEADERS
    ${INC}/App.hpp
    ${INC}/Core.hpp
    ${INC}/openApp.hpp
    ${HAPP}/AppFactory.hpp
    ${HAPP}/App.hpp
    ${HAPP}/Button.hpp
    ${HAPP}/Context.hpp
    ${HAPP}/Context3D.hpp
    ${HAPP}/EventArea.hpp
    ${HAPP}/Event.hpp
    ${HAPP}/IApp.hpp
    ${HAPP}/ImageButton.hpp
    ${HAPP}/Image.hpp
    ${HAPP}/IRenderer.hpp
    ${HAPP}/IRenderer3D.hpp
    ${HAPP}/Item.hpp
    ${HAPP}/Keys.hpp
    ${HAPP}/Parser.hpp
    ${HAPP}/Rectangle.hpp
    ${HAPP}/Switch.hpp
    ${HAPP}/Scene3D.hpp
    ${HAPP}/Text.hpp
    ${HAPP}/TextInput.hpp
    ${HAPP}/Var.hpp
    ${HAPP}/Window.hpp
    ${HCORE}/Array.hpp
    ${HCORE}/Chrono.hpp
    ${HCORE}/Colors.hpp
    ${HCORE}/Console.hpp
    ${HCORE}/ContainerHelper.hpp
    ${HCORE}/Error.hpp
    ${HCORE}/Expression.hpp
    ${HCORE}/Factory.hpp
    ${HCORE}/FStream.hpp
    ${HCORE}/Function.hpp
    ${HCORE}/List.hpp
    ${HCORE}/Log.hpp
    ${HCORE}/Map.hpp
    ${HCORE}/Memory.hpp
    ${HCORE}/Mutex.hpp
    ${HCORE}/Operators.hpp
    ${HCORE}/Pair.hpp
    ${HCORE}/Path.hpp
    ${HCORE}/Property.hpp
    ${HCORE}/Queue.hpp
    ${HCORE}/Scalar.hpp
    ${HCORE}/Signal.hpp
    ${HCORE}/Stack.hpp
    ${HCORE}/Stream.hpp
    ${HCORE}/String.hpp
    ${HCORE}/StringStream.hpp
    ${HCORE}/Thread.hpp
    ${HCORE}/Tuple.hpp
    ${HCORE}/UMap.hpp
    ${HCORE}/Variant.hpp
    ${HCORE}/Vector.hpp
    ${HCORE}/V2.hpp
    ${HCORE}/V3.hpp
)

set(SOURCES
    ${SCORE}/Log.cpp
    ${SCORE}/Path.cpp
    ${SCORE}/Operators.cpp
    ${SCORE}/Colors.cpp
    ${SCORE}/String.cpp
    ${SAPP}/Item.cpp
    ${SAPP}/ItemChilds.cpp
    ${SAPP}/ItemProperty.cpp
    ${SAPP}/ItemExpression.cpp
    ${SAPP}/ItemFind.cpp
    ${SAPP}/Parser.cpp
    ${SAPP}/Var.cpp
    ${SAPP}/AppFactory.cpp
    ${SAPP}/Event.cpp
)

set(GRAPHIC
    ${RENDER}/Irrlicht/Irrlicht.hpp
    ${RENDER}/Irrlicht/EventHandler.hpp
    ${RENDER}/Irrlicht/IrrlichtContext.hpp
    ${RENDER}/Irrlicht/Irrlicht.cpp
    ${RENDER}/Irrlicht/Irrlicht3D.cpp
    ${RENDER}/Irrlicht/EventHandler.cpp
)

link_libraries(Irrlicht)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library(openApp ${HEADERS} ${SOURCES} ${GRAPHIC})