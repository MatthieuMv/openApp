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
    ${oATypes}/Scalars.hpp
    ${oATypes}/Function.hpp
    ${oATypes}/String.hpp
    ${oATypes}/String.cpp
    ${oATypes}/Error.hpp
)

set(Core
)

set(Containers
    ${oAContainers}/ContainerHelper.hpp
    ${oAContainers}/Pair.hpp
    ${oAContainers}/Map.hpp
    ${oAContainers}/UMap.hpp
    ${oAContainers}/Vector.hpp
)

set(Memory
)

set(Time
)

set(Network
)

set(oASources
    ${Types}
    ${Core}
    ${Containers}
    ${Memory}
    ${Time}
    ${Network}
)