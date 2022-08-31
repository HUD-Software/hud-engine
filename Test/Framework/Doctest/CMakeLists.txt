cmake_minimum_required(VERSION 3.18)

# Set the name of the target
set(target_name Doctest)
file( GLOB_RECURSE source_files Doctest/*.h )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES Doctest/${source_files})
add_library(${target_name} INTERFACE )
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}) 

set_target_properties(Doctest PROPERTIES FOLDER Test/Framework/Doctest  )