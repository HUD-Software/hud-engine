cmake_minimum_required(VERSION 3.18)

# Set the name of the target
set(target_name CityHash)

# Define a grouping for source files in IDE project generation
# source_files variable is a list all files source files
file( GLOB_RECURSE source_files *)
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

# Add SliceBy8 to the project
add_library(${target_name} STATIC ${source_files})

# Add HUDEngine compiler options
add_hudengine_cxx_compile_options(${target_name})
# Add HUDEngine compiler options
add_hudengine_cxx_compile_definitions(${target_name})
# Add HUDEngine linker options
add_hudengine_cxx_linker_static_options(${target_name})


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

#Disable some flags
set(MSVC_COMPILER_OPTIONS
	/wd4456 #declaration of 'identifier' hides previous local declaration 
	/wd4267 # 'var' : conversion from 'size_t' to 'type', possible loss of data
)
set(CLANG_COMPILER_OPTIONS 
	-Wno-shadow # declaration shadows a local variable
	-Wno-sign-conversion # implicit conversion changes signedness
)

target_compile_options(
		${target_name}
		PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:${MSVC_COMPILER_OPTIONS}>
		$<$<CXX_COMPILER_ID:Clang>:${CLANG_COMPILER_OPTIONS}>
)