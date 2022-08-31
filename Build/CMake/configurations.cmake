cmake_minimum_required(VERSION 3.18)

#Check whether the generator supports multiple configurations
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release DebugOptimized)
	set(CMAKE_CXX_FLAGS_DEBUGOPTIMIZED "")
	set(CMAKE_C_FLAGS_DEBUGOPTIMIZED  "")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUGOPTIMIZED "")
	set(CMAKE_SHARED_LINKER_FLAGS_MAINTAINER "")
endif()