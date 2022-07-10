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
   
   
<hr>
   
**项目说明:**

工作台中包含以下包:

- _**cv_bridge**_     
   >此包在ros系统内是内置的,但是由于gtk版本原因重新下载编译
- _**driver_pkg**_  
   >此包的内容主要为相机的驱动以及发送相关的信息
- _**receive_pkg**_ 
   >此包的内容主要为一个接收类,作为接收器,使用函数指针向回调函数外传出数据,并且被编译为静态库,无可运行程序
- **_recognize_pkg_**
   >此包的内容主要为识别器,将receive_pkg作为其依赖,实现识别加上单目测距以及姿态解算,但是目前姿态解算部分并未完全得到解决

<hr>   
   
**其他被依赖但是工程中没有的包:**

**_cv_bridge:_**

- boost
- libopencv-dev
- python3
- python3-opencv
- rosconsole

**_其他:_**

- roscpp
- sensor_msgs

