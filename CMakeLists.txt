cmake_minimum_required(VERSION 3.21)

project(VULKANAUDIO)

find_package(Vulkan REQUIRED)

set (CMAKE_CXX_STANDARD 17)

set(RTAUDIO_BUILD_STATIC_LIBS ON CACHE BOOL "Rtaudio Shared Lib" FORCE)
set(RTAUDIO_BUILD_TESTING OFF CACHE BOOL "Rtaudio Testing" FORCE)
set(RTAUDIO_TARGETNAME_UNINSTALL
    RTAUDIO_UNINSTALL CACHE STRING "Rtaudio Uninstall Target" FORCE)
add_subdirectory(rtaudio)

add_executable(VulkanAudio "Main.cpp")

set_target_properties(VulkanAudio PROPERTIES 
    DEBUG_POSTFIX _DEBUG 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(VulkanAudio PRIVATE ${Vulkan_INCLUDE_DIRS})

target_link_libraries(VulkanAudio PRIVATE ${Vulkan_LIBRARIES} rtaudio)