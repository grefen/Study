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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/grefen/github/Study/boostdemo/synctimer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/grefen/github/Study/boostdemo/synctimer

# Include any dependencies generated for this target.
include CMakeFiles/synctimer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/synctimer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/synctimer.dir/flags.make

CMakeFiles/synctimer.dir/synctimer.cpp.o: CMakeFiles/synctimer.dir/flags.make
CMakeFiles/synctimer.dir/synctimer.cpp.o: synctimer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/grefen/github/Study/boostdemo/synctimer/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/synctimer.dir/synctimer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/synctimer.dir/synctimer.cpp.o -c /home/grefen/github/Study/boostdemo/synctimer/synctimer.cpp

CMakeFiles/synctimer.dir/synctimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/synctimer.dir/synctimer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/grefen/github/Study/boostdemo/synctimer/synctimer.cpp > CMakeFiles/synctimer.dir/synctimer.cpp.i

CMakeFiles/synctimer.dir/synctimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/synctimer.dir/synctimer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/grefen/github/Study/boostdemo/synctimer/synctimer.cpp -o CMakeFiles/synctimer.dir/synctimer.cpp.s

CMakeFiles/synctimer.dir/synctimer.cpp.o.requires:
.PHONY : CMakeFiles/synctimer.dir/synctimer.cpp.o.requires

CMakeFiles/synctimer.dir/synctimer.cpp.o.provides: CMakeFiles/synctimer.dir/synctimer.cpp.o.requires
	$(MAKE) -f CMakeFiles/synctimer.dir/build.make CMakeFiles/synctimer.dir/synctimer.cpp.o.provides.build
.PHONY : CMakeFiles/synctimer.dir/synctimer.cpp.o.provides

CMakeFiles/synctimer.dir/synctimer.cpp.o.provides.build: CMakeFiles/synctimer.dir/synctimer.cpp.o

# Object files for target synctimer
synctimer_OBJECTS = \
"CMakeFiles/synctimer.dir/synctimer.cpp.o"

# External object files for target synctimer
synctimer_EXTERNAL_OBJECTS =

synctimer: CMakeFiles/synctimer.dir/synctimer.cpp.o
synctimer: CMakeFiles/synctimer.dir/build.make
synctimer: CMakeFiles/synctimer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable synctimer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/synctimer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/synctimer.dir/build: synctimer
.PHONY : CMakeFiles/synctimer.dir/build

CMakeFiles/synctimer.dir/requires: CMakeFiles/synctimer.dir/synctimer.cpp.o.requires
.PHONY : CMakeFiles/synctimer.dir/requires

CMakeFiles/synctimer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/synctimer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/synctimer.dir/clean

CMakeFiles/synctimer.dir/depend:
	cd /home/grefen/github/Study/boostdemo/synctimer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/grefen/github/Study/boostdemo/synctimer /home/grefen/github/Study/boostdemo/synctimer /home/grefen/github/Study/boostdemo/synctimer /home/grefen/github/Study/boostdemo/synctimer /home/grefen/github/Study/boostdemo/synctimer/CMakeFiles/synctimer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/synctimer.dir/depend

