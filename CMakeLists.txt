# This should be self-explanatory.
cmake_minimum_required(VERSION 3.10)

# Tell CMake to use the C++20 standard, to compile with exceptions, and to
# build in debug mode.
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXCEPTIONS ON)

# This should also be self-explanatory.
project(cppvkvoxel)

# Tell GLFW's CMake files to not build the docs, tests, or examples, we just
# want the library.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add the GLFW subdirectory.
add_subdirectory(glfw)

# This should ALSO be self-explanatory.
if(NOT APP_RESOURCE_PATH)
	set(APP_RESOURCE_PATH "..")
endif()

# Find Vulkan. You should have Vulkan SDK installed in order for it to be
# found.
find_package(Vulkan REQUIRED)

# Compile all C & C++ source files in the source directory. We likely won't be
# using any raw C code, but it's good to have this here in case we do.
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c)

# Make sure our program gets compiled as a standalone executable.
add_executable(cppvkvoxel ${SOURCES})

# Tell CMake to use GLFW's include directory & ours.
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tell CMake to link our program against GLFW & Vulkan.
target_link_libraries(cppvkvoxel glfw Vulkan::Vulkan)