cmake_minimum_required(VERSION 3.18)

project(rtype-server)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(GAMEONE_SOURCES
	src/main.cpp
)

add_executable(rtype-server ${GAMEONE_SOURCES})

target_include_directories(rtype-server PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(rtype-server ${CONAN_LIBS})

if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT rtype-server)
  set_property(TARGET rtype-server PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()