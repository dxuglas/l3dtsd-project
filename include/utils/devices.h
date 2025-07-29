#ifndef DEVICES_H
#define DEVICES_H

#include "pros/adi.hpp"
#include "pros/rotation.hpp"
#include "robot/chassis.h"
#include "robot/tracking/tracking_wheel.h"

extern Chassis chassis;
extern pros::Rotation left_h_rotation, right_h_rotation;
extern TrackingWheel left_h_wheel, right_h_wheel, v_wheel;
extern pros::IMU left_imu;

extern pros::Motor indexer, front_rollers, top_rollers;
extern pros::adi::Pneumatics match_load_ramp;
extern pros::Controller master;
extern pros::adi::DigitalOut indexer_led_left, indexer_led_right;

#endif