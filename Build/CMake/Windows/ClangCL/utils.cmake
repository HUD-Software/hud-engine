cmake_minimum_required(VERSION 3.18)

if(MSVC)

# Set the pdb name and output directory
# name : The name of the pdb file
# output_directory : The output directory of the pdb file
function(set_pdb name output_directory)
	set_target_properties(${name} PROPERTIES PDB_OUTPUT_DIRECTORY  ${output_directory})
	set_target_properties(${name} PROPERTIES PDB_NAME "${name}" PDB_NAME_DEBUG "${name}" COMPILE_PDB_NAME "${name}" COMPILE_PDB_NAME_DEBUG "${name}")
endfunction()

endif()
