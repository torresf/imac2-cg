# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build

# Include any dependencies generated for this target.
include TP2/CMakeFiles/TP2_exo4_matrices.dir/depend.make

# Include the progress variables for this target.
include TP2/CMakeFiles/TP2_exo4_matrices.dir/progress.make

# Include the compile flags for this target's objects.
include TP2/CMakeFiles/TP2_exo4_matrices.dir/flags.make

TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o: TP2/CMakeFiles/TP2_exo4_matrices.dir/flags.make
TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o: /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template/TP2/exo4_matrices.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o"
	cd /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o -c /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template/TP2/exo4_matrices.cpp

TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.i"
	cd /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template/TP2/exo4_matrices.cpp > CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.i

TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.s"
	cd /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template/TP2/exo4_matrices.cpp -o CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.s

TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.requires:

.PHONY : TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.requires

TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.provides: TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.requires
	$(MAKE) -f TP2/CMakeFiles/TP2_exo4_matrices.dir/build.make TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.provides.build
.PHONY : TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.provides

TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.provides.build: TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o


# Object files for target TP2_exo4_matrices
TP2_exo4_matrices_OBJECTS = \
"CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o"

# External object files for target TP2_exo4_matrices
TP2_exo4_matrices_EXTERNAL_OBJECTS =

TP2/TP2_exo4_matrices: TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o
TP2/TP2_exo4_matrices: TP2/CMakeFiles/TP2_exo4_matrices.dir/build.make
TP2/TP2_exo4_matrices: glimac/libglimac.a
TP2/TP2_exo4_matrices: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP2/TP2_exo4_matrices: /usr/lib/x86_64-linux-gnu/libSDL.so
TP2/TP2_exo4_matrices: /usr/lib/x86_64-linux-gnu/libOpenGL.so
TP2/TP2_exo4_matrices: /usr/lib/x86_64-linux-gnu/libGLX.so
TP2/TP2_exo4_matrices: /usr/lib/x86_64-linux-gnu/libGLU.so
TP2/TP2_exo4_matrices: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP2/TP2_exo4_matrices: TP2/CMakeFiles/TP2_exo4_matrices.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP2_exo4_matrices"
	cd /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP2_exo4_matrices.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP2/CMakeFiles/TP2_exo4_matrices.dir/build: TP2/TP2_exo4_matrices

.PHONY : TP2/CMakeFiles/TP2_exo4_matrices.dir/build

TP2/CMakeFiles/TP2_exo4_matrices.dir/requires: TP2/CMakeFiles/TP2_exo4_matrices.dir/exo4_matrices.cpp.o.requires

.PHONY : TP2/CMakeFiles/TP2_exo4_matrices.dir/requires

TP2/CMakeFiles/TP2_exo4_matrices.dir/clean:
	cd /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2 && $(CMAKE_COMMAND) -P CMakeFiles/TP2_exo4_matrices.dir/cmake_clean.cmake
.PHONY : TP2/CMakeFiles/TP2_exo4_matrices.dir/clean

TP2/CMakeFiles/TP2_exo4_matrices.dir/depend:
	cd /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template/TP2 /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2 /home/torresf/Documents/CG/imac2-cg/td1/GLImac-Template-build/TP2/CMakeFiles/TP2_exo4_matrices.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP2/CMakeFiles/TP2_exo4_matrices.dir/depend

