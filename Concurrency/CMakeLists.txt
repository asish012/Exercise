cmake_minimum_required(VERSION 3.0.0)

project(Concurrency)

# Set Compiler
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# Enable all warnings
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

# Use C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O1 -fsanitize=address -fno-omit-frame-pointer")

SET(CMAKE_BUILD_TYPE Debug)

# Set output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/inc)
file(GLOB SOURCES
#        "${PROJECT_SOURCE_DIR}/src/ConditionVariable.cpp"
#        "${PROJECT_SOURCE_DIR}/src/Async.cpp"
#        "${PROJECT_SOURCE_DIR}/src/AsyncFile.cpp"
#        "${PROJECT_SOURCE_DIR}/src/LambdaObserver.cpp"
        "${PROJECT_SOURCE_DIR}/src/SqliteExercise.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCES})

#target_link_libraries(${PROJECT_NAME})

add_custom_target(run
        COMMAND ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running ${PROJECT_NAME}..."
        )