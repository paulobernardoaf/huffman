# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.1.1\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.1.1\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\paulo\CLionProjects\HuffmanSemVoid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\paulo\CLionProjects\HuffmanSemVoid\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Teste.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Teste.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Teste.dir/flags.make

CMakeFiles/Teste.dir/main.c.obj: CMakeFiles/Teste.dir/flags.make
CMakeFiles/Teste.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\paulo\CLionProjects\HuffmanSemVoid\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Teste.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Teste.dir\main.c.obj   -c C:\Users\paulo\CLionProjects\HuffmanSemVoid\main.c

CMakeFiles/Teste.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Teste.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\paulo\CLionProjects\HuffmanSemVoid\main.c > CMakeFiles\Teste.dir\main.c.i

CMakeFiles/Teste.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Teste.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\paulo\CLionProjects\HuffmanSemVoid\main.c -o CMakeFiles\Teste.dir\main.c.s

CMakeFiles/Teste.dir/main.c.obj.requires:

.PHONY : CMakeFiles/Teste.dir/main.c.obj.requires

CMakeFiles/Teste.dir/main.c.obj.provides: CMakeFiles/Teste.dir/main.c.obj.requires
	$(MAKE) -f CMakeFiles\Teste.dir\build.make CMakeFiles/Teste.dir/main.c.obj.provides.build
.PHONY : CMakeFiles/Teste.dir/main.c.obj.provides

CMakeFiles/Teste.dir/main.c.obj.provides.build: CMakeFiles/Teste.dir/main.c.obj


# Object files for target Teste
Teste_OBJECTS = \
"CMakeFiles/Teste.dir/main.c.obj"

# External object files for target Teste
Teste_EXTERNAL_OBJECTS =

Teste.exe: CMakeFiles/Teste.dir/main.c.obj
Teste.exe: CMakeFiles/Teste.dir/build.make
Teste.exe: CMakeFiles/Teste.dir/linklibs.rsp
Teste.exe: CMakeFiles/Teste.dir/objects1.rsp
Teste.exe: CMakeFiles/Teste.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\paulo\CLionProjects\HuffmanSemVoid\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Teste.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Teste.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Teste.dir/build: Teste.exe

.PHONY : CMakeFiles/Teste.dir/build

CMakeFiles/Teste.dir/requires: CMakeFiles/Teste.dir/main.c.obj.requires

.PHONY : CMakeFiles/Teste.dir/requires

CMakeFiles/Teste.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Teste.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Teste.dir/clean

CMakeFiles/Teste.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\paulo\CLionProjects\HuffmanSemVoid C:\Users\paulo\CLionProjects\HuffmanSemVoid C:\Users\paulo\CLionProjects\HuffmanSemVoid\cmake-build-debug C:\Users\paulo\CLionProjects\HuffmanSemVoid\cmake-build-debug C:\Users\paulo\CLionProjects\HuffmanSemVoid\cmake-build-debug\CMakeFiles\Teste.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Teste.dir/depend

