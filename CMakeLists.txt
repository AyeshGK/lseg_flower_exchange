# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# project name
project( flower_exchange )

# flags

# files

# include
include_directories( ./include ./src  )

# target
add_executable( binary ./src/main.cpp )

# external libs - 3rd party libs
add_subdirectory( ./libs/Logger )
target_link_libraries( binary logger )

# add_subdirectory( ./libs/Randomize )
# target_link_libraries( binary randomize )

add_library(randomize STATIC IMPORTED)
set_property(TARGET randomize PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/Randomize/librandomize.a)
target_link_libraries( binary randomize )