cmake_minimum_required(VERSION 3.18)

project(engine)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)
set(ENGINE_SOURCES
    src/engine.cpp
)

add_library(engine STATIC ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC include ${CONAN_INCLUDE_DIRS})

target_link_libraries(engine ${CONAN_LIBS})