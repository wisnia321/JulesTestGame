cmake_minimum_required(VERSION 3.14)
project(ProjectJules VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Dependencies
include(FetchContent)

# GLFW
set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_COCOA OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WIN32 OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_NULL ON CACHE BOOL "" FORCE)
set(GLFW_PKG_CONFIG_HEADERS "" CACHE STRING "" FORCE)
set(GLFW_PKG_CONFIG_REQUIRES "" CACHE STRING "" FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Vulkan Headers (since they are missing in the environment)
FetchContent_Declare(
    VulkanHeaders
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG        v1.3.275
)
FetchContent_MakeAvailable(VulkanHeaders)

# Find Vulkan Loader (Runtime)
find_library(VULKAN_LOADER NAMES vulkan libvulkan)

if (NOT VULKAN_LOADER)
    message(WARNING "Vulkan loader not found! You may need to install it.")
endif()

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h" "include/*.h")

add_executable(ProjectJules ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(ProjectJules PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(ProjectJules PRIVATE
    glfw
    glm::glm
    Vulkan::Headers
)

if (VULKAN_LOADER)
    target_link_libraries(ProjectJules PRIVATE ${VULKAN_LOADER})
endif()

# Compiler options
if(MSVC)
    target_compile_options(ProjectJules PRIVATE /W4 /WX)
else()
    target_compile_options(ProjectJules PRIVATE -Wall -Wextra -Wpedantic)
endif()
