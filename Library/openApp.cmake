cmake_minimum_required(VERSION 3.0.0)
project(openApp)

# This file need the variable 'oAPath' to be set !

set(oARoot ${oAPath}/openApp)
set(oATypes ${oARoot}/Types)
set(oACore ${oARoot}/Core)
set(oAContainers ${oARoot}/Containers)
set(oAApp ${oARoot}/App)
set(oANetwork ${oARoot}/Network)

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
    ${oACore}/Expression.hpp
    ${oACore}/ExpressionStack.hpp
    ${oACore}/ExpressionNode.hpp
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
    ${oAApp}/Var.hpp
    ${oAApp}/Var.cpp
)

set(Network
)


set(oASources
    ${Types}
    ${Core}
    ${Containers}
    ${App}
    ${Network}
)