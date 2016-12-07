set(NAME logger)
add_library(${NAME} SHARED Logger.hpp LogPolicy.hpp LogWritter.hpp)
set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)