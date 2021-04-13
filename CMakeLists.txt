#
# engine
#

cmake_minimum_required(VERSION 3.12.4)

#
# Building in-tree is not allowed (we take care of your craziness).
#

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

#
# Check project clone recursively
#

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(ENGINE_GIT_SUBMODULE "Check submodules during build" ON)

    if(ENGINE_GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

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
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -Wall -Wextra -msse4.1")
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

# ---- Tool ----

file(GLOB_RECURSE PROJECT_MODULES "${CMAKE_SOURCE_DIR}/cmake/*.cmake")
foreach(ARG ${PROJECT_MODULES})
  include(${ARG})
endforeach()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# ---- Conan package ----

if(CONAN_EXPORTED)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    include("${CMAKE_SOURCE_DIR}/cmake/manual/conan.cmake")
    conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP BUILD missing)
endif()

# ---- Create library ----

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_library(${PROJECT_NAME} OBJECT ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Lib needs its header files, and users of the library must also see these (PUBLIC).
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Find SDL2, SDL2_image and SDL2_gfx libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::Main SDL2::GFX ${CONAN_LIBS})

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
        install(TARGETS pong DESTINATION bin)
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