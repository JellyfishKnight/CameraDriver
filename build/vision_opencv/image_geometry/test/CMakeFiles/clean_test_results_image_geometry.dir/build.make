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

# Utility rule file for clean_test_results_image_geometry.

# Include any custom commands dependencies for this target.
include vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/compiler_depend.make

# Include the progress variables for this target.
include vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/progress.make

vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry:
	cd /home/wjy/CameraDriverWS/build/vision_opencv/image_geometry/test && /usr/bin/python3 /opt/ros/noetic/share/catkin/cmake/test/remove_test_results.py /home/wjy/CameraDriverWS/build/test_results/image_geometry

clean_test_results_image_geometry: vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry
clean_test_results_image_geometry: vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/build.make
.PHONY : clean_test_results_image_geometry

# Rule to build all files generated by this target.
vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/build: clean_test_results_image_geometry
.PHONY : vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/build

vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/clean:
	cd /home/wjy/CameraDriverWS/build/vision_opencv/image_geometry/test && $(CMAKE_COMMAND) -P CMakeFiles/clean_test_results_image_geometry.dir/cmake_clean.cmake
.PHONY : vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/clean

vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/depend:
	cd /home/wjy/CameraDriverWS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wjy/CameraDriverWS/src /home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test /home/wjy/CameraDriverWS/build /home/wjy/CameraDriverWS/build/vision_opencv/image_geometry/test /home/wjy/CameraDriverWS/build/vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vision_opencv/image_geometry/test/CMakeFiles/clean_test_results_image_geometry.dir/depend

