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
CMAKE_SOURCE_DIR = /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk

# Include any dependencies generated for this target.
include libSolve/CMakeFiles/Solve.dir/depend.make

# Include the progress variables for this target.
include libSolve/CMakeFiles/Solve.dir/progress.make

# Include the compile flags for this target's objects.
include libSolve/CMakeFiles/Solve.dir/flags.make

libSolve/CMakeFiles/Solve.dir/solve.cpp.o: libSolve/CMakeFiles/Solve.dir/flags.make
libSolve/CMakeFiles/Solve.dir/solve.cpp.o: libSolve/solve.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object libSolve/CMakeFiles/Solve.dir/solve.cpp.o"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Solve.dir/solve.cpp.o -c /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve/solve.cpp

libSolve/CMakeFiles/Solve.dir/solve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Solve.dir/solve.cpp.i"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve/solve.cpp > CMakeFiles/Solve.dir/solve.cpp.i

libSolve/CMakeFiles/Solve.dir/solve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Solve.dir/solve.cpp.s"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve/solve.cpp -o CMakeFiles/Solve.dir/solve.cpp.s

libSolve/CMakeFiles/Solve.dir/solve.cpp.o.requires:
.PHONY : libSolve/CMakeFiles/Solve.dir/solve.cpp.o.requires

libSolve/CMakeFiles/Solve.dir/solve.cpp.o.provides: libSolve/CMakeFiles/Solve.dir/solve.cpp.o.requires
	$(MAKE) -f libSolve/CMakeFiles/Solve.dir/build.make libSolve/CMakeFiles/Solve.dir/solve.cpp.o.provides.build
.PHONY : libSolve/CMakeFiles/Solve.dir/solve.cpp.o.provides

libSolve/CMakeFiles/Solve.dir/solve.cpp.o.provides.build: libSolve/CMakeFiles/Solve.dir/solve.cpp.o

# Object files for target Solve
Solve_OBJECTS = \
"CMakeFiles/Solve.dir/solve.cpp.o"

# External object files for target Solve
Solve_EXTERNAL_OBJECTS =

libSolve/libSolve.a: libSolve/CMakeFiles/Solve.dir/solve.cpp.o
libSolve/libSolve.a: libSolve/CMakeFiles/Solve.dir/build.make
libSolve/libSolve.a: libSolve/CMakeFiles/Solve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libSolve.a"
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve && $(CMAKE_COMMAND) -P CMakeFiles/Solve.dir/cmake_clean_target.cmake
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Solve.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libSolve/CMakeFiles/Solve.dir/build: libSolve/libSolve.a
.PHONY : libSolve/CMakeFiles/Solve.dir/build

libSolve/CMakeFiles/Solve.dir/requires: libSolve/CMakeFiles/Solve.dir/solve.cpp.o.requires
.PHONY : libSolve/CMakeFiles/Solve.dir/requires

libSolve/CMakeFiles/Solve.dir/clean:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve && $(CMAKE_COMMAND) -P CMakeFiles/Solve.dir/cmake_clean.cmake
.PHONY : libSolve/CMakeFiles/Solve.dir/clean

libSolve/CMakeFiles/Solve.dir/depend:
	cd /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve /home/cg/dev/master-thesis/dev/src/c-cpp/AntConfApp/trunk/libSolve/CMakeFiles/Solve.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libSolve/CMakeFiles/Solve.dir/depend

