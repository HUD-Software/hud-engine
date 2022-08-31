cmake_minimum_required(VERSION 3.18)

# add_subdirectory(Catch2)

# set_target_properties(gtest PROPERTIES FOLDER Test/Framework/GoogleTest )
# set_target_properties(gtest PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})
# set_target_properties(gtest PROPERTIES PDB_OUTPUT_DIRECTORY ${OUT_DIR})

# set_target_properties(gtest_main PROPERTIES FOLDER Test/Framework/GoogleTest )
# set_target_properties(gtest_main PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})
# set_target_properties(gtest_main PROPERTIES PDB_OUTPUT_DIRECTORY ${OUT_DIR})


add_subdirectory(GoogleTest)

set_target_properties(gtest PROPERTIES FOLDER Test/Framework/GoogleTest )
set_target_properties(gtest PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})
set_target_properties(gtest PROPERTIES PDB_OUTPUT_DIRECTORY ${OUT_DIR})

set_target_properties(gtest_main PROPERTIES FOLDER Test/Framework/GoogleTest )
set_target_properties(gtest_main PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})
set_target_properties(gtest_main PROPERTIES PDB_OUTPUT_DIRECTORY ${OUT_DIR})

# Add HUDEngine compiler options
add_hudengine_cxx_compile_options(gtest)
add_hudengine_cxx_linker_executable_options(gtest)

add_hudengine_cxx_compile_options(gtest_main)
add_hudengine_cxx_linker_executable_options(gtest_main)

# Replace some compiler options with MSVC
if(MSVC)
target_compile_options( gtest PRIVATE
                        $<$<CXX_COMPILER_ID:Clang>: -Wno-microsoft-cast> # Do not warning microsoft cast
                    )
endif() 