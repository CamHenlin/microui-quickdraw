# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/camh/Documents/Retro68kApps/MicroUIQuickDraw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build

# Include any dependencies generated for this target.
include CMakeFiles/MicroUIQuickDraw.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MicroUIQuickDraw.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MicroUIQuickDraw.dir/flags.make

CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.obj: CMakeFiles/MicroUIQuickDraw.dir/flags.make
CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.obj: ../SerialHelper.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.obj"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.obj   -c /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/SerialHelper.c

CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.i"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/SerialHelper.c > CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.i

CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.s"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/SerialHelper.c -o CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.s

CMakeFiles/MicroUIQuickDraw.dir/microui.c.obj: CMakeFiles/MicroUIQuickDraw.dir/flags.make
CMakeFiles/MicroUIQuickDraw.dir/microui.c.obj: ../microui.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MicroUIQuickDraw.dir/microui.c.obj"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MicroUIQuickDraw.dir/microui.c.obj   -c /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/microui.c

CMakeFiles/MicroUIQuickDraw.dir/microui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MicroUIQuickDraw.dir/microui.c.i"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/microui.c > CMakeFiles/MicroUIQuickDraw.dir/microui.c.i

CMakeFiles/MicroUIQuickDraw.dir/microui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MicroUIQuickDraw.dir/microui.c.s"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/microui.c -o CMakeFiles/MicroUIQuickDraw.dir/microui.c.s

CMakeFiles/MicroUIQuickDraw.dir/Sample.c.obj: CMakeFiles/MicroUIQuickDraw.dir/flags.make
CMakeFiles/MicroUIQuickDraw.dir/Sample.c.obj: ../Sample.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MicroUIQuickDraw.dir/Sample.c.obj"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MicroUIQuickDraw.dir/Sample.c.obj   -c /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/Sample.c

CMakeFiles/MicroUIQuickDraw.dir/Sample.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MicroUIQuickDraw.dir/Sample.c.i"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/Sample.c > CMakeFiles/MicroUIQuickDraw.dir/Sample.c.i

CMakeFiles/MicroUIQuickDraw.dir/Sample.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MicroUIQuickDraw.dir/Sample.c.s"
	/home/camh/Retro68-build/toolchain/bin/m68k-apple-macos-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/Sample.c -o CMakeFiles/MicroUIQuickDraw.dir/Sample.c.s

# Object files for target MicroUIQuickDraw
MicroUIQuickDraw_OBJECTS = \
"CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.obj" \
"CMakeFiles/MicroUIQuickDraw.dir/microui.c.obj" \
"CMakeFiles/MicroUIQuickDraw.dir/Sample.c.obj"

# External object files for target MicroUIQuickDraw
MicroUIQuickDraw_EXTERNAL_OBJECTS =

MicroUIQuickDraw.code.bin: CMakeFiles/MicroUIQuickDraw.dir/SerialHelper.c.obj
MicroUIQuickDraw.code.bin: CMakeFiles/MicroUIQuickDraw.dir/microui.c.obj
MicroUIQuickDraw.code.bin: CMakeFiles/MicroUIQuickDraw.dir/Sample.c.obj
MicroUIQuickDraw.code.bin: CMakeFiles/MicroUIQuickDraw.dir/build.make
MicroUIQuickDraw.code.bin: CMakeFiles/MicroUIQuickDraw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable MicroUIQuickDraw.code.bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MicroUIQuickDraw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MicroUIQuickDraw.dir/build: MicroUIQuickDraw.code.bin

.PHONY : CMakeFiles/MicroUIQuickDraw.dir/build

CMakeFiles/MicroUIQuickDraw.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MicroUIQuickDraw.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MicroUIQuickDraw.dir/clean

CMakeFiles/MicroUIQuickDraw.dir/depend:
	cd /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camh/Documents/Retro68kApps/MicroUIQuickDraw /home/camh/Documents/Retro68kApps/MicroUIQuickDraw /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build /home/camh/Documents/Retro68kApps/MicroUIQuickDraw/build/CMakeFiles/MicroUIQuickDraw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MicroUIQuickDraw.dir/depend

