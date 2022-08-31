cmake_minimum_required(VERSION 3.18)

# Set the name of the target
set(target_name OSLayer)

# Define a grouping for source files in IDE project generation
# source_files variable is a list all files in Implementation and Interface directory
set( implementations
	Implementation/OSLayer/Hash/Crc32.cpp
)

#Linux implementations
if(UNIX AND NOT APPLE)
set( implementations ${implementations}
	Implementation/OSLayer/OSLinux/LinuxDebugger.cpp
)
endif()

set( interfaces
	Interface/OSLayer/Allocators/AlignedHeapAllocator.h
	Interface/OSLayer/Allocators/Allocation.h
	Interface/OSLayer/Allocators/HeapAllocator.h
	Interface/OSLayer/Containers/AlignedBuffer.h
	Interface/OSLayer/Containers/Array.h
	Interface/OSLayer/Containers/Optional.h
	Interface/OSLayer/Containers/Pair.h
	Interface/OSLayer/Containers/SharedPointer.h
	Interface/OSLayer/Containers/Tuple.h
	Interface/OSLayer/Containers/TupleElement.h
	Interface/OSLayer/Containers/TupleSize.h
	Interface/OSLayer/Containers/UniquePointer.h
	Interface/OSLayer/Hash/CityHash.h
	Interface/OSLayer/Hash/Crc32.h
	Interface/OSLayer/Iterators/RandomAccessIterator.h
	Interface/OSLayer/OSCommon/CommonAtomics.h
	Interface/OSLayer/OSCommon/CommonChar.h
	Interface/OSLayer/OSCommon/CommonCString.h
	Interface/OSLayer/OSCommon/CommonMemory.h
	Interface/OSLayer/OSCommon/CommonTypes.h
	Interface/OSLayer/OSCommon/CommonUuid.h
	Interface/OSLayer/OSLinux/LinuxAtomics.h
	Interface/OSLayer/OSLinux/LinuxChar.h
	Interface/OSLayer/OSLinux/LinuxCString.h
	Interface/OSLayer/OSLinux/LinuxDebugger.h
	Interface/OSLayer/OSLinux/LinuxMemory.h
	Interface/OSLayer/OSLinux/LinuxTypes.h
	Interface/OSLayer/OSLinux/LinuxUuid.h
	Interface/OSLayer/OSWindows/WindowsAPI.h
	Interface/OSLayer/OSWindows/WindowsAtomics.h
	Interface/OSLayer/OSWindows/WindowsAtomicsIntel.h
	Interface/OSLayer/OSWindows/WindowsChar.h
	Interface/OSLayer/OSWindows/WindowsCString.h
	Interface/OSLayer/OSWindows/WindowsDebugger.h
	Interface/OSLayer/OSWindows/WindowsMemory.h
	Interface/OSLayer/OSWindows/WindowsTypes.h
	Interface/OSLayer/OSWindows/WindowsUuid.h
	Interface/OSLayer/Templates/BitCast.h
	Interface/OSLayer/Templates/Declval.h
	Interface/OSLayer/Templates/DefaultDeleter.h
	Interface/OSLayer/Templates/Equal.h
	Interface/OSLayer/Templates/Forward.h
	Interface/OSLayer/Templates/Greater.h
	Interface/OSLayer/Templates/GreaterEqual.h
	Interface/OSLayer/Templates/IntegerSequence.h
	Interface/OSLayer/Templates/Less.h
	Interface/OSLayer/Templates/LessEqual.h
	Interface/OSLayer/Templates/LexicographicalCompare.h
	Interface/OSLayer/Templates/Max.h
	Interface/OSLayer/Templates/Min.h
	Interface/OSLayer/Templates/Move.h
	Interface/OSLayer/Templates/SelectDeleterPointerType.h
	Interface/OSLayer/Templates/Swap.h
	Interface/OSLayer/Traits/AddConst.h
	Interface/OSLayer/Traits/AddCV.h
	Interface/OSLayer/Traits/AddLValueReference.h
	Interface/OSLayer/Traits/AddPointer.h
	Interface/OSLayer/Traits/AddRValueReference.h
	Interface/OSLayer/Traits/AddVolatile.h
	Interface/OSLayer/Traits/And.h
	Interface/OSLayer/Traits/ApplyCV.h
	Interface/OSLayer/Traits/CommonType.h
	Interface/OSLayer/Traits/Conditional.h
	Interface/OSLayer/Traits/Decay.h
	Interface/OSLayer/Traits/EnableIf.h
	Interface/OSLayer/Traits/Extent.h
	Interface/OSLayer/Traits/HasUniqueObjectRepresentations.h
	Interface/OSLayer/Traits/IntegralConstant.h
	Interface/OSLayer/Traits/IsAnyTypeIn.h
	Interface/OSLayer/Traits/IsArithmetic.h
	Interface/OSLayer/Traits/IsArray.h
	Interface/OSLayer/Traits/IsAssignable.h
	Interface/OSLayer/Traits/IsBaseOf.h
	Interface/OSLayer/Traits/IsBitwiseComparable.h
	Interface/OSLayer/Traits/IsBitwiseConvertible.h
	Interface/OSLayer/Traits/IsBitwiseCopyAssignable.h
	Interface/OSLayer/Traits/IsBitwiseCopyConstructible.h
	Interface/OSLayer/Traits/IsBitwiseMoveAssignable.h
	Interface/OSLayer/Traits/IsBitwiseMoveConstructible.h
	Interface/OSLayer/Traits/IsBool.h
	Interface/OSLayer/Traits/IsBoundedArray.h
	Interface/OSLayer/Traits/IsClass.h
	Interface/OSLayer/Traits/IsComparableWithEqual.h
	Interface/OSLayer/Traits/IsComparableWithGreater.h
	Interface/OSLayer/Traits/IsComparableWithGreaterEqual.h
	Interface/OSLayer/Traits/IsComparableWithLess.h
	Interface/OSLayer/Traits/IsComparableWithLessEqual.h
	Interface/OSLayer/Traits/IsComparableWithNotEqual.h
	Interface/OSLayer/Traits/IsConst.h
	Interface/OSLayer/Traits/IsConstantEvaluated.h
	Interface/OSLayer/Traits/IsConstructible.h
	Interface/OSLayer/Traits/IsConvertible.h
	Interface/OSLayer/Traits/IsCopyAssignable.h
	Interface/OSLayer/Traits/IsCopyConstructible.h
	Interface/OSLayer/Traits/IsDefaultConstructible.h
	Interface/OSLayer/Traits/IsDerivedFrom.h
	Interface/OSLayer/Traits/IsDestructible.h
	Interface/OSLayer/Traits/IsEnum.h
	Interface/OSLayer/Traits/IsExplicitlyConstructible.h
	Interface/OSLayer/Traits/IsExplicitlyCopyConstructible.h
	Interface/OSLayer/Traits/IsExplicitlyDefaultConstructible.h
	Interface/OSLayer/Traits/IsExplicitlyMoveConstructible.h
	Interface/OSLayer/Traits/IsFloatingPoint.h
	Interface/OSLayer/Traits/IsFunction.h
	Interface/OSLayer/Traits/IsImplicitlyConstructible.h
	Interface/OSLayer/Traits/IsImplicitlyCopyConstructible.h
	Interface/OSLayer/Traits/IsImplicitlyDefaultConstructible.h
	Interface/OSLayer/Traits/IsImplicitlyMoveConstructible.h
	Interface/OSLayer/Traits/IsIntegral.h
	Interface/OSLayer/Traits/IsLValueReference.h
	Interface/OSLayer/Traits/IsMemberFunctionPointer.h
	Interface/OSLayer/Traits/IsMemberObjectPointer.h
	Interface/OSLayer/Traits/IsMemberPointer.h
	Interface/OSLayer/Traits/IsMoveAssignable.h
	Interface/OSLayer/Traits/IsMoveConstructible.h
	Interface/OSLayer/Traits/IsNothrowAssignable.h
	Interface/OSLayer/Traits/IsNothrowConstructible.h
	Interface/OSLayer/Traits/IsNothrowCopyAssignable.h
	Interface/OSLayer/Traits/IsNothrowCopyConstructible.h
	Interface/OSLayer/Traits/IsNothrowDefaultConstructible.h
	Interface/OSLayer/Traits/IsNothrowDestructible.h
	Interface/OSLayer/Traits/IsNothrowMoveAssignable.h
	Interface/OSLayer/Traits/IsNothrowMoveConstructible.h
	Interface/OSLayer/Traits/IsNothrowSwappable.h
	Interface/OSLayer/Traits/IsNotSame.h
	Interface/OSLayer/Traits/IsNullptr.h
	Interface/OSLayer/Traits/IsObject.h
	Interface/OSLayer/Traits/IsPointer.h
	Interface/OSLayer/Traits/IsPowerOfTwo.h
	Interface/OSLayer/Traits/IsReference.h
	Interface/OSLayer/Traits/IsReferenceable.h
	Interface/OSLayer/Traits/IsRValueReference.h
	Interface/OSLayer/Traits/IsSame.h
	Interface/OSLayer/Traits/IsSameSize.h
	Interface/OSLayer/Traits/IsScalar.h
	Interface/OSLayer/Traits/IsSigned.h
	Interface/OSLayer/Traits/IsStandardLayout.h
	Interface/OSLayer/Traits/IsSwappable.h
	Interface/OSLayer/Traits/IsTrivial.h
	Interface/OSLayer/Traits/IsTriviallyAssignable.h
	Interface/OSLayer/Traits/IsTriviallyConstructible.h
	Interface/OSLayer/Traits/IsTriviallyCopyable.h
	Interface/OSLayer/Traits/IsTriviallyCopyAssignable.h
	Interface/OSLayer/Traits/IsTriviallyCopyConstructible.h
	Interface/OSLayer/Traits/IsTriviallyDefaultConstructible.h
	Interface/OSLayer/Traits/IsTriviallyDestructible.h
	Interface/OSLayer/Traits/IsTriviallyMoveAssignable.h
	Interface/OSLayer/Traits/IsTriviallyMoveConstructible.h
	Interface/OSLayer/Traits/IsTriviallySwappable.h
	Interface/OSLayer/Traits/IsUnboundedArray.h
	Interface/OSLayer/Traits/IsUnion.h
	Interface/OSLayer/Traits/IsUnsigned.h
	Interface/OSLayer/Traits/IsVoid.h
	Interface/OSLayer/Traits/IsVolatile.h
	Interface/OSLayer/Traits/MakeSigned.h
	Interface/OSLayer/Traits/MakeUnsigned.h
	Interface/OSLayer/Traits/Not.h
	Interface/OSLayer/Traits/Or.h
	Interface/OSLayer/Traits/RemoveAllExtents.h
	Interface/OSLayer/Traits/RemoveConst.h
	Interface/OSLayer/Traits/RemoveCV.h
	Interface/OSLayer/Traits/RemoveCVRef.h
	Interface/OSLayer/Traits/RemoveExtent.h
	Interface/OSLayer/Traits/RemovePointer.h
	Interface/OSLayer/Traits/RemoveReference.h
	Interface/OSLayer/Traits/RemoveVolatile.h
	Interface/OSLayer/Traits/UnderlyingType.h
	Interface/OSLayer/Traits/VoidT.h
	Interface/OSLayer/Assert.h
	Interface/OSLayer/Atomics.h
	Interface/OSLayer/Char.h
	Interface/OSLayer/Compilation.h
	Interface/OSLayer/CompilerDefines.h
	Interface/OSLayer/Containers
	Interface/OSLayer/CString.h
	Interface/OSLayer/Debugger.h
	Interface/OSLayer/Defines.h
	Interface/OSLayer/Hash
	Interface/OSLayer/Hash.h
	Interface/OSLayer/Iterators
	Interface/OSLayer/Math.h
	Interface/OSLayer/Memory.h
	Interface/OSLayer/Minimal.h
	Interface/OSLayer/OSCommon
	Interface/OSLayer/OSLinux
	Interface/OSLayer/OSWindows
	Interface/OSLayer/Slice.h
	Interface/OSLayer/String.h
	Interface/OSLayer/TagInit.h
	Interface/OSLayer/TagInPlace.h
	Interface/OSLayer/Templates
	Interface/OSLayer/Traits
	Interface/OSLayer/Types.h
	Interface/OSLayer/Uuid.h
)

#file( GLOB_RECURSE source_files Implementation/* Interface/* )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${interfaces} ${implementations})

# Add OSLayer to the project
add_library(${target_name} STATIC ${interfaces} ${implementations})

# Add HUDEngine compiler options
add_hudengine_cxx_compile_options(${target_name})
# Add HUDEngine compiler options
add_hudengine_cxx_compile_definitions(${target_name})
# Add HUDEngine linker options
add_hudengine_cxx_linker_static_options(${target_name})

#Set the target under Runtime folder
set_target_properties(${target_name} PROPERTIES FOLDER Runtime)

# Set output directory
set_target_properties(${target_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})

# Set MSVC PDB
if(MSVC)
	set_target_properties(${target_name} PROPERTIES PDB_OUTPUT_DIRECTORY  ${OUT_DIR})
	set_target_properties(${target_name} PROPERTIES PDB_NAME "${target_name}" PDB_NAME_DEBUG "${target_name}" COMPILE_PDB_NAME "${target_name}" COMPILE_PDB_NAME_DEBUG "${target_name}")
endif()

# Include Interface directory to inclusion path
target_include_directories(${target_name} PUBLIC Interface)

