cmake_minimum_required(VERSION 3.0.0)

project(Concurrency)

# Enable all warnings
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

# Use C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/inc)
file(GLOB SOURCES
#        "${PROJECT_SOURCE_DIR}/src/ConditionVariable.cpp"
#        "${PROJECT_SOURCE_DIR}/src/Async.cpp"
        "${PROJECT_SOURCE_DIR}/src/AsyncFile.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(${PROJECT_NAME})

add_custom_target(run
        COMMAND ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running ${PROJECT_NAME}..."
        )