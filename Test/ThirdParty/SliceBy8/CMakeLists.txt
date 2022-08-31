cmake_minimum_required(VERSION 3.18)

# Set the name of the target
set(target_name SliceBy8)

# Define a grouping for source files in IDE project generation
# source_files variable is a list all files source files
file( GLOB_RECURSE source_files *)
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

# Add SliceBy8 to the project
add_library(${target_name} STATIC ${source_files})

# Add HUDEngine compiler options
add_hudengine_c_compile_options(${target_name})
# Add HUDEngine compiler options
add_hudengine_c_compile_definitions(${target_name})
# Add HUDEngine linker options
add_hudengine_c_linker_static_options(${target_name})


#Set the target under Runtime folder
set_target_properties(${target_name} PROPERTIES FOLDER Test/ThirdParty)

# Set output directory
set_target_properties(${target_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})

# Set MSVC PDB
if(MSVC)
	set_pdb(${target_name} ${OUT_DIR})
endif()

# Include Interface directory to inclusion path
target_include_directories(${target_name} PUBLIC .)

