cmake_minimum_required(VERSION 3.27.4)

project("CoffeeBrowser" VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    add_definitions(-D _CRT_SECURE_NO_WARNINGS)
endif()

# Gather source and header files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

# Add subdirectories for dependencies
add_subdirectory("lib/glfw")
add_subdirectory("lib/glew-cmake")

# CEF Setup
set(CEF_ROOT "${PROJECT_SOURCE_DIR}/lib/cef")
include_directories(${CEF_ROOT}/include)
link_directories(${CEF_ROOT}/Release)
link_directories(${CEF_ROOT}/Debug)

# Define the executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

# Link against dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC libglew_static)

# Link against CEF libraries
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC libcef libcef_dll_wrapper)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC cef cef_dll_wrapper)
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC 
    "${PROJECT_SOURCE_DIR}/lib/glfw/include"
    "${PROJECT_SOURCE_DIR}/lib/glew-cmake/include"
    "${PROJECT_SOURCE_DIR}/src"
)

# Copy CEF resources to the build directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CEF_ROOT}/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CEF_ROOT}/Release $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

# Add additional compile options
add_compile_options(/bigobj)

# Set the startup project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "CoffeeBrowser")
