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
include examples/CMakeFiles/KernelOptimization.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/KernelOptimization.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/KernelOptimization.dir/flags.make

examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o: examples/CMakeFiles/KernelOptimization.dir/flags.make
examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o: examples/ReClaM/KernelOptimization.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o -c /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/ReClaM/KernelOptimization.cpp

examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.i"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/ReClaM/KernelOptimization.cpp > CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.i

examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.s"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/ReClaM/KernelOptimization.cpp -o CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.s

examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.requires:
.PHONY : examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.requires

examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.provides: examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/KernelOptimization.dir/build.make examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.provides.build
.PHONY : examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.provides

examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.provides.build: examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o

# Object files for target KernelOptimization
KernelOptimization_OBJECTS = \
"CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o"

# External object files for target KernelOptimization
KernelOptimization_EXTERNAL_OBJECTS =

examples/KernelOptimization: examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o
examples/KernelOptimization: libshark.so.2.3.0
examples/KernelOptimization: examples/CMakeFiles/KernelOptimization.dir/build.make
examples/KernelOptimization: examples/CMakeFiles/KernelOptimization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable KernelOptimization"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KernelOptimization.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/KernelOptimization.dir/build: examples/KernelOptimization
.PHONY : examples/CMakeFiles/KernelOptimization.dir/build

examples/CMakeFiles/KernelOptimization.dir/requires: examples/CMakeFiles/KernelOptimization.dir/ReClaM/KernelOptimization.cpp.o.requires
.PHONY : examples/CMakeFiles/KernelOptimization.dir/requires

examples/CMakeFiles/KernelOptimization.dir/clean:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples && $(CMAKE_COMMAND) -P CMakeFiles/KernelOptimization.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/KernelOptimization.dir/clean

examples/CMakeFiles/KernelOptimization.dir/depend:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/Shark && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cg/dev/master-thesis/dev/src/c-cpp/Shark /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples /home/cg/dev/master-thesis/dev/src/c-cpp/Shark /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples /home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/CMakeFiles/KernelOptimization.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/KernelOptimization.dir/depend

