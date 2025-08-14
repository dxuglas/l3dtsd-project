#include "devices.h"
#include "../include/robot/chassis.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/rotation.hpp"
#include "robot/tracking/tracking_wheel.h"

Chassis chassis({-12, -14, -13}, {18, 19, 20}, 0.1, 0.1);

pros::Rotation left_h_rotation(16);
TrackingWheel left_h_wheel(&left_h_rotation, 2.0, -1.75);

pros::Rotation right_h_rotation(-15);
TrackingWheel right_h_wheel(&right_h_rotation, 2.0, 1.75);

pros::Rotation v_rotation(3);
TrackingWheel v_wheel(&v_rotation, 2.0, 1);

pros::IMU left_imu(11);
pros::Distance block_detector(1);

pros::Motor indexer(10);
pros::Motor front_rollers(4);
pros::Motor top_rollers(5);
pros::Motor bin_control(6);

pros::adi::Pneumatics match_load_ramp('A', false);

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::adi::DigitalOut indexer_led_left('B');
pros::adi::DigitalOut indexer_led_right('C');
