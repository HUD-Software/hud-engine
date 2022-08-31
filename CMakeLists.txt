cmake_minimum_required(VERSION 3.18)
# If operating system for which CMake to build is Windows set SDK version to 10
set(CMAKE_SYSTEM_VERSION 10.0)

# Set project name ( VS Solution name ) 
project(HUDEngine
		DESCRIPTION "HUD Engine"
		LANGUAGES C CXX
)

# Add include path for cmake include()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Build/CMake")

# Use the FOLDER target property to organize targets into folder
# Subdirectory can be place in folders by setting target FOLDER property
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Prevent ZERO_CHECK generation
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# Compilation constants
set(OUT_DIR Bin/${CMAKE_BUILD_TYPE})

# List possible configurations
include(configurations)

# Enable unity build
# include(unity_build)

# Set the path the additional modules
if(MSVC)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_MODULE_PATH}/Windows/ClangCL")
	else()
		set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_MODULE_PATH}/Windows/MSVC")
	endif()
	include(utils)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_MODULE_PATH}/Linux/Clang")
endif()

# Include modules
include(c_compile_options)
include(c_linker_options)
include(cxx_compile_options)
include(cxx_linker_options)

# Add targets
add_subdirectory(Sources/Runtime/OSLayer)

# Add tests
enable_testing()
add_subdirectory(Test Test)
