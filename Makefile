# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/michael/workspace/perso/games/blockofighter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/michael/workspace/perso/games/blockofighter

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/michael/workspace/perso/games/blockofighter/CMakeFiles /home/michael/workspace/perso/games/blockofighter/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/michael/workspace/perso/games/blockofighter/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named blockofighter

# Build rule for target.
blockofighter: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 blockofighter
.PHONY : blockofighter

# fast build rule for target.
blockofighter/fast:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/build
.PHONY : blockofighter/fast

src/3dutils.o: src/3dutils.cpp.o

.PHONY : src/3dutils.o

# target to build an object file
src/3dutils.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/3dutils.cpp.o
.PHONY : src/3dutils.cpp.o

src/3dutils.i: src/3dutils.cpp.i

.PHONY : src/3dutils.i

# target to preprocess a source file
src/3dutils.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/3dutils.cpp.i
.PHONY : src/3dutils.cpp.i

src/3dutils.s: src/3dutils.cpp.s

.PHONY : src/3dutils.s

# target to generate assembly for a file
src/3dutils.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/3dutils.cpp.s
.PHONY : src/3dutils.cpp.s

src/appearance.o: src/appearance.cpp.o

.PHONY : src/appearance.o

# target to build an object file
src/appearance.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/appearance.cpp.o
.PHONY : src/appearance.cpp.o

src/appearance.i: src/appearance.cpp.i

.PHONY : src/appearance.i

# target to preprocess a source file
src/appearance.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/appearance.cpp.i
.PHONY : src/appearance.cpp.i

src/appearance.s: src/appearance.cpp.s

.PHONY : src/appearance.s

# target to generate assembly for a file
src/appearance.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/appearance.cpp.s
.PHONY : src/appearance.cpp.s

src/audio.o: src/audio.cpp.o

.PHONY : src/audio.o

# target to build an object file
src/audio.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/audio.cpp.o
.PHONY : src/audio.cpp.o

src/audio.i: src/audio.cpp.i

.PHONY : src/audio.i

# target to preprocess a source file
src/audio.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/audio.cpp.i
.PHONY : src/audio.cpp.i

src/audio.s: src/audio.cpp.s

.PHONY : src/audio.s

# target to generate assembly for a file
src/audio.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/audio.cpp.s
.PHONY : src/audio.cpp.s

src/camera.o: src/camera.cpp.o

.PHONY : src/camera.o

# target to build an object file
src/camera.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/camera.cpp.o
.PHONY : src/camera.cpp.o

src/camera.i: src/camera.cpp.i

.PHONY : src/camera.i

# target to preprocess a source file
src/camera.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/camera.cpp.i
.PHONY : src/camera.cpp.i

src/camera.s: src/camera.cpp.s

.PHONY : src/camera.s

# target to generate assembly for a file
src/camera.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/camera.cpp.s
.PHONY : src/camera.cpp.s

src/collision.o: src/collision.cpp.o

.PHONY : src/collision.o

# target to build an object file
src/collision.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/collision.cpp.o
.PHONY : src/collision.cpp.o

src/collision.i: src/collision.cpp.i

.PHONY : src/collision.i

# target to preprocess a source file
src/collision.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/collision.cpp.i
.PHONY : src/collision.cpp.i

src/collision.s: src/collision.cpp.s

.PHONY : src/collision.s

# target to generate assembly for a file
src/collision.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/collision.cpp.s
.PHONY : src/collision.cpp.s

src/end.o: src/end.cpp.o

.PHONY : src/end.o

# target to build an object file
src/end.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/end.cpp.o
.PHONY : src/end.cpp.o

src/end.i: src/end.cpp.i

.PHONY : src/end.i

# target to preprocess a source file
src/end.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/end.cpp.i
.PHONY : src/end.cpp.i

src/end.s: src/end.cpp.s

.PHONY : src/end.s

# target to generate assembly for a file
src/end.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/end.cpp.s
.PHONY : src/end.cpp.s

src/fight.o: src/fight.cpp.o

.PHONY : src/fight.o

# target to build an object file
src/fight.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/fight.cpp.o
.PHONY : src/fight.cpp.o

src/fight.i: src/fight.cpp.i

.PHONY : src/fight.i

# target to preprocess a source file
src/fight.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/fight.cpp.i
.PHONY : src/fight.cpp.i

src/fight.s: src/fight.cpp.s

.PHONY : src/fight.s

# target to generate assembly for a file
src/fight.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/fight.cpp.s
.PHONY : src/fight.cpp.s

src/fonct.o: src/fonct.cpp.o

.PHONY : src/fonct.o

# target to build an object file
src/fonct.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/fonct.cpp.o
.PHONY : src/fonct.cpp.o

src/fonct.i: src/fonct.cpp.i

