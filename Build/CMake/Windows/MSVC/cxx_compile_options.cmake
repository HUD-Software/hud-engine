cmake_minimum_required(VERSION 3.18)

if(MSVC)

# !add_hudengine_cxx_compile_options : Add HUD Engine compiler options to a target
# 
# \arg:target The target
#
function(add_hudengine_cxx_compile_options target)

	set(MSVC_HUDENGINE_COMPILER_OPTIONS
		/std:c++latest # Enable supported C and C++ language features from the latest version of the C or C++ language standard
		/utf-8  # Set Source and Executable character sets to UTF-8
		/W4 # Displays level 1, level 2, and level 3 warnings, and all level 4 (informational) warnings that aren't off by default
		/WX # Treats all compiler warnings as errors
		/nologo # Suppresses the display of the copyright banner when the compiler starts up and display of informational messages during compiling
		/diagnostics:caret # Specify the display of error and warning location information (caret includes the column where the issue was found and places a caret (^) under the location in the line of code where the issue was detected.)
		/permissive- # Specify standards-conforming compiler behavior
		/Zc:alignedNew # Enable support for C++17 over-aligned new
		/Zc:auto # Tell the compiler to use the revised meaning of the auto keyword
		/Zc:__cplusplus # Enables the __cplusplus preprocessor macro to report an updated value for recent C++ language standards support
		/Zc:externConstexpr # Tells the compiler to conform to the C++ standard and allow external linkage for constexpr variables
		/Zc:hiddenFriend # Specifies the compiler conforms to the C++ standard treatment of hidden friend functions or function templates
		/Zc:implicitNoexcept # The compiler adds an implicit noexcept exception specifier to compiler-defined special member functions and to user-defined destructors and deallocators
		/Zc:inline # Removes unreferenced data or functions that are COMDATs, or that only have internal linkage. This optimization simplifies some of the work the linker does in release builds and can significantly reduce .obj file size and improve linker speeds
		/Zc:noexceptTypes # The compiler conforms to the C++17 standard and treats throw() as an alias for noexcept, removes throw(type-list) and throw(...), and allows certain types to include noexcept
		#(Reactivate when C5105 will be fixed) /Zc:preprocessor # Enables a token-based preprocessor that conforms to C99 and C++11 and later standards
		/Zc:referenceBinding # The compiler doesn't allow a non-const lvalue reference to bind to a temporary
		/Zc:rvalueCast # The compiler correctly identifies an rvalue reference type as the result of a cast operation. Its behavior conforms to the C++11 standard
		/Zc:sizedDealloc # Tells the compiler to preferentially call global operator delete or operator delete[] functions that have a second parameter of type size_t when the size of the object is available. These functions may use the size_t parameter to optimize deallocator performance
		/Zc:strictStrings # The compiler requires strict const-qualification conformance for pointers initialized by using string literals
		/Zc:ternary # Enable enforcement of C++ Standard rules for the types and const or volatile (cv) qualification of the second and third operands in a conditional operator expression
		/Zc:threadSafeInit- # Tells the compiler to NOT initialize static local (function scope) variables in a thread-safe way, eliminating the need for manual synchronization
		/Zc:throwingNew # Tells the compiler to assume that all linked implementations of operator new and custom allocators conform to the C++ standard and throw on allocation failure
		/Zc:trigraphs- # Disable trigraphs
		/Zc:wchar_t # Parse wchar_t as a built-in type according to the C++ standard
		#$<$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win32>:/Gr> # Specifies the __fastcall calling convention for all functions except C++ member functions, functions named main, and functions that are marked __cdecl, __stdcall, or __vectorcall
		/GR- # Disable Runrime Type Informations (RTTI)
		/openmp- # Causes the compiler to NOT process #pragma omp directives in support of OpenMP
		/Gy # Enable Function-Level Linking. Allows the compiler to package individual functions in the form of packaged functions (COMDATs)
		/FC # Full Path of Source Code File in Diagnostics. Causes the compiler to display the full path of source code files passed to the compiler in diagnostics
		/GF # Eliminate Duplicate Strings. Enables the compiler to create a single copy of identical strings in the program image and in memory during execution. This is an optimization called string pooling that can create smaller programs.
		/fp:fast # Specify floating-point behavior. Allows the compiler to reorder, combine, or simplify floating-point operations to optimize floating-point code for speed and space
		/fp:except- # Specify floating-point behavior. Disable floating-point exceptions ( Invalid operation, Division by zero, Overflow, Underflow, Inexact calculation )
		/arch:AVX2 # Enables the use of Intel Advanced Vector Extensions 2 instructions
		/GT # Supports fiber safety for data allocated using static thread-local storage, that is, data allocated with __declspec(thread)
		/bigobj # Increases the number of sections that an object file can contain
		# Options not allowed when compiling with NMake
		$<$<NOT:$<STREQUAL:${CMAKE_MAKE_PROGRAM},nmake>>: 
			/Qpar- # Disable the Auto-Parallelizer feature of the compiler to automatically parallelize loops in your code
			/MP # Build with Multiple Processes
		>
		# Win32 specific compiler options
		$<$<AND:$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win32>,$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win64>>:
			/arch:AVX2 # Enables the use of Intel Advanced Vector Extensions 2 instructions
		>
		# ARM specific compiler options
		$<$<AND:$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},ARM32>,$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},ARM64>>:
			/arch:VFPv4
		>
		# Debug specific compiler options
		$<$<CONFIG:Debug>:
			/MDd  # Defines _DEBUG, _MT, and _DLL and causes the application to use the debug multithread-specific and DLL-specific version of the run-time library. It also causes the compiler to place the library name MSVCRTD.lib into the .obj file
			/Zi # Produces a separate PDB file that contains all the symbolic debugging information for use with the debugger. The debugging information isn't included in the object files or executable, which makes them much smaller
			/Od # Turns off all optimizations in the program and speeds compilation
			/Oi # Replaces some function calls with intrinsic or otherwise special forms of the function that help your application run faster
			/RTC1 # Enable the run-time error checks feature, in conjunction with the runtime_checks pragma. ( Enables stack frame run-time error checking and Reports when a variable is used without having been initialized )
			/sdl # Enables recommended Security Development Lifecycle (SDL) checks. These checks change security-relevant warnings into errors, and set additional secure code-generation features
			/GS # Detects some buffer overruns that overwrite a function's return address, exception handler address, or certain types of parameters
			/guard:cf # enable security flags
		>
		# DebugOptimized specific compiler options
		$<$<CONFIG:DebugOptimized>:
			/MD # Causes the application to use the multithread-specific and DLL-specific version of the run-time library. Defines _MT and _DLL and causes the compiler to place the library name MSVCRT.lib into the .obj file
			/Zi  # Produces a separate PDB file that contains all the symbolic debugging information for use with the debugger. The debugging information isn't included in the object files or executable, which makes them much smaller
			/Ox # Enable Most Speed Optimizations. Same as using the following options in combination /Ob2 /Oi /Ot /Oy
			/GL # Enables whole program optimization.
			/sdl # Enables recommended Security Development Lifecycle (SDL) checks. These checks change security-relevant warnings into errors, and set additional secure code-generation features
			/GS # Disables detection of some buffer overruns that overwrite a function's return address, exception handler address, or certain types of parameters
			/guard:cf # enable security flags
		>
		# Release specific compiler options
		$<$<CONFIG:Release>:
			/MD # Causes the application to use the multithread-specific and DLL-specific version of the run-time library. Defines _MT and _DLL and causes the compiler to place the library name MSVCRT.lib into the .obj file
			/Ox # Enable Most Speed Optimizations. Same as using the following options in combination /Ob2 /Oi /Ot /Oy
			/GL # Enables whole program optimization.
			/sdl- # Disables recommended Security Development Lifecycle (SDL) checks. These checks change security-relevant warnings into errors, and set additional secure code-generation features
			/GS- # Disables detection of some buffer overruns that overwrite a function's return address, exception handler address, or certain types of parameters
			/guard:cf- # disable security flags
		>
	)

 	set(CLANG_HUDENGINE_COMPILER_OPTIONS
		-std:c++latest # Enable supported C and C++ language features from the latest version of the C or C++ language standard
		-utf-8 # Set Source and Executable character sets to UTF-8
		-W4  # Displays level 1, level 2, and level 3 warnings, and all level 4 (informational) warnings that aren't off by default
		-WX # Treats all compiler warnings as errors
		-nologo # Suppresses the display of the copyright banner when the compiler starts up and display of informational messages during compiling
		-diagnostics:caret # Specify the display of error and warning location information (caret includes the column where the issue was found and places a caret (^) under the location in the line of code where the issue was detected.)
		-permissive- # Specify standards-conforming compiler behavior 
		-Zc:alignedNew # Enable support for C++17 over-aligned new
		-Zc:sizedDealloc # Tells the compiler to preferentially call global operator delete or operator delete[] functions that have a second parameter of type size_t when the size of the object is available. These functions may use the size_t parameter to optimize deallocator performance
		-Zc:strictStrings # The compiler requires strict const-qualification conformance for pointers initialized by using string literals
		-Zc:threadSafeInit- # Tells the compiler to NOT initialize static local (function scope) variables in a thread-safe way, eliminating the need for manual synchronization
		-Zc:trigraphs- # Disable trigraphs
		-Zc:char8_t # Enable char8_t from C++2a
		#$<$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win32>:/Gr> # Specifies the __fastcall calling convention for all functions except C++ member functions, functions named main, and functions that are marked __cdecl, __stdcall, or __vectorcall
		-GR- # Disable Runrime Type Informations (RTTI)
		-openmp- # Causes the compiler to NOT process #pragma omp directives in support of OpenMP
		-Gy # Enable Function-Level Linking. Allows the compiler to package individual functions in the form of packaged functions (COMDATs)
		-FC # Full Path of Source Code File in Diagnostics. Causes the compiler to display the full path of source code files passed to the compiler in diagnostics
		-GF # Eliminate Duplicate Strings. Enables the compiler to create a single copy of identical strings in the program image and in memory during execution. This is an optimization called string pooling that can create smaller programs.
		-fp:fast # Specify floating-point behavior. Allows the compiler to reorder, combine, or simplify floating-point operations to optimize floating-point code for speed and space
		-fp:except- # Specify floating-point behavior. Disable floating-point exceptions ( Invalid operation, Division by zero, Overflow, Underflow, Inexact calculation )
		-Qvec # Enable the loop vectorization passes
		-Wshadow -Wshadow-field -Wshadow-field-in-constructor # Enable warnings when variable shadows another variable
		-Wdouble-promotion # Enable warning : implicit conversion increases floating-point precision: A to B
		-Wformat=2 # Enable warning : format string is not a string literal, format string is not a string literal (potentially insecure), 
		-Wfloat-conversion # Enable warning : implicit conversion turns floating-point number into integer: A to B
		-Wsign-compare # comparison of integers of different signs: A and B
		-Wsign-conversion # implicit conversion changes signedness: A to B
		-Wno-format-nonliteral # format string is not a string literal
		# Options not allowed when compiling with NMake
		$<$<NOT:$<STREQUAL:${CMAKE_MAKE_PROGRAM},nmake>>: 
			-Qpar- # Disable the Auto-Parallelizer feature of the compiler to automatically parallelize loops in your code
			-MP # Build with Multiple Processes
		>
		# Win32 specific compiler options
		$<$<AND:$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win32>,$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},Win64>>:
			-arch:AVX2 # Enables the use of Intel Advanced Vector Extensions 2 instructions
		>
		# ARM specific compiler options
		$<$<AND:$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},ARM32>,$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},ARM64>>:
			-arch:VFPv4
		>
		# Debug specific compiler options
		$<$<CONFIG:Debug>:
			-MDd  # Defines _DEBUG, _MT, and _DLL and causes the application to use the debug multithread-specific and DLL-specific version of the run-time library. It also causes the compiler to place the library name MSVCRTD.lib into the .obj file
			-Zi # Produces a separate PDB file that contains all the symbolic debugging information for use with the debugger. The debugging information isn't included in the object files or executable, which makes them much smaller
			-Od # Turns off all optimizations in the program and speeds compilation
			-Oi # Replaces some function calls with intrinsic or otherwise special forms of the function that help your application run faster
			-RTC1 # Enable the run-time error checks feature, in conjunction with the runtime_checks pragma. ( Enables stack frame run-time error checking and Reports when a variable is used without having been initialized )
			-sdl # Enables recommended Security Development Lifecycle (SDL) checks. These checks change security-relevant warnings into errors, and set additional secure code-generation features
			-GS # Detects some buffer overruns that overwrite a function's return address, exception handler address, or certain types of parameters
			-guard:cf # enable security flags
		>
		# DebugOptimized specific compiler options
		$<$<CONFIG:DebugOptimized>:
			-MD # Causes the application to use the multithread-specific and DLL-specific version of the run-time library. Defines _MT and _DLL and causes the compiler to place the library name MSVCRT.lib into the .obj file
			-Zi  # Produces a separate PDB file that contains all the symbolic debugging information for use with the debugger. The debugging information isn't included in the object files or executable, which makes them much smaller
			-Ox # Enable Most Speed Optimizations. Same as using the following options in combination /Ob2 /Oi /Ot /Oy
			#-flto=thin # Enables whole program optimization.
			-sdl # Enables recommended Security Development Lifecycle (SDL) checks. These checks change security-relevant warnings into errors, and set additional secure code-generation features
			-GS # Disables detection of some buffer overruns that overwrite a function's return address, exception handler address, or certain types of parameters
			-guard:cf # enable security flags
		>
		# Release specific compiler options
		$<$<CONFIG:Release>:
			-MD # Causes the application to use the multithread-specific and DLL-specific version of the run-time library. Defines _MT and _DLL and causes the compiler to place the library name MSVCRT.lib into the .obj file
			-Ox # Enable Most Speed Optimizations. Same as using the following options in combination /Ob2 /Oi /Ot /Oy
			-flto=thin # Enables whole program optimization.
			-sdl- # Disables recommended Security Development Lifecycle (SDL) checks. These checks change security-relevant warnings into errors, and set additional secure code-generation features
			-GS- # Disables detection of some buffer overruns that overwrite a function's return address, exception handler address, or certain types of parameters
			-guard:cf- # disable security flags
		>
	)


	target_compile_options(
		${target}
		PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:${MSVC_HUDENGINE_COMPILER_OPTIONS}>
		$<$<CXX_COMPILER_ID:Clang>:${CLANG_HUDENGINE_COMPILER_OPTIONS}>
	)

endfunction()


# !add_hudengine_cxx_compile_definitions : Add HUD Engine compiler definition to a target
# 
# \arg:target The target
#
function(add_hudengine_cxx_compile_definitions target)
	target_compile_definitions(
		${target}
		PRIVATE
		_HAS_EXCEPTIONS=0
		_CRT_SECURE_NO_WARNINGS
		_UNICODE
		UNICODE
		HD_GLOBAL_NAMESPACE_TYPES
		# Debug specific compiler flags
		$<$<CONFIG:Debug>:HD_DEBUG>
		# Release specific compiler flags
		$<$<CONFIG:Release>:HD_RELEASE>
		# DebugOptimized specific compiler flags
		$<$<CONFIG:DebugOptimized>:HD_DEBUGOPTIMIZED>
	)
endfunction()


endif()