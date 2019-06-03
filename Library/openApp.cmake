cmake_minimum_required(VERSION 3.0.0)
project(openApp)

# This file need the variable 'oAPath' to be set !

set(Types
    ${oAPath}/Types/Scalars.hpp
    ${oAPath}/Types/Function.hpp
    ${oAPath}/Types/String.hpp
    ${oAPath}/Types/String.cpp
)

set(Core
    ${oAPath}/Core/Error.hpp
)

set(Containers
    ${oAPath}/Containers/ContainerHelper.hpp
    ${oAPath}/Containers/Pair.hpp
    ${oAPath}/Containers/Map.hpp
    ${oAPath}/Containers/UMap.hpp
    ${oAPath}/Containers/Vector.hpp
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