.PHONY : src/fonct.i

# target to preprocess a source file
src/fonct.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/fonct.cpp.i
.PHONY : src/fonct.cpp.i

src/fonct.s: src/fonct.cpp.s

.PHONY : src/fonct.s

# target to generate assembly for a file
src/fonct.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/fonct.cpp.s
.PHONY : src/fonct.cpp.s

src/font.o: src/font.cpp.o

.PHONY : src/font.o

# target to build an object file
src/font.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/font.cpp.o
.PHONY : src/font.cpp.o

src/font.i: src/font.cpp.i

.PHONY : src/font.i

# target to preprocess a source file
src/font.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/font.cpp.i
.PHONY : src/font.cpp.i

src/font.s: src/font.cpp.s

.PHONY : src/font.s

# target to generate assembly for a file
src/font.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/font.cpp.s
.PHONY : src/font.cpp.s

src/glapi.o: src/glapi.cpp.o

.PHONY : src/glapi.o

# target to build an object file
src/glapi.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/glapi.cpp.o
.PHONY : src/glapi.cpp.o

src/glapi.i: src/glapi.cpp.i

.PHONY : src/glapi.i

# target to preprocess a source file
src/glapi.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/glapi.cpp.i
.PHONY : src/glapi.cpp.i

src/glapi.s: src/glapi.cpp.s

.PHONY : src/glapi.s

# target to generate assembly for a file
src/glapi.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/glapi.cpp.s
.PHONY : src/glapi.cpp.s

src/graphics.o: src/graphics.cpp.o

.PHONY : src/graphics.o

# target to build an object file
src/graphics.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/graphics.cpp.o
.PHONY : src/graphics.cpp.o

src/graphics.i: src/graphics.cpp.i

.PHONY : src/graphics.i

# target to preprocess a source file
src/graphics.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/graphics.cpp.i
.PHONY : src/graphics.cpp.i

src/graphics.s: src/graphics.cpp.s

.PHONY : src/graphics.s

# target to generate assembly for a file
src/graphics.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/graphics.cpp.s
.PHONY : src/graphics.cpp.s

src/legoblocks.o: src/legoblocks.cpp.o

.PHONY : src/legoblocks.o

# target to build an object file
src/legoblocks.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/legoblocks.cpp.o
.PHONY : src/legoblocks.cpp.o

src/legoblocks.i: src/legoblocks.cpp.i

.PHONY : src/legoblocks.i

# target to preprocess a source file
src/legoblocks.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/legoblocks.cpp.i
.PHONY : src/legoblocks.cpp.i

src/legoblocks.s: src/legoblocks.cpp.s

.PHONY : src/legoblocks.s

# target to generate assembly for a file
src/legoblocks.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/legoblocks.cpp.s
.PHONY : src/legoblocks.cpp.s

src/legoman.o: src/legoman.cpp.o

.PHONY : src/legoman.o

# target to build an object file
src/legoman.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/legoman.cpp.o
.PHONY : src/legoman.cpp.o

src/legoman.i: src/legoman.cpp.i

.PHONY : src/legoman.i

# target to preprocess a source file
src/legoman.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/legoman.cpp.i
.PHONY : src/legoman.cpp.i

src/legoman.s: src/legoman.cpp.s

.PHONY : src/legoman.s

# target to generate assembly for a file
src/legoman.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/legoman.cpp.s
.PHONY : src/legoman.cpp.s

src/light.o: src/light.cpp.o

.PHONY : src/light.o

# target to build an object file
src/light.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/light.cpp.o
.PHONY : src/light.cpp.o

src/light.i: src/light.cpp.i

.PHONY : src/light.i

# target to preprocess a source file
src/light.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/light.cpp.i
.PHONY : src/light.cpp.i

src/light.s: src/light.cpp.s

.PHONY : src/light.s

# target to generate assembly for a file
src/light.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/light.cpp.s
.PHONY : src/light.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/material.o: src/material.cpp.o

.PHONY : src/material.o

# target to build an object file
src/material.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/material.cpp.o
.PHONY : src/material.cpp.o

src/material.i: src/material.cpp.i

.PHONY : src/material.i

# target to preprocess a source file
src/material.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/material.cpp.i
.PHONY : src/material.cpp.i

src/material.s: src/material.cpp.s

.PHONY : src/material.s

# target to generate assembly for a file
src/material.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/material.cpp.s
.PHONY : src/material.cpp.s

src/menu.o: src/menu.cpp.o

.PHONY : src/menu.o

# target to build an object file
src/menu.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/menu.cpp.o
.PHONY : src/menu.cpp.o

src/menu.i: src/menu.cpp.i

.PHONY : src/menu.i

# target to preprocess a source file
src/menu.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/menu.cpp.i
.PHONY : src/menu.cpp.i

