cmake_minimum_required(VERSION 3.0.0)
project(openApp)

# This file need the variable 'oAPath' to be set !

set(oARoot ${oAPath}/openApp)
set(oATypes ${oARoot}/Types)
set(oACore ${oARoot}/Core)
set(oAContainers ${oARoot}/Containers)
set(oAMemory ${oARoot}/Memory)
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
)

set(Core
    ${oACore}/Log.hpp
    ${oACore}/Log.cpp
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

set(Network
)

set(oASources
    ${Types}
    ${Core}
    ${Containers}
    ${Network}
)