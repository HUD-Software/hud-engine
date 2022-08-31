#!/bin/sh

#=========================
# Print the help function
#=========================
print_help() {
	echo
	echo "Syntax: generate_makefile.sh [arch] [compiler] [config]"
	echo
	echo " [arch] Set the architecture used to generate the project"
	echo "   * x86_64"
	echo "   * x86"
	echo
	echo " [compiler] Set the compiler used to generate the project"
	echo "   * GCC"
	echo "   * Clang"
	echo
	echo " [config] Configuration used to generate the project"
	echo "   * Debug"
	echo "   * Release"
	echo "   * DebugOptimized"
	echo
	exit 1
}

#========================
# Check input parameters
#========================
if [ "$1" != "x86_64" ] && [ "$1" != "x86" ]; then
echo "[arch] is not correct: "$1""
print_help
exit 1
fi


if [ "$2" = "GCC" ]; then
export CXX="/usr/bin/g++"
export CC="/usr/bin/gcc"
elif [ "$2" = "Clang" ]; then
export CXX=/usr/bin/clang++
export CC=/usr/bin/clang
else
echo "[compiler] is not correct"
print_help
exit 1
fi

if [ "$3" = "Debug" ] || [ "$3" = "Release" ] || [ "$3" = "DebugOptimized" ]; then
CMAKE_BUILD_TYPE=$3
else
echo "[config] is not correct"
print_help
exit 1
fi

#=========================
# Generate Unix Makefiles
#=========================
export current_dir=$(pwd)
export build_dir=$(./setup_build_env.sh Makefile "$1" "$2" "$3")
if [ $? -eq 0 ]; then
(
	cd "$build_dir"
	cmake ""$current_dir"/../../.." -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE
)
fi
exit $?