src/menu.s: src/menu.cpp.s

.PHONY : src/menu.s

# target to generate assembly for a file
src/menu.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/menu.cpp.s
.PHONY : src/menu.cpp.s

src/mesh.o: src/mesh.cpp.o

.PHONY : src/mesh.o

# target to build an object file
src/mesh.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/mesh.cpp.o
.PHONY : src/mesh.cpp.o

src/mesh.i: src/mesh.cpp.i

.PHONY : src/mesh.i

# target to preprocess a source file
src/mesh.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/mesh.cpp.i
.PHONY : src/mesh.cpp.i

src/mesh.s: src/mesh.cpp.s

.PHONY : src/mesh.s

# target to generate assembly for a file
src/mesh.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/mesh.cpp.s
.PHONY : src/mesh.cpp.s

src/object.o: src/object.cpp.o

.PHONY : src/object.o

# target to build an object file
src/object.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/object.cpp.o
.PHONY : src/object.cpp.o

src/object.i: src/object.cpp.i

.PHONY : src/object.i

# target to preprocess a source file
src/object.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/object.cpp.i
.PHONY : src/object.cpp.i

src/object.s: src/object.cpp.s

.PHONY : src/object.s

# target to generate assembly for a file
src/object.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/object.cpp.s
.PHONY : src/object.cpp.s

src/objectfactory.o: src/objectfactory.cpp.o

.PHONY : src/objectfactory.o

# target to build an object file
src/objectfactory.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/objectfactory.cpp.o
.PHONY : src/objectfactory.cpp.o

src/objectfactory.i: src/objectfactory.cpp.i

.PHONY : src/objectfactory.i

# target to preprocess a source file
src/objectfactory.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/objectfactory.cpp.i
.PHONY : src/objectfactory.cpp.i

src/objectfactory.s: src/objectfactory.cpp.s

.PHONY : src/objectfactory.s

# target to generate assembly for a file
src/objectfactory.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/objectfactory.cpp.s
.PHONY : src/objectfactory.cpp.s

src/particle.o: src/particle.cpp.o

.PHONY : src/particle.o

# target to build an object file
src/particle.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/particle.cpp.o
.PHONY : src/particle.cpp.o

src/particle.i: src/particle.cpp.i

.PHONY : src/particle.i

# target to preprocess a source file
src/particle.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/particle.cpp.i
.PHONY : src/particle.cpp.i

src/particle.s: src/particle.cpp.s

.PHONY : src/particle.s

# target to generate assembly for a file
src/particle.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/particle.cpp.s
.PHONY : src/particle.cpp.s

src/run.o: src/run.cpp.o

.PHONY : src/run.o

# target to build an object file
src/run.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/run.cpp.o
.PHONY : src/run.cpp.o

src/run.i: src/run.cpp.i

.PHONY : src/run.i

# target to preprocess a source file
src/run.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/run.cpp.i
.PHONY : src/run.cpp.i

src/run.s: src/run.cpp.s

.PHONY : src/run.s

# target to generate assembly for a file
src/run.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/run.cpp.s
.PHONY : src/run.cpp.s

src/shape.o: src/shape.cpp.o

.PHONY : src/shape.o

# target to build an object file
src/shape.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/shape.cpp.o
.PHONY : src/shape.cpp.o

src/shape.i: src/shape.cpp.i

.PHONY : src/shape.i

# target to preprocess a source file
src/shape.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/shape.cpp.i
.PHONY : src/shape.cpp.i

src/shape.s: src/shape.cpp.s

.PHONY : src/shape.s

# target to generate assembly for a file
src/shape.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/shape.cpp.s
.PHONY : src/shape.cpp.s

src/sphere.o: src/sphere.cpp.o

.PHONY : src/sphere.o

# target to build an object file
src/sphere.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/sphere.cpp.o
.PHONY : src/sphere.cpp.o

src/sphere.i: src/sphere.cpp.i

.PHONY : src/sphere.i

# target to preprocess a source file
src/sphere.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/sphere.cpp.i
.PHONY : src/sphere.cpp.i

src/sphere.s: src/sphere.cpp.s

.PHONY : src/sphere.s

# target to generate assembly for a file
src/sphere.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/sphere.cpp.s
.PHONY : src/sphere.cpp.s

src/texture.o: src/texture.cpp.o

.PHONY : src/texture.o

# target to build an object file
src/texture.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/texture.cpp.o
.PHONY : src/texture.cpp.o

src/texture.i: src/texture.cpp.i

.PHONY : src/texture.i

# target to preprocess a source file
src/texture.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/texture.cpp.i
.PHONY : src/texture.cpp.i

src/texture.s: src/texture.cpp.s

.PHONY : src/texture.s

# target to generate assembly for a file
src/texture.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/texture.cpp.s
.PHONY : src/texture.cpp.s

