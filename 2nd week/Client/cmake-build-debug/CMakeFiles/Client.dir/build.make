# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/main.cpp.obj: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Client.dir\main.cpp.obj -c "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\main.cpp"

CMakeFiles/Client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\main.cpp" > CMakeFiles\Client.dir\main.cpp.i

CMakeFiles/Client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\main.cpp" -o CMakeFiles\Client.dir\main.cpp.s

CMakeFiles/Client.dir/Client.cpp.obj: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Client.cpp.obj: ../Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Client.dir/Client.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Client.dir\Client.cpp.obj -c "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\Client.cpp"

CMakeFiles/Client.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Client.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\Client.cpp" > CMakeFiles\Client.dir\Client.cpp.i

CMakeFiles/Client.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Client.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\Client.cpp" -o CMakeFiles\Client.dir\Client.cpp.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/main.cpp.obj" \
"CMakeFiles/Client.dir/Client.cpp.obj"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client.exe: CMakeFiles/Client.dir/main.cpp.obj
Client.exe: CMakeFiles/Client.dir/Client.cpp.obj
Client.exe: CMakeFiles/Client.dir/build.make
Client.exe: CMakeFiles/Client.dir/linklibs.rsp
Client.exe: CMakeFiles/Client.dir/objects1.rsp
Client.exe: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Client.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Client.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: Client.exe

.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Client.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client" "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client" "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug" "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug" "C:\Users\Alex\Documents\GitHub\-Internship\2nd week\Client\cmake-build-debug\CMakeFiles\Client.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Client.dir/depend

