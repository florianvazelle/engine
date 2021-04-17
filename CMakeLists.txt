#
# engine
#

cmake_minimum_required(VERSION 3.12)

#
# Building in-tree is not allowed (we take care of your craziness).
#

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

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

set(PROJECT_CXX_STANDARD 17)

# https://stackoverflow.com/questions/41361631/optimize-in-cmake-by-default
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -Wall -msse4.1")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

option(ENGINE_USE_LIBCPP "Use libc++ by adding -stdlib=libc++ flag if availbale." ON)
option(ENGINE_USE_SANITIZER "Enable sanitizers by adding -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined flags" OFF)

#
# Compiler stuff
#

if(NOT WIN32 AND ENGINE_USE_LIBCPP)
    include(CheckCXXSourceCompiles)
    include(CMakePushCheckState)

    cmake_push_check_state()

    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -stdlib=libc++")

    check_cxx_source_compiles("
        #include<type_traits>
        int main() { return std::is_same_v<int, char>; }
    " ENGINE_HAS_LIBCPP)

    if(NOT ENGINE_HAS_LIBCPP)
        message(VERBOSE "The option ENGINE_USE_LIBCPP is set (by default) but libc++ is not available. The flag will not be added to the target.")
    endif()

    cmake_pop_check_state()
endif()

#
# Add engine library target
#

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_library(${PROJECT_NAME} OBJECT ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Lib needs its header files, and users of the library must also see these (PUBLIC).
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

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
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_gfx)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_gfx)
endif()

if(ENGINE_USE_SANITIZER)
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined>)
    target_link_libraries(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined>)
endif()

if(ENGINE_HAS_LIBCPP)
    target_compile_options(${PROJECT_NAME} BEFORE PRIVATE -stdlib=libc++)
endif()

# Set the properties you require, e.g. what C++ standard to use. 
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES 
        CXX_STANDARD ${PROJECT_CXX_STANDARD} 
        CXX_STANDARD_REQUIRED YES 
        CXX_EXTENSIONS NO
)

# https://stackoverflow.com/questions/1620918/cmake-and-libpthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

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

    # Set the properties you require, e.g. what C++ standard to use. 
    set_target_properties(
        ${APP_NAME}
        PROPERTIES 
            CXX_STANDARD ${PROJECT_CXX_STANDARD} 
            CXX_STANDARD_REQUIRED YES 
            CXX_EXTENSIONS NO
    )

    # Install the executable
    if (ENGINE_INSTALL_APP)
        install(TARGETS ${APP_NAME} DESTINATION bin)
    endif()
endif()

#
# Tests
#

option(ENGINE_BUILD_TESTING "Enable building tests." OFF)

if(ENGINE_BUILD_TESTING)
    # https://github.com/onqtam/doctest/blob/master/doc/markdown/build-systems.md
    include(ExternalProject)
    find_package(Git REQUIRED)

    ExternalProject_Add(
        doctest
        PREFIX ${CMAKE_BINARY_DIR}/doctest
        GIT_REPOSITORY https://github.com/onqtam/doctest.git
        TIMEOUT 10
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
    )

    # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
    ExternalProject_Get_Property(doctest source_dir)
    set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")

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