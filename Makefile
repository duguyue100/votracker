# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.12/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.12/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.12/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dgyHome/Documents/GitHub/vot-toolkit/votracker/votracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dgyHome/Documents/GitHub/vot-toolkit/votracker/votracker

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/2.8.12/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/2.8.12/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/dgyHome/Documents/GitHub/vot-toolkit/votracker/votracker/CMakeFiles /Users/dgyHome/Documents/GitHub/vot-toolkit/votracker/votracker/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/dgyHome/Documents/GitHub/vot-toolkit/votracker/votracker/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named trackermain

# Build rule for target.
trackermain: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 trackermain
.PHONY : trackermain

# fast build rule for target.
trackermain/fast:
	$(MAKE) -f CMakeFiles/trackermain.dir/build.make CMakeFiles/trackermain.dir/build
.PHONY : trackermain/fast

#=============================================================================
# Target rules for targets named votdrawbox

# Build rule for target.
votdrawbox: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 votdrawbox
.PHONY : votdrawbox

# fast build rule for target.
votdrawbox/fast:
	$(MAKE) -f CMakeFiles/votdrawbox.dir/build.make CMakeFiles/votdrawbox.dir/build
.PHONY : votdrawbox/fast

#=============================================================================
# Target rules for targets named votrackerlib

# Build rule for target.
votrackerlib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 votrackerlib
.PHONY : votrackerlib

# fast build rule for target.
votrackerlib/fast:
	$(MAKE) -f CMakeFiles/votrackerlib.dir/build.make CMakeFiles/votrackerlib.dir/build
.PHONY : votrackerlib/fast

src/votdrawboxtest.o: src/votdrawboxtest.cpp.o
.PHONY : src/votdrawboxtest.o

# target to build an object file
src/votdrawboxtest.cpp.o:
	$(MAKE) -f CMakeFiles/votdrawbox.dir/build.make CMakeFiles/votdrawbox.dir/src/votdrawboxtest.cpp.o
.PHONY : src/votdrawboxtest.cpp.o

src/votdrawboxtest.i: src/votdrawboxtest.cpp.i
.PHONY : src/votdrawboxtest.i

# target to preprocess a source file
src/votdrawboxtest.cpp.i:
	$(MAKE) -f CMakeFiles/votdrawbox.dir/build.make CMakeFiles/votdrawbox.dir/src/votdrawboxtest.cpp.i
.PHONY : src/votdrawboxtest.cpp.i

src/votdrawboxtest.s: src/votdrawboxtest.cpp.s
.PHONY : src/votdrawboxtest.s

# target to generate assembly for a file
src/votdrawboxtest.cpp.s:
	$(MAKE) -f CMakeFiles/votdrawbox.dir/build.make CMakeFiles/votdrawbox.dir/src/votdrawboxtest.cpp.s
.PHONY : src/votdrawboxtest.cpp.s

src/votrackermain.o: src/votrackermain.cpp.o
.PHONY : src/votrackermain.o

# target to build an object file
src/votrackermain.cpp.o:
	$(MAKE) -f CMakeFiles/trackermain.dir/build.make CMakeFiles/trackermain.dir/src/votrackermain.cpp.o
.PHONY : src/votrackermain.cpp.o

src/votrackermain.i: src/votrackermain.cpp.i
.PHONY : src/votrackermain.i

# target to preprocess a source file
src/votrackermain.cpp.i:
	$(MAKE) -f CMakeFiles/trackermain.dir/build.make CMakeFiles/trackermain.dir/src/votrackermain.cpp.i
.PHONY : src/votrackermain.cpp.i

src/votrackermain.s: src/votrackermain.cpp.s
.PHONY : src/votrackermain.s

# target to generate assembly for a file
src/votrackermain.cpp.s:
	$(MAKE) -f CMakeFiles/trackermain.dir/build.make CMakeFiles/trackermain.dir/src/votrackermain.cpp.s
.PHONY : src/votrackermain.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... trackermain"
	@echo "... votdrawbox"
	@echo "... votrackerlib"
	@echo "... src/votdrawboxtest.o"
	@echo "... src/votdrawboxtest.i"
	@echo "... src/votdrawboxtest.s"
	@echo "... src/votrackermain.o"
	@echo "... src/votrackermain.i"
	@echo "... src/votrackermain.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

