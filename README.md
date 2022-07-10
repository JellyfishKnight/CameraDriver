## 基于ROS系统的相机驱动程序

<hr>

**运行环境**:

- OpenCV (version:4.5.4)
- Ubuntu (version:20.04)
- ros (version: noetic)
- MindVision相机驱动 (项目内已经内置)
- cmake (version >= 3.2)

**使用说明:**

0. **_注意:!!!_**

   >**使用前请删除ros自带的cv_bridge文件**

1. **运行ros核心**

   ```bash
   #在第一个终端中运行ros核心
   $ roscore
   ```

2. **进入本文件第一级目录**

   ```bash
   $ cd CameraDriverWS
   ```

3. **编译项目**

   ```bash
   #删除原有的构建文件
   $ rm -rf build devel
   $ catkin_make
   $ source /devel/setup.bash
   #如果是zsh
   $ source /devel/setup.zsh
   ```

4. **运行项目**

   ```bash
   #在第二个终端中运行
   $ rosrun driver_pkg driver_pkg_node
   #在第三个终端中运行
   $ rosrun recognize_pkg recognize_pkg_node
   ```

   **或者直接**
   
   ```bash
   $ roslaunch driver_pkg CameraTest.launch
   ```
   <hr>
  
   **现在可以 source /devel/setup.bash 或者 source /devel/setup.zsh 后直接使用命令行打开clion运行程序**
   

