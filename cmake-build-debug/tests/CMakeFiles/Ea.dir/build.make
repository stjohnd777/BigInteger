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
include tests/CMakeFiles/Ea.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/Ea.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/Ea.dir/flags.make

tests/CMakeFiles/Ea.dir/utils/MetricTest.cpp.o: tests/CMakeFiles/Ea.dir/flags.make
tests/CMakeFiles/Ea.dir/utils/MetricTest.cpp.o: ../tests/utils/MetricTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/Ea.dir/utils/MetricTest.cpp.o"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ea.dir/utils/MetricTest.cpp.o -c /Users/overman/dev/github/utils-bigint-crpto/tests/utils/MetricTest.cpp

tests/CMakeFiles/Ea.dir/utils/MetricTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ea.dir/utils/MetricTest.cpp.i"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/overman/dev/github/utils-bigint-crpto/tests/utils/MetricTest.cpp > CMakeFiles/Ea.dir/utils/MetricTest.cpp.i

tests/CMakeFiles/Ea.dir/utils/MetricTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ea.dir/utils/MetricTest.cpp.s"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/overman/dev/github/utils-bigint-crpto/tests/utils/MetricTest.cpp -o CMakeFiles/Ea.dir/utils/MetricTest.cpp.s

tests/CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.o: tests/CMakeFiles/Ea.dir/flags.make
tests/CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.o: ../tests/utils/EasyStringTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.o"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.o -c /Users/overman/dev/github/utils-bigint-crpto/tests/utils/EasyStringTest.cpp

tests/CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.i"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/overman/dev/github/utils-bigint-crpto/tests/utils/EasyStringTest.cpp > CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.i

tests/CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.s"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/overman/dev/github/utils-bigint-crpto/tests/utils/EasyStringTest.cpp -o CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.s

# Object files for target Ea
Ea_OBJECTS = \
"CMakeFiles/Ea.dir/utils/MetricTest.cpp.o" \
"CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.o"

# External object files for target Ea
Ea_EXTERNAL_OBJECTS =

tests/Ea: tests/CMakeFiles/Ea.dir/utils/MetricTest.cpp.o
tests/Ea: tests/CMakeFiles/Ea.dir/utils/EasyStringTest.cpp.o
tests/Ea: tests/CMakeFiles/Ea.dir/build.make
tests/Ea: tests/CMakeFiles/Ea.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Ea"
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ea.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/Ea.dir/build: tests/Ea

.PHONY : tests/CMakeFiles/Ea.dir/build

tests/CMakeFiles/Ea.dir/clean:
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/Ea.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/Ea.dir/clean

tests/CMakeFiles/Ea.dir/depend:
	cd /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/overman/dev/github/utils-bigint-crpto /Users/overman/dev/github/utils-bigint-crpto/tests /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests /Users/overman/dev/github/utils-bigint-crpto/cmake-build-debug/tests/CMakeFiles/Ea.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/Ea.dir/depend
