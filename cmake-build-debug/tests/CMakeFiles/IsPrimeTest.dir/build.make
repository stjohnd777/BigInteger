# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/overman/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/overman/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.7660.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/overman/dev/github/utils-bigint-crpto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/IsPrimeTest.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/IsPrimeTest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/IsPrimeTest.dir/flags.make

tests/CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.o: tests/CMakeFiles/IsPrimeTest.dir/flags.make
tests/CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.o: ../tests/big_interger/IsPrimeTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.o"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.o -c /Users/overman/dev/github/utils-bigint-crpto/tests/big_interger/IsPrimeTest.cpp

tests/CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.i"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/overman/dev/github/utils-bigint-crpto/tests/big_interger/IsPrimeTest.cpp > CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.i

tests/CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.s"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/overman/dev/github/utils-bigint-crpto/tests/big_interger/IsPrimeTest.cpp -o CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.s

# Object files for target IsPrimeTest
IsPrimeTest_OBJECTS = \
"CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.o"

# External object files for target IsPrimeTest
IsPrimeTest_EXTERNAL_OBJECTS =

tests/IsPrimeTest: tests/CMakeFiles/IsPrimeTest.dir/big_interger/IsPrimeTest.cpp.o
tests/IsPrimeTest: tests/CMakeFiles/IsPrimeTest.dir/build.make
tests/IsPrimeTest: bigint/libbigint.a
tests/IsPrimeTest: utils/libutils.a
tests/IsPrimeTest: tests/CMakeFiles/IsPrimeTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IsPrimeTest"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/IsPrimeTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/IsPrimeTest.dir/build: tests/IsPrimeTest

.PHONY : tests/CMakeFiles/IsPrimeTest.dir/build

tests/CMakeFiles/IsPrimeTest.dir/clean:
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/IsPrimeTest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/IsPrimeTest.dir/clean

tests/CMakeFiles/IsPrimeTest.dir/depend:
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/overman/dev/github/utils-bigint-crpto /Users/overman/dev/github/utils-bigint-crpto/tests /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests/CMakeFiles/IsPrimeTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/IsPrimeTest.dir/depend

