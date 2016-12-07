cmake_minimum_required(VERSION 3.0.0)

project(Concurrency)

set(CMAKE_CXX_COMPILER /usr/bin/g++)

add_compile_options(-Wall -Wextra -Werror -Wpedantic)

set(FILENAME_DEDUCTION_FLAG "-D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O1 -fsanitize=address -fno-omit-frame-pointer ${FILENAME_DEDUCTION_FLAG}")

SET(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Doesn't make sense to make a shared lib for logger,
# Because our "logger" is header only, and we have to include logger directory in "include_directories" anyways.
add_subdirectory(logger)
set(LOGGER logger)

include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${PROJECT_SOURCE_DIR}/logger)

file(GLOB SOURCES
#        "${PROJECT_SOURCE_DIR}/src/ConditionVariable.cpp"
#        "${PROJECT_SOURCE_DIR}/src/Async.cpp"
#        "${PROJECT_SOURCE_DIR}/src/AsyncFile.cpp"
#        "${PROJECT_SOURCE_DIR}/src/LambdaObserver.cpp"
        "${PROJECT_SOURCE_DIR}/src/SqliteExercise.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LOGGER})

add_custom_target(run
        COMMAND ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running ${PROJECT_NAME}..."
        )