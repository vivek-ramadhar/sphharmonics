cmake_minimum_required(VERSION 3.25)
project(sphh)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Dependencies
include(FetchContent)

FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(Eigen)
FetchContent_Declare(
        libigl
        GIT_REPOSITORY https://github.com/libigl/libigl.git
        GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(libigl)

FetchContent_Declare(
        polyscope
        GIT_REPOSITORY https://github.com/nmwsharp/polyscope.git
        GIT_TAG master
)
FetchContent_MakeAvailable(polyscope)

include_directories(.)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../raytracer)

add_executable(plot_polyscope
        nittygritty.h
        plot.cpp)

target_link_libraries(plot_polyscope PRIVATE
        Eigen3::Eigen
        igl_core
        polyscope
)
