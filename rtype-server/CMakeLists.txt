cmake_minimum_required(VERSION 3.18)

project(rtype-server)

include(InstallRequiredSystemLibraries)
include(CPack)
set(CPACK_PACKAGE_NAME "rtype-server")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "Epitech")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "rtype-server")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "rtype-server")

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
        src/ServerGame.cpp
        src/EntityTemplate.cpp
        src/serverInstance.cpp
        src/LevelManager.cpp
        src/ScoreManager.cpp
        ../game/src/game.cpp
        )


add_executable(rtype-server ${GAMEONE_SOURCES})

target_include_directories(rtype-server PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CONAN_INCLUDE_DIRS}
        )

target_link_libraries(rtype-server engine ${CONAN_LIBS})

if(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT rtype-server)
  set_property(TARGET rtype-server PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()

install(TARGETS rtype-server DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib DESTINATION bin)

