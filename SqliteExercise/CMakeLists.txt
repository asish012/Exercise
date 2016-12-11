cmake_minimum_required(VERSION 3.0.0)

project(Concurrency)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

set(FILENAME_DEDUCTION_FLAG "-D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FILENAME_DEDUCTION_FLAG}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")

SET(CMAKE_BUILD_TYPE Debug)

find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
if(NOT SQLITE3_INCLUDE_DIR)
    message(SEND_ERROR "Failed to find sqlite3.h")
endif()
find_library(SQLITE3_LIBRARY sqlite3)
if(NOT SQLITE3_LIBRARY)
    message(SEND_ERROR "Failed to find the sqlite3 library")
endif()

find_package(Threads REQUIRED)

# set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/log)
add_definitions(-DDIR_LOG="${CMAKE_SOURCE_DIR}/log")

include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/logger)

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${SQLITE3_LIBRARY}
)

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running ${PROJECT_NAME}..."
)
