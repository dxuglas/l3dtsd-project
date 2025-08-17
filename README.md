
# Odometry Tracking System

This repository is a clone of dxuglas/pushback-8757b, modified for refrence in my L3 DTSD Project.

Source code is this repository WILL NOT COMPILE, as it is missing key dependencies (PROS) and a lot device management code written by me. 

It ONLY contains the code for the odometry tracking system itself, to help make it clear to anyone marking what code is included in the scope of my project, and to prevent them from having to explore deeply nested directories to ensure they have found all of my code. However it WILL NOT WORK in isolation as it is here. To better understand the systems real world implementations,
refer to the repository referenced above. 

My program is designed for use by experienced VEX V5 Robotics Competition participants. It is a violation of the RECF Student Centered Policy if you use this outcome without fully understanding how it works. 
If you are looking to gain an understanding of how odometry works, I would recommend watching/reading all of the guides listed below. 

[What is Odometry - Rex Liu](https://www.youtube.com/watch?v=GEZBYHVHmFQ&list=PLsTj2tgnvJ8Qm96AQsrS2ehwexOj03Try)

[Odometry - Queen's VEX U Robotics](https://www.youtube.com/watch?v=_T6KHywSP58)

[Odometry - Purdue SigBots](https://wiki.purduesigbots.com/software/odometry)

Assuming you understand the fundamentals, implementing my program should be relatively easy. 

## Installation

This program is dependant on PROS, developed by Purdue Sigbots. However it is not distributed with it. To install the program, simply create a project in PROS and then clone this repository and copy the include and src files into their respective directories. 

## Documentation

The first step is to setup your tracking wheels and sensors. You can (mostly) use as many or as few as you want. Atleast one wheel is needed, and then either an IMU or a second tracking wheel.

```cpp
// Tracking Wheel
TrackingWheel horizontal_wheel(sensor_reference, wheel_diameter, offset);

// IMU
pros::IMU imu(imu_port);
```

```sensor_reference```: A refrence to either a V5 Rotation sensor or Quad Encoder\
```wheel_diameter```: The diameter of your tracking wheel.\
```offset```: The offset of the tracking wheel from the tracking center.\
```imu_port```: Digital port the IMU is connected to.

The next step is to configure the Odometry system.
```cpp
// Create an odometry object
Odoemtry odometry;

// Create a pose starting a (0,0) with heading 0rad
Pose pose = (0.0f, 0.0f, 0.0f)

odometry.configure(
    horizontal_wheel_vector, vertical_wheel_vector
    imu_vector, p, r, q
)
```
```horizontal_wheel_vector```: a vector of references to horizontal tracking wheel references (i.e. ```{&right_h_wheel, &left_h_wheel}```).\
```vertical_wheel_vector```: a vector of references to vertical tracking wheel references (i.e. ```{&vertical_wheel}```). Can be left empty.\
```imu_vector```: a vector of IMU references (i.e. ```{&imu_1, &imu_2}```)\
```p```: uncertantiy of heading data (optional)\
```r```: expected noise of heading data (optional)\
```q```: expected process noise (optional)

p, r, and q represent inputs for the kalman filter which is used to fuse different heading data sources. It is recommended you leave these empty unless you know what you are doing, as tuning them incorrectly can ruin any accuracy in the system. Default values are provided. 

The last step to begin odometry tracking is to start the system inside a task. It must be run in a task to allow other functions to run simultaniously. 
```cpp
// Start odometry tracking
odometry_task = pros::Task([delay] { odometry.update(pose, delay);
```
```delay```: The delay between odometry updates in milliseconds. Recommend 10.\
```pose```: The pose to be updated (which you set up earlier)
