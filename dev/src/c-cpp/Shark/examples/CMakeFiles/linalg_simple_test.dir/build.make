# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cg/dev/master-thesis/dev/src/c-cpp/Shark

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cg/dev/master-thesis/dev/src/c-cpp/Shark

# Include any dependencies generated for this target.
include examples/CMakeFiles/linalg_simple_test.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/linalg_simple_test.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/linalg_simple_test.dir/flags.make

examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o: examples/CMakeFiles/linalg_simple_test.dir/flags.make
examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o: examples/LinAlg/linalg_simple_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o -c /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/LinAlg/linalg_simple_test.cpp

examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.i"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/LinAlg/linalg_simple_test.cpp > CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.i

examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.s"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/LinAlg/linalg_simple_test.cpp -o CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.s

examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.requires:
.PHONY : examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.requires

examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.provides: examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/linalg_simple_test.dir/build.make examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.provides.build
.PHONY : examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.provides

examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.provides.build: examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o

# Object files for target linalg_simple_test
linalg_simple_test_OBJECTS = \
"CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o"

# External object files for target linalg_simple_test
linalg_simple_test_EXTERNAL_OBJECTS =

examples/linalg_simple_test: examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o
examples/linalg_simple_test: libshark.so.2.3.0
examples/linalg_simple_test: examples/CMakeFiles/linalg_simple_test.dir/build.make
examples/linalg_simple_test: examples/CMakeFiles/linalg_simple_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable linalg_simple_test"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linalg_simple_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/linalg_simple_test.dir/build: examples/linalg_simple_test
.PHONY : examples/CMakeFiles/linalg_simple_test.dir/build

examples/CMakeFiles/linalg_simple_test.dir/requires: examples/CMakeFiles/linalg_simple_test.dir/LinAlg/linalg_simple_test.cpp.o.requires
.PHONY : examples/CMakeFiles/linalg_simple_test.dir/requires

examples/CMakeFiles/linalg_simple_test.dir/clean:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && $(CMAKE_COMMAND) -P CMakeFiles/linalg_simple_test.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/linalg_simple_test.dir/clean

examples/CMakeFiles/linalg_simple_test.dir/depend:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cg/dev/master-thesis/dev/src/c-cpp/Shark /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples /home/cg/dev/master-thesis/dev/src/c-cpp/Shark /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/CMakeFiles/linalg_simple_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/linalg_simple_test.dir/depend

