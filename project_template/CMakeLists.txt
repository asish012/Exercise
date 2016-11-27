cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")    # Use C++14
add_compile_options(-Wall -Wextra -Werror -Wpedantic)   # Enable all warnings

project(template_project)
subdirs(app_project)
subdirs(lib_project)
