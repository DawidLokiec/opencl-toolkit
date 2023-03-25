cmake_minimum_required(VERSION 3.26.1)
project(opencl-toolkit LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME}
        src/device_manager.cpp
        src/program.cpp
        src/command_queue.cpp
        src/error.cpp
        src/base_buffer.cpp
        src/read_only_buffer.cpp
        src/write_only_buffer.cpp
        src/context.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
# A CMake pattern to have headers that are not seen by the client of this library.
# So headers which not have to be visible for client-code should be placed in src/
target_include_directories(${PROJECT_NAME} PRIVATE src)

if (MSVC)
    # PRIVATE specifies that the specified compile options are only for the ${PROJECT_NAME} itself,
    # and not for any targets that link to it.
    # warning level 4 and all warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /EHsc /std:c++20)
else ()
    # PRIVATE specifies that the specified compile options are only for the ${PROJECT_NAME} itself,
    # and not for any targets that link to it.
    # lots of warnings and all warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

#OpenCL
find_package(OpenCL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)