src/utils.o: src/utils.cpp.o

.PHONY : src/utils.o

# target to build an object file
src/utils.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/utils.cpp.o
.PHONY : src/utils.cpp.o

src/utils.i: src/utils.cpp.i

.PHONY : src/utils.i

# target to preprocess a source file
src/utils.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/utils.cpp.i
.PHONY : src/utils.cpp.i

src/utils.s: src/utils.cpp.s

.PHONY : src/utils.s

# target to generate assembly for a file
src/utils.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/utils.cpp.s
.PHONY : src/utils.cpp.s

src/vector.o: src/vector.cpp.o

.PHONY : src/vector.o

# target to build an object file
src/vector.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/vector.cpp.o
.PHONY : src/vector.cpp.o

src/vector.i: src/vector.cpp.i

.PHONY : src/vector.i

# target to preprocess a source file
src/vector.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/vector.cpp.i
.PHONY : src/vector.cpp.i

src/vector.s: src/vector.cpp.s

.PHONY : src/vector.s

# target to generate assembly for a file
src/vector.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/vector.cpp.s
.PHONY : src/vector.cpp.s

src/world.o: src/world.cpp.o

.PHONY : src/world.o

# target to build an object file
src/world.cpp.o:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/world.cpp.o
.PHONY : src/world.cpp.o

src/world.i: src/world.cpp.i

.PHONY : src/world.i

# target to preprocess a source file
src/world.cpp.i:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/world.cpp.i
.PHONY : src/world.cpp.i

src/world.s: src/world.cpp.s

.PHONY : src/world.s

# target to generate assembly for a file
src/world.cpp.s:
	$(MAKE) -f CMakeFiles/blockofighter.dir/build.make CMakeFiles/blockofighter.dir/src/world.cpp.s
.PHONY : src/world.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... blockofighter"
	@echo "... edit_cache"
	@echo "... src/3dutils.o"
	@echo "... src/3dutils.i"
	@echo "... src/3dutils.s"
	@echo "... src/appearance.o"
	@echo "... src/appearance.i"
	@echo "... src/appearance.s"
	@echo "... src/audio.o"
	@echo "... src/audio.i"
	@echo "... src/audio.s"
	@echo "... src/camera.o"
	@echo "... src/camera.i"
	@echo "... src/camera.s"
	@echo "... src/collision.o"
	@echo "... src/collision.i"
	@echo "... src/collision.s"
	@echo "... src/end.o"
	@echo "... src/end.i"
	@echo "... src/end.s"
	@echo "... src/fight.o"
	@echo "... src/fight.i"
	@echo "... src/fight.s"
	@echo "... src/fonct.o"
	@echo "... src/fonct.i"
	@echo "... src/fonct.s"
	@echo "... src/font.o"
	@echo "... src/font.i"
	@echo "... src/font.s"
	@echo "... src/glapi.o"
	@echo "... src/glapi.i"
	@echo "... src/glapi.s"
	@echo "... src/graphics.o"
	@echo "... src/graphics.i"
	@echo "... src/graphics.s"
	@echo "... src/legoblocks.o"
	@echo "... src/legoblocks.i"
	@echo "... src/legoblocks.s"
	@echo "... src/legoman.o"
	@echo "... src/legoman.i"
	@echo "... src/legoman.s"
	@echo "... src/light.o"
	@echo "... src/light.i"
	@echo "... src/light.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/material.o"
	@echo "... src/material.i"
	@echo "... src/material.s"
	@echo "... src/menu.o"
	@echo "... src/menu.i"
	@echo "... src/menu.s"
	@echo "... src/mesh.o"
	@echo "... src/mesh.i"
	@echo "... src/mesh.s"
	@echo "... src/object.o"
	@echo "... src/object.i"
	@echo "... src/object.s"
	@echo "... src/objectfactory.o"
	@echo "... src/objectfactory.i"
	@echo "... src/objectfactory.s"
	@echo "... src/particle.o"
	@echo "... src/particle.i"
	@echo "... src/particle.s"
	@echo "... src/run.o"
	@echo "... src/run.i"
	@echo "... src/run.s"
	@echo "... src/shape.o"
	@echo "... src/shape.i"
	@echo "... src/shape.s"
	@echo "... src/sphere.o"
	@echo "... src/sphere.i"
	@echo "... src/sphere.s"
	@echo "... src/texture.o"
	@echo "... src/texture.i"
	@echo "... src/texture.s"
	@echo "... src/utils.o"
	@echo "... src/utils.i"
	@echo "... src/utils.s"
	@echo "... src/vector.o"
	@echo "... src/vector.i"
	@echo "... src/vector.s"
	@echo "... src/world.o"
	@echo "... src/world.i"
	@echo "... src/world.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

