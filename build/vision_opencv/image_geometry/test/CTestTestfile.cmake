# CMake generated Testfile for 
# Source directory: /home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test
# Build directory: /home/wjy/CameraDriverWS/build/vision_opencv/image_geometry/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_image_geometry_nosetests_directed.py "/home/wjy/CameraDriverWS/build/catkin_generated/env_cached.sh" "/usr/bin/python3" "/opt/ros/noetic/share/catkin/cmake/test/run_tests.py" "/home/wjy/CameraDriverWS/build/test_results/image_geometry/nosetests-directed.py.xml" "--return-code" "\"/home/wjy/CMAKE/cmake-3.24.0-rc2-linux-x86_64/bin/cmake\" -E make_directory /home/wjy/CameraDriverWS/build/test_results/image_geometry" "/usr/bin/nosetests3 -P --process-timeout=60 /home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/directed.py --with-xunit --xunit-file=/home/wjy/CameraDriverWS/build/test_results/image_geometry/nosetests-directed.py.xml")
set_tests_properties(_ctest_image_geometry_nosetests_directed.py PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/catkin/cmake/test/tests.cmake;160;add_test;/opt/ros/noetic/share/catkin/cmake/test/nosetests.cmake;83;catkin_run_tests_target;/home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/CMakeLists.txt;1;catkin_add_nosetests;/home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/CMakeLists.txt;0;")
add_test(_ctest_image_geometry_gtest_image_geometry-utest "/home/wjy/CameraDriverWS/build/catkin_generated/env_cached.sh" "/usr/bin/python3" "/opt/ros/noetic/share/catkin/cmake/test/run_tests.py" "/home/wjy/CameraDriverWS/build/test_results/image_geometry/gtest-image_geometry-utest.xml" "--return-code" "/home/wjy/CameraDriverWS/devel/lib/image_geometry/image_geometry-utest --gtest_output=xml:/home/wjy/CameraDriverWS/build/test_results/image_geometry/gtest-image_geometry-utest.xml")
set_tests_properties(_ctest_image_geometry_gtest_image_geometry-utest PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/catkin/cmake/test/tests.cmake;160;add_test;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;98;catkin_run_tests_target;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;37;_catkin_add_google_test;/home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/CMakeLists.txt;3;catkin_add_gtest;/home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/CMakeLists.txt;0;")
add_test(_ctest_image_geometry_gtest_image_geometry-utest-equi "/home/wjy/CameraDriverWS/build/catkin_generated/env_cached.sh" "/usr/bin/python3" "/opt/ros/noetic/share/catkin/cmake/test/run_tests.py" "/home/wjy/CameraDriverWS/build/test_results/image_geometry/gtest-image_geometry-utest-equi.xml" "--return-code" "/home/wjy/CameraDriverWS/devel/lib/image_geometry/image_geometry-utest-equi --gtest_output=xml:/home/wjy/CameraDriverWS/build/test_results/image_geometry/gtest-image_geometry-utest-equi.xml")
set_tests_properties(_ctest_image_geometry_gtest_image_geometry-utest-equi PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/catkin/cmake/test/tests.cmake;160;add_test;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;98;catkin_run_tests_target;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;37;_catkin_add_google_test;/home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/CMakeLists.txt;6;catkin_add_gtest;/home/wjy/CameraDriverWS/src/vision_opencv/image_geometry/test/CMakeLists.txt;0;")
