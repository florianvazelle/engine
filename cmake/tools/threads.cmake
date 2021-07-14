function(add_threads_option)
    include(CMakeParseArguments)
    
    cmake_parse_arguments(PARSED_ARGS "" "TARGET" "" ${ARGN})

    # Note: if it remains unparsed arguments, here, they can be found in variable PARSED_ARGS_UNPARSED_ARGUMENTS
    if(NOT PARSED_ARGS_TARGET)
        message(FATAL_ERROR "You must provide a target.")
    endif()

    # https://stackoverflow.com/questions/1620918/cmake-and-libpthread
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${PARSED_ARGS_TARGET} INTERFACE Threads::Threads)
endfunction()