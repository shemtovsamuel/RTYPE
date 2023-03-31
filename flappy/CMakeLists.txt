cmake_minimum_required(VERSION 3.18)

project(flappy)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(engine STATIC IMPORTED)
if (WIN32)
  set_target_properties(engine PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/engine.lib)
elseif (UNIX)
  set_target_properties(engine PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libengine.a)
endif()

include_directories(include)
set(GAMEONE_SOURCES
	src/main.cpp
  src/game.cpp
  src/EntityTemplate.cpp
  src/debug/Debugger.cpp
  src/debug/Logger.cpp
)

add_executable(flappy ${GAMEONE_SOURCES})

target_include_directories(flappy PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CONAN_INCLUDE_DIRS}
)

target_link_libraries(flappy engine ${CONAN_LIBS})

if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT flappy)
  set_property(TARGET flappy PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()

set (source "${CMAKE_SOURCE_DIR}/src/scripts")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/bin/scripts")
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
  DEPENDS ${destination}
  COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

set (source "${CMAKE_SOURCE_DIR}/assets")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/bin/assets")
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
  DEPENDS ${destination}
  COMMENT "symbolic link resources folder from ${source} => ${destination}"
)