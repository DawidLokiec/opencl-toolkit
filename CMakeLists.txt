cmake_minimum_required(VERSION 3.25.1)
project(opencl-toolkit LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(opencl-toolkit
        src/library.cpp
        )

if (MSVC)
    # PUBLIC = use this compile options also while compiling other projects
    # warning level 4 and all warnings as errors
    target_compile_options(opencl-toolkit PUBLIC /W4 /WX)
else ()
    # PUBLIC = use this compile options also while compiling other projects
    # lots of warnings and all warnings as errors
    target_compile_options(opencl-toolkit PUBLIC -Wall -Wextra -pedantic -Werror)
endif ()
