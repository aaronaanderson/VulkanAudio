cmake_minimum_required(VERSION 3.21)

project(VULKANAUDIO)

find_package(Vulkan REQUIRED)

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_MACOS_MVK")# -DVK_KHR_portability_subset")
endif()

set (CMAKE_CXX_STANDARD 17)

set(RTAUDIO_BUILD_STATIC_LIBS ON CACHE BOOL "Rtaudio Shared Lib" FORCE)
set(RTAUDIO_BUILD_TESTING OFF CACHE BOOL "Rtaudio Testing" FORCE)
set(RTAUDIO_TARGETNAME_UNINSTALL
    RTAUDIO_UNINSTALL CACHE STRING "Rtaudio Uninstall Target" FORCE)
add_subdirectory(rtaudio)

add_executable(VulkanAudio 
    "Main.cpp"
    "Compute/VulkanTools.cpp")

set_target_properties(VulkanAudio PROPERTIES 
    DEBUG_POSTFIX _DEBUG 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(VulkanAudio PRIVATE ${Vulkan_INCLUDE_DIRS})

target_link_libraries(VulkanAudio PRIVATE ${Vulkan_LIBRARIES} rtaudio)