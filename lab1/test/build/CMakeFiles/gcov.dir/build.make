# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/krillin/code/nsu/23203_knyazkov/lab1/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/krillin/code/nsu/23203_knyazkov/lab1/test/build

# Utility rule file for gcov.

# Include any custom commands dependencies for this target.
include CMakeFiles/gcov.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gcov.dir/progress.make

CMakeFiles/gcov:
	mkdir -p gcoverage
	/usr/bin/gmake test

gcov: CMakeFiles/gcov
gcov: CMakeFiles/gcov.dir/build.make
	cd /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/gcoverage && echo ===================\ GCOV\ ====================
	cd /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/gcoverage && gcov -b src/all_tests.cc -o /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/CMakeFiles/TestCoverage.dir/src
	cd /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/gcoverage && echo --\ Source\ directory:\ /home/krillin/code/nsu/23203_knyazkov/lab1/test/src/
	cd /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/gcoverage && echo --\ Coverage\ files\ have\ been\ output\ to\ /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/gcoverage
.PHONY : gcov

# Rule to build all files generated by this target.
CMakeFiles/gcov.dir/build: gcov
.PHONY : CMakeFiles/gcov.dir/build

CMakeFiles/gcov.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gcov.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gcov.dir/clean

CMakeFiles/gcov.dir/depend:
	cd /home/krillin/code/nsu/23203_knyazkov/lab1/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/krillin/code/nsu/23203_knyazkov/lab1/test /home/krillin/code/nsu/23203_knyazkov/lab1/test /home/krillin/code/nsu/23203_knyazkov/lab1/test/build /home/krillin/code/nsu/23203_knyazkov/lab1/test/build /home/krillin/code/nsu/23203_knyazkov/lab1/test/build/CMakeFiles/gcov.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/gcov.dir/depend

