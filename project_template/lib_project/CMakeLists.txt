set(NAME mylib)
include_directories(${template_project_SOURCE_DIR}/lib_project/inc)
add_library(${NAME} src/mylib.cpp)