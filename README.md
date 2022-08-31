# HUDEngine
HUDEngine is a multiplatform 2D/3D engine

[![pipeline status](https://gitlab.com/hud-software/hudengine/badges/dev/pipeline.svg)](https://gitlab.com/hud-software/hudengine/-/pipelines)

# GENERATION
HUDEngine use [CMake](https://cmake.org/) to generate project file that can be compiled later and to run tests

## Windows
To generate project on Windows you need to install [Visual Studio](https://visualstudio.microsoft.com/fr/vs/) first.
HUDEngine only support the following version of Visual Studio:
- Visual Studio 2019 Professional
- Visual Studio 2019 Community

Once Visual Studio is installed, you can generate a Visual Studio project. The generation must be done only once except if you add/remove/modify files that need to be used during the generation process.
To generate a project you need to call the script `Build\CMake\generate.bat` like this `generate.bat [generator] [arch]`

HUDEngine provides 2 generator on Windows:
- Visual Studio Solution : Generate a Visual Studio 2019 solution with `[generator]`=`"Visual Studio 2019"`
- NMake Makefiles : Generate a NMake Makefiles with `[generator]`=`"NMake Visual Studio 2019"`

HUDEngine provides 4 architectures on Windows:
- 32 bits x86 architecture with `[arch]`=`Win32`
- 64 bts x86 architecture with `[arch]`=`Win64`
- 32 bits ARM architecture with `[arch]`=`ARM32`
- 64 bits ARM architecture with `[arch]`=`ARM64`


# COMPILATION
HUDEngine use [CMake](https://cmake.org/) only for the generation and test.

## Windows
The compilation must be done with the same argument that was provided during the generation plus a configuration `[config]`.
To compile a project you need to call the script `Build\CMake\build.bat` like this `generate.bat [generator] [arch] [config]`

HUDEngine provides 3 configurations on Windows:
- Compile the engine with debug informations but without optimisations with `[config]`=`Debug`
- Compile the engine without debug informations but with optimisations with `[config]`=`Release`
- Compile the engine with debug informations with optimisations with `[config]`=`DebugOptimized`

Note that depending of the generator the compilation is done with different compilation tools:
- `Visual Studio 2019` generator use [MSBuild](https://docs.microsoft.com/fr-fr/visualstudio/msbuild).
- `NMake Visual Studio 2019` generator use [NMake](https://docs.microsoft.com/fr-fr/cpp/build/reference/nmake-reference).


# TEST
HUDEngine use [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) to run HUDEngine tests.

## Windows
To test the HUDEngine you need to call the script `Build\CMake\test.bat` like this `test.bat [generator] [arch] [config] [test]`
`[generator]` `[arch]` and `[config]` is respectivly the generator, the architecture and the configuration used for the compilation.
The optional `[test]` is used to select which test you want to run that matching regular expression given in `[test]`. Run all test if empty.