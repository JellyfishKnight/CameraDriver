# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/wjy/CMAKE/cmake-3.24.0-rc2-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/wjy/CMAKE/cmake-3.24.0-rc2-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wjy/CameraDriverWS/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wjy/CameraDriverWS/build

# Include any dependencies generated for this target.
include MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/compiler_depend.make

# Include the progress variables for this target.
include MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/progress.make

# Include the compile flags for this target's objects.
include MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/flags.make

MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.o: MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/flags.make
MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.o: /home/wjy/CameraDriverWS/src/MindVision_pkg/include/MindVisionClass/MindVision.cpp
MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.o: MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wjy/CameraDriverWS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.o"
	cd /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.o -MF CMakeFiles/MindVisionClass.dir/MindVision.cpp.o.d -o CMakeFiles/MindVisionClass.dir/MindVision.cpp.o -c /home/wjy/CameraDriverWS/src/MindVision_pkg/include/MindVisionClass/MindVision.cpp

MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MindVisionClass.dir/MindVision.cpp.i"
	cd /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wjy/CameraDriverWS/src/MindVision_pkg/include/MindVisionClass/MindVision.cpp > CMakeFiles/MindVisionClass.dir/MindVision.cpp.i

MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MindVisionClass.dir/MindVision.cpp.s"
	cd /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wjy/CameraDriverWS/src/MindVision_pkg/include/MindVisionClass/MindVision.cpp -o CMakeFiles/MindVisionClass.dir/MindVision.cpp.s

# Object files for target MindVisionClass
MindVisionClass_OBJECTS = \
"CMakeFiles/MindVisionClass.dir/MindVision.cpp.o"

# External object files for target MindVisionClass
MindVisionClass_EXTERNAL_OBJECTS =

/home/wjy/CameraDriverWS/devel/lib/libMindVisionClass.so: MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/MindVision.cpp.o
/home/wjy/CameraDriverWS/devel/lib/libMindVisionClass.so: MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/build.make
/home/wjy/CameraDriverWS/devel/lib/libMindVisionClass.so: MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wjy/CameraDriverWS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/wjy/CameraDriverWS/devel/lib/libMindVisionClass.so"
	cd /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MindVisionClass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/build: /home/wjy/CameraDriverWS/devel/lib/libMindVisionClass.so
.PHONY : MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/build

MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/clean:
	cd /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass && $(CMAKE_COMMAND) -P CMakeFiles/MindVisionClass.dir/cmake_clean.cmake
.PHONY : MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/clean

MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/depend:
	cd /home/wjy/CameraDriverWS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjy/CameraDriverWS/src /home/wjy/CameraDriverWS/src/MindVision_pkg/include/MindVisionClass /home/wjy/CameraDriverWS/build /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass /home/wjy/CameraDriverWS/build/MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MindVision_pkg/include/MindVisionClass/CMakeFiles/MindVisionClass.dir/depend

