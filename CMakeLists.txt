#
# engine
#

cmake_minimum_required(VERSION 3.12)

include(cmake/tools/guards.cmake)

#
# Install SDL2 dependencies
#

include(cmake/vcpkg.cmake)

vcpkg_bootstrap()
vcpkg_install_packages(sdl2 sdl2-gfx)

#
# Project configuration
#

project(
    engine
    DESCRIPTION "A small data-driven game engine"
    HOMEPAGE_URL "https://github.com/florianvazelle/engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -msse4.1")

include(cmake/tools/libcpp.cmake)
include(cmake/tools/threads.cmake)
include(cmake/tools/sanitizer.cmake)

#
# Add engine library target
#

include(GNUInstallDirs)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${engine_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(WIN32)
    # Visual Studio 2018 15.8 implemented conformant support for std::aligned_storage, but the conformant support is only enabled when the following flag is passed, to avoid
    # breaking backwards compatibility with code that relied on the non-conformant behavior (the old nonconformant behavior is not used with Binaryen)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_ENABLE_EXTENDED_ALIGNED_STORAGE")

    # Just setting vcpkg.cmake as toolchain file does not seem to actually pull in the code
    include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
endif()

# Find SDL2 and SDL2_gfx libraries and link it to the project
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-gfx CONFIG REQUIRED)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} INTERFACE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_gfx)
else()
    target_link_libraries(${PROJECT_NAME} INTERFACE SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_gfx)
endif()

# add_libcpp_option(TARGET ${PROJECT_NAME})
add_threads_option(TARGET ${PROJECT_NAME})
add_sanitizer_options(TARGET ${PROJECT_NAME})

#
# Entry point
#

option(ENGINE_BUILD_APP "Enable building with entry point." ON)

if(ENGINE_BUILD_APP)
    option(ENGINE_INSTALL_APP "Enable installation of the entry point." OFF)

    file(GLOB_RECURSE APP_SOURCES "${CMAKE_SOURCE_DIR}/app/src/*.cpp")
    file(GLOB_RECURSE APP_HEADERS "${CMAKE_SOURCE_DIR}/app/include/*.hpp")

    set(APP_NAME pong)

    # Add an executable for the file app/main.cc
    add_executable(${APP_NAME} app/main.cpp ${APP_SOURCES} ${APP_HEADERS})

    target_include_directories(${APP_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/app/include)

    # Link the executable to library
    target_link_libraries(${APP_NAME} PRIVATE ${PROJECT_NAME})

    # Install the executable
    if (ENGINE_INSTALL_APP)
        install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} DESTINATION .)
    endif()
endif()

#
# Tests
#

option(ENGINE_BUILD_TESTING "Enable building tests." OFF)

if(ENGINE_BUILD_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()

#
# Documentation
#

option(ENGINE_BUILD_DOCS "Enable building with documentation." OFF)

if(ENGINE_BUILD_DOCS)
    find_package(Doxygen 1.8)

    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    endif()
endif()