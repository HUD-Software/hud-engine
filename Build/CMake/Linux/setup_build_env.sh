#!/bin/sh

#=========================
# Print the help function
#=========================
print_help() {
	echo
	echo "Syntax: setup_build_env.sh [arch] [compiler] [config]"
	echo
	echo " [generator] The generator used for the project"
	echo "    * Makefile"
	echo 
	echo " [arch] Set the architecture used for the project"
	echo "   * x86_64"
	echo "   * x86"
	echo
	echo " [compiler] Set the compiler used for the project"
	echo "   * GCC"
	echo "   * Clang"
	echo
	echo " [config] Configuration used for the project"
	echo "   * Debug"
	echo "   * Release"
	echo "   * DebugOptimized"
	echo
	exit 1
}

#========================
# Check input parameters
#========================
if [ "$2" != "x86_64" ] && [ "$2" != "x86" ]; then
echo "[arch] is not correct"
print_help
exit 1
fi


if [ "$3" != "GCC" ] && [ "$3" != "Clang" ]; then
echo "[compiler] is not correct"
print_help
exit 1
fi

if [ "$4" != "Debug" ] && [ "$4" != "Release" ] && [ "$4" != "DebugOptimized" ]; then
echo "[config] is not correct"
print_help
exit 1
fi

#============================
# Create the build directory
#============================
if [ "$1" = "Makefile" ]; then
export build_dir=""$current_dir"/../Generated/Unix Makefiles/$2/$3/$4"
else
echo "[generator] is not correct: "$1""
print_help
exit 1
fi

# Print the build directory to allow caller to retrieve it via redirection of output
echo $build_dir

# Create the build directory if not exist
if ! [ -d "$build_dir" ]; then
mkdir -p "$build_dir"
fi

