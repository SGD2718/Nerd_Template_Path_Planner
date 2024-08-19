cmake_minimum_required(VERSION 3.27)
project(VEX_Path_Planner)

set(CMAKE_CXX_STANDARD 17)

#[[# Find the Boost library
find_package(Boost 1.85.0 REQUIRED COMPONENTS system filesystem HINTS opt/homebrew/cellar/boost/1.85.0)

# Include Boost headers
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(MyExecutable main.cpp)
    target_link_libraries(MyExecutable ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find Boost libraries!")
endif()]]#

# GSL library
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})

add_executable(VEX_Path_Planner main.cpp
        Vector2.h
        MathUtils.h
        Curve.h
        Clothoid.h
        Vector2.cpp
        Clothoid.cpp
        Line.cpp
        Line.h
        Curve.cpp
        CircularArc.cpp
        CircularArc.h
        Curves.h
        Fresnel.h
        Fresnel.cpp)
