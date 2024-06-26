cmake_minimum_required(VERSION 3.19)

project(VULKANAUDIO)

find_package(Vulkan REQUIRED)

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_MACOS_MVK")
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

set(SHADERS_IN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Compute/Shaders")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/Shaders")

file(MAKE_DIRECTORY ${SHADERS_OUT_DIR})
add_definitions(-DSHADER_BINARY_PATH=\"${SHADERS_OUT_DIR}/\")

file(GLOB SHADERS "${SHADERS_IN_DIR}/*.comp")
foreach(SHADER ${SHADERS})
	get_filename_component(SHADER_NAME ${SHADER} NAME)
	message("Adding to build: ${SHADER_NAME}")
	set(SHADER_OUT_NAME "${SHADERS_OUT_DIR}/${SHADER_NAME}.spv")
	list(APPEND SHADER_OUT_NAMES ${SHADER_OUT_NAME})
	add_custom_command(
		MAIN_DEPENDENCY ${SHADER}
		OUTPUT ${SHADER_OUT_NAME}
		COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${SHADER} "-o" ${SHADER_OUT_NAME}
	    VERBATIM)
endforeach()

add_custom_target(shaders DEPENDS ${SHADER_OUT_NAMES})
add_dependencies(VulkanAudio shaders)

set_target_properties(VulkanAudio PROPERTIES 
DEBUG_POSTFIX _DEBUG 
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON
)

target_include_directories(VulkanAudio PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(VulkanAudio PRIVATE ${Vulkan_LIBRARIES} rtaudio)