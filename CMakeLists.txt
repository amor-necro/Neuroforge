cmake_minimum_required(VERSION 3.25)

project(Neuroforge
    VERSION 0.1.0
    DESCRIPTION "High-performance numerical computing engine built from first principles in Modern C++23"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The public target is intentionally header-only until the project introduces
# its first implementation unit. Module targets will be added with their
# corresponding implementations, not pre-emptively.
add_library(neuroforge INTERFACE)
add_library(Neuroforge::neuroforge ALIAS neuroforge)

target_include_directories(neuroforge
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

include(cmake/CompilerWarnings.cmake)

option(NEUROFORGE_BUILD_TESTS "Build unit tests" ON)

if(NEUROFORGE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
