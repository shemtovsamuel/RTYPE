cmake_minimum_required(VERSION 3.18)

project(rtype-client)

include(InstallRequiredSystemLibraries)
include(CPack)
set(CPACK_PACKAGE_NAME "rtype-client")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "Epitech")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "rtype-client")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "rtype-client")

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(engine STATIC IMPORTED)
if (WIN32)
  set_target_properties(engine PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/engine.lib)
elseif (UNIX)
  set_target_properties(engine PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libengine.a)
endif()

include_directories(
        include
        ../game/include
)
set(GAMEONE_SOURCES
        src/main.cpp
        src/ClientGame.cpp
        src/EntityTemplate.cpp
        src/LevelManager.cpp
        src/ScoreManager.cpp
        src/clientInstance.cpp
        src/debug/Debugger.cpp
        src/debug/Logger.cpp
        ../game/src/game.cpp
)

add_executable(rtype-client ${GAMEONE_SOURCES})

target_include_directories(rtype-client PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CONAN_INCLUDE_DIRS}
)

target_link_libraries(rtype-client engine ${CONAN_LIBS})

if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT rtype-client)
  set_property(TARGET rtype-client PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
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

install(TARGETS rtype-client DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/scripts DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib DESTINATION bin)