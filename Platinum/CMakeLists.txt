cmake_minimum_required(VERSION 3.25)
project(Platinum C CXX OBJC OBJCXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(fetchcontent)

fetchcontent_declare(
        glfw3
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
        FIND_PACKAGE_ARGS
)
fetchcontent_declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.1.1
        FIND_PACKAGE_ARGS
)
fetchcontent_makeavailable(glfw3 fmt)

#find_package(glfw3 CONFIG REQUIRED)

if (APPLE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apple/bin/lib PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apple/bin/lib PARENT_SCOPE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apple/bin PARENT_SCOPE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apple/bin/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apple/bin/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apple/bin)
#elseif (WIN32)
#elseif (UNIX)
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib PARENT_SCOPE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib PARENT_SCOPE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin PARENT_SCOPE)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    add_compile_definitions(LIB_PATH="")
endif ()

#set_property(GLOBAL PROPERTY CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set_property(GLOBAL PROPERTY CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set_property(GLOBAL PROPERTY CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(Platinum STATIC Platinum.h src/Application.cpp src/Application.h src/Renderer.h src/Window.h src/event/Event.h src/event/WindowEvent.h src/event/MouseEvents.h src/event/KeyEvent.h)

add_subdirectory(src/platform)

target_precompile_headers(Platinum PUBLIC Platinum_pch.h)
target_include_directories(Platinum PUBLIC src src/event)
target_link_libraries(Platinum PUBLIC glfw fmt::fmt)

add_compile_definitions(LIB_PATH=lib/)
