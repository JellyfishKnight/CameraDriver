#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/wjy/CameraDriverWS/src/vision_opencv/cv_bridge"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/wjy/CameraDriverWS/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/wjy/CameraDriverWS/install/lib/python3/dist-packages:/home/wjy/CameraDriverWS/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/wjy/CameraDriverWS/build" \
    "/usr/bin/python3" \
    "/home/wjy/CameraDriverWS/src/vision_opencv/cv_bridge/setup.py" \
    egg_info --egg-base /home/wjy/CameraDriverWS/build/vision_opencv/cv_bridge \
    build --build-base "/home/wjy/CameraDriverWS/build/vision_opencv/cv_bridge" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/wjy/CameraDriverWS/install" --install-scripts="/home/wjy/CameraDriverWS/install/bin"
