cmake_minimum_required(VERSION 3.25.1)
project(opencl-toolkit LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME}
        src/buffer_factories.cpp
        src/device_manager.cpp include/program.h src/program.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
# A CMake pattern to have headers that are not seen by the consumers of this library.
# So headers which not have to be visible for consumers should be placed in src/
target_include_directories(${PROJECT_NAME} PRIVATE src)

if (MSVC)
    # PUBLIC = use this compile options also while compiling other projects
    # warning level 4 and all warnings as errors
    target_compile_options(${PROJECT_NAME} PUBLIC /W4 /WX)
else ()
    # PUBLIC = use this compile options also while compiling other projects
    # lots of warnings and all warnings as errors
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror)
endif ()

#OpenCL
find_package(OpenCL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)