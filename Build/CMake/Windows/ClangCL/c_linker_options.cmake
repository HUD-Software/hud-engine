cmake_minimum_required(VERSION 3.18)

if(MSVC)

# !add_hudengine_c_linker_static_options : Add HUD Engine compiler options for static target (.lib)
# 
# \arg:target The target
#
function(add_hudengine_c_linker_static_options target)
	set_target_properties(${target} PROPERTIES STATIC_LIBRARY_OPTIONS /NOLOGO /WX /ERRORREPORT:PROMPT)
endfunction()

# !add_hudengine_c_linker_shared_options : Add HUD Engine compiler options for shared target (.dll)
# 
# \arg:target The target
#
function(add_hudengine_c_linker_shared_options target)

		target_link_options( ${target} PRIVATE 
		-NOLOGO # Prevents display of the copyright message and version number
		-WX # Treat Linker Warnings as Errors
		-DYNAMICBASE # Specifies whether to generate an executable image that can be randomly rebased at load time by using the address space layout randomization (ASLR) feature of Windows that was first available in Windows Vista
		-NXCOMPAT # Indicates that an executable is compatible with the Windows Data Execution Prevention feature
		$<$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win32>:-SAFESEH> # Image has Safe Exception Handlers (only valid when linking for x86 targets)
		$<$<CONFIG:Debug>:
			/INCREMENTAL # Enable incremental linking
			/DEBUG:FULL # Moves all private symbol information from individual compilation products (object files and libraries) into a single PDB, and can be the most time-consuming part of the link. However, the full PDB can be used to debug the executable when no other build products are available, such as when the executable is deployed
			/OPT:NOREF # Keeps functions and data that are never referenced
			/OPT:NOICF # Disable COMDAT folding
		>

		$<$<CONFIG:DebugOptimized>:
			/INCREMENTAL:NO # Disable incremental linking
			/DEBUG:FULL # Moves all private symbol information from individual compilation products (object files and libraries) into a single PDB, and can be the most time-consuming part of the link. However, the full PDB can be used to debug the executable when no other build products are available, such as when the executable is deployed 
			/OPT:NOREF # Keeps functions and data that are never referenced
			/OPT:NOICF # Disable COMDAT folding
		>

		$<$<CONFIG:Release>:
			/INCREMENTAL:NO # Disable incremental linking
			/OPT:REF # Eliminates functions and data that are never referenced
			/OPT:ICF # Enable COMDAT folding. Redundant COMDATs can be removed from the linker output
		>
	)
	
endfunction()

# !add_hudengine_c_linker_exectuable_options : Add HUD Engine compiler options for shared target (.elf)
# 
# \arg:target The target
#elf
function(add_hudengine_c_linker_executable_options target)
	add_hudengine_c_linker_shared_options(${target})
endfunction()
	
endif()
