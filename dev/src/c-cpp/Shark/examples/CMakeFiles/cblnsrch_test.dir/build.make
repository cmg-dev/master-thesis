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
include examples/CMakeFiles/cblnsrch_test.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/cblnsrch_test.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/cblnsrch_test.dir/flags.make

examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o: examples/CMakeFiles/cblnsrch_test.dir/flags.make
examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o: examples/LinAlg/cblnsrch_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o -c /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/LinAlg/cblnsrch_test.cpp

examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.i"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/LinAlg/cblnsrch_test.cpp > CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.i

examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.s"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/LinAlg/cblnsrch_test.cpp -o CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.s

examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.requires:
.PHONY : examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.requires

examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.provides: examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/cblnsrch_test.dir/build.make examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.provides.build
.PHONY : examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.provides

examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.provides.build: examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o

# Object files for target cblnsrch_test
cblnsrch_test_OBJECTS = \
"CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o"

# External object files for target cblnsrch_test
cblnsrch_test_EXTERNAL_OBJECTS =

examples/cblnsrch_test: examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o
examples/cblnsrch_test: libshark.so.2.3.0
examples/cblnsrch_test: examples/CMakeFiles/cblnsrch_test.dir/build.make
examples/cblnsrch_test: examples/CMakeFiles/cblnsrch_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable cblnsrch_test"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cblnsrch_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/cblnsrch_test.dir/build: examples/cblnsrch_test
.PHONY : examples/CMakeFiles/cblnsrch_test.dir/build

examples/CMakeFiles/cblnsrch_test.dir/requires: examples/CMakeFiles/cblnsrch_test.dir/LinAlg/cblnsrch_test.cpp.o.requires
.PHONY : examples/CMakeFiles/cblnsrch_test.dir/requires

examples/CMakeFiles/cblnsrch_test.dir/clean:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && $(CMAKE_COMMAND) -P CMakeFiles/cblnsrch_test.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/cblnsrch_test.dir/clean

examples/CMakeFiles/cblnsrch_test.dir/depend:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cg/dev/master-thesis/dev/src/c-cpp/Shark /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples /home/cg/dev/master-thesis/dev/src/c-cpp/Shark /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/CMakeFiles/cblnsrch_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/cblnsrch_test.dir/depend

