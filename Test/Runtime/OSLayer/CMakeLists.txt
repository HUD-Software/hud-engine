cmake_minimum_required(VERSION 3.18)

# Set the name of the target
set(target_name Test_OSLayer)

# Define a grouping for source files in IDE project generation
# source_files variable is a list all files in Implementation directory
file( GLOB_RECURSE source_files * )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${source_files})

add_executable(${target_name} ${source_files})

# Add the precompiled header
target_include_directories(${target_name} PRIVATE .)
target_precompile_headers(${target_name} PRIVATE Precompiled.h)

add_test(NAME OSLayer COMMAND ${target_name} --gtest_output=xml:../../../TestReports/OSLayer_test_report.xml --extra-verbose --gtest_break_on_failure)

# Add HUDEngine compiler options
add_hudengine_cxx_compile_options(${target_name})
# Add HUDEngine compiler options
add_hudengine_cxx_compile_definitions(${target_name})
# Add HUDEngine linker options
add_hudengine_cxx_linker_executable_options(${target_name})

# assertion must abort tests
target_compile_definitions( ${target_name} PRIVATE HD_ABORT_ON_ASSERT)

# Set the target under 'Test' folder
set_target_properties(${target_name} PROPERTIES FOLDER Test )

# Set binary output files
set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR})
set_target_properties(${target_name} PROPERTIES PDB_OUTPUT_DIRECTORY ${OUT_DIR})

# Add OSLayer dependency
add_dependencies( ${target_name} OSLayer)
target_link_libraries(${target_name} PRIVATE OSLayer)

# Add Test Framework dependency
add_dependencies( ${target_name} gtest)
target_link_libraries(${target_name} PRIVATE gtest)

#add ThirdParty's dependencies
add_dependencies( ${target_name} SliceBy8)
target_link_libraries( ${target_name} PRIVATE SliceBy8)
add_dependencies( ${target_name} CityHash)
target_link_libraries( ${target_name} PRIVATE CityHash)
