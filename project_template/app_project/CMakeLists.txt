set(NAME project_template)

include_directories(${template_project_SOURCE_DIR}/app_project/inc)
include_directories(${template_project_SOURCE_DIR}/lib_project/inc)     # lib_project(mylib) is assumed to be a required library of app_project
link_directories(${template_project_SOURCE_DIR}/lib_project/src)

set(EXECUTABLE_OUTPUT_PATH ${template_project_SOURCE_DIR}/build/bin)    # binary output directory
add_executable(${NAME} src/main.cpp)

target_link_libraries(${NAME} mylib)                                    # mylib is prepared in lib_project's CMakefile

add_custom_target(run COMMAND ${NAME} COMMENT "Running ${NAME} ...")    # enable: make run
