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
include tests/CMakeFiles/EasyVectorTest.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/EasyVectorTest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/EasyVectorTest.dir/flags.make

tests/CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.o: tests/CMakeFiles/EasyVectorTest.dir/flags.make
tests/CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.o: ../tests/utils/EasyVectorTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.o"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.o -c /Users/overman/dev/github/utils-bigint-crpto/tests/utils/EasyVectorTest.cpp

tests/CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.i"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/overman/dev/github/utils-bigint-crpto/tests/utils/EasyVectorTest.cpp > CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.i

tests/CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.s"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/overman/dev/github/utils-bigint-crpto/tests/utils/EasyVectorTest.cpp -o CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.s

# Object files for target EasyVectorTest
EasyVectorTest_OBJECTS = \
"CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.o"

# External object files for target EasyVectorTest
EasyVectorTest_EXTERNAL_OBJECTS =

tests/EasyVectorTest: tests/CMakeFiles/EasyVectorTest.dir/utils/EasyVectorTest.cpp.o
tests/EasyVectorTest: tests/CMakeFiles/EasyVectorTest.dir/build.make
tests/EasyVectorTest: utils/libutils.a
tests/EasyVectorTest: bigint/libbigint.a
tests/EasyVectorTest: utils/libutils.a
tests/EasyVectorTest: tests/CMakeFiles/EasyVectorTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EasyVectorTest"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EasyVectorTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/EasyVectorTest.dir/build: tests/EasyVectorTest

.PHONY : tests/CMakeFiles/EasyVectorTest.dir/build

tests/CMakeFiles/EasyVectorTest.dir/clean:
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/EasyVectorTest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/EasyVectorTest.dir/clean

tests/CMakeFiles/EasyVectorTest.dir/depend:
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/overman/dev/github/utils-bigint-crpto /Users/overman/dev/github/utils-bigint-crpto/tests /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests/CMakeFiles/EasyVectorTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/EasyVectorTest.dir/depend
