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
CMAKE_SOURCE_DIR = /home/torresf/Documents/CG/imac2-cg/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build

# Include any dependencies generated for this target.
include TP8/CMakeFiles/TP8_SDLtemplate.dir/depend.make

# Include the progress variables for this target.
include TP8/CMakeFiles/TP8_SDLtemplate.dir/progress.make

# Include the compile flags for this target's objects.
include TP8/CMakeFiles/TP8_SDLtemplate.dir/flags.make

TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o: TP8/CMakeFiles/TP8_SDLtemplate.dir/flags.make
TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o: /home/torresf/Documents/CG/imac2-cg/GLImac-Template/TP8/SDLtemplate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o"
	cd /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o -c /home/torresf/Documents/CG/imac2-cg/GLImac-Template/TP8/SDLtemplate.cpp

TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.i"
	cd /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/torresf/Documents/CG/imac2-cg/GLImac-Template/TP8/SDLtemplate.cpp > CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.i

TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.s"
	cd /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/torresf/Documents/CG/imac2-cg/GLImac-Template/TP8/SDLtemplate.cpp -o CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.s

TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.requires:

.PHONY : TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.requires

TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.provides: TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.requires
	$(MAKE) -f TP8/CMakeFiles/TP8_SDLtemplate.dir/build.make TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.provides.build
.PHONY : TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.provides

TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.provides.build: TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o


# Object files for target TP8_SDLtemplate
TP8_SDLtemplate_OBJECTS = \
"CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o"

# External object files for target TP8_SDLtemplate
TP8_SDLtemplate_EXTERNAL_OBJECTS =

TP8/TP8_SDLtemplate: TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o
TP8/TP8_SDLtemplate: TP8/CMakeFiles/TP8_SDLtemplate.dir/build.make
TP8/TP8_SDLtemplate: glimac/libglimac.a
TP8/TP8_SDLtemplate: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP8/TP8_SDLtemplate: /usr/lib/x86_64-linux-gnu/libSDL.so
TP8/TP8_SDLtemplate: /usr/lib/x86_64-linux-gnu/libOpenGL.so
TP8/TP8_SDLtemplate: /usr/lib/x86_64-linux-gnu/libGLX.so
TP8/TP8_SDLtemplate: /usr/lib/x86_64-linux-gnu/libGLU.so
TP8/TP8_SDLtemplate: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP8/TP8_SDLtemplate: TP8/CMakeFiles/TP8_SDLtemplate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP8_SDLtemplate"
	cd /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP8_SDLtemplate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP8/CMakeFiles/TP8_SDLtemplate.dir/build: TP8/TP8_SDLtemplate

.PHONY : TP8/CMakeFiles/TP8_SDLtemplate.dir/build

TP8/CMakeFiles/TP8_SDLtemplate.dir/requires: TP8/CMakeFiles/TP8_SDLtemplate.dir/SDLtemplate.cpp.o.requires

.PHONY : TP8/CMakeFiles/TP8_SDLtemplate.dir/requires

TP8/CMakeFiles/TP8_SDLtemplate.dir/clean:
	cd /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8 && $(CMAKE_COMMAND) -P CMakeFiles/TP8_SDLtemplate.dir/cmake_clean.cmake
.PHONY : TP8/CMakeFiles/TP8_SDLtemplate.dir/clean

TP8/CMakeFiles/TP8_SDLtemplate.dir/depend:
	cd /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/torresf/Documents/CG/imac2-cg/GLImac-Template /home/torresf/Documents/CG/imac2-cg/GLImac-Template/TP8 /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8 /home/torresf/Documents/CG/imac2-cg/GLImac-Template-build/TP8/CMakeFiles/TP8_SDLtemplate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP8/CMakeFiles/TP8_SDLtemplate.dir/depend
