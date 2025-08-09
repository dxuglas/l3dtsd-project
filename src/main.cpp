#include "main.h"
#include "../include/utils/devices.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void initialize() {
    pros::lcd::initialize();
    //pros::delay(2000);
    chassis.configure_odometry(
        {&left_h_wheel, &right_h_wheel}, 
        {}, 
        {&left_imu});
    left_h_wheel.tare();
    right_h_wheel.tare();
    left_imu.tare_heading();
    while (left_imu.is_calibrating()) pros::delay(10);
    pros::Task([&] {
    while (true) {
        auto p = chassis.get_pose();
        pros::lcd::print(0, "X: %f", p.x);
        pros::lcd::print(1, "Y: %f", p.y);
        pros::lcd::print(2, "Theta: %f", p.heading);
        pros::delay(10);
    }
    });
}

void competition_initialize() {}

void disabled() {}

void autonomous() {
    chassis.move(127);
    pros::delay(1000);
    chassis.move(0);
}

void opcontrol() {
    chassis.start_odometry();
    int loader_countdown = 0;
	while (true) {
        chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            front_rollers.move(127);
            indexer.move(127);
            top_rollers.move(24);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            front_rollers.move(127);
            indexer.move(-127);
            if (block_detector.get() < 30) {
                top_rollers.move(-127);
            } else {
                top_rollers.move(127);
            }
            bin_control.move(-127);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            front_rollers.move(127);
            indexer.move(127);
            top_rollers.move(127);
            bin_control.move(127);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            front_rollers.move(-127);
            indexer.move(-127);
            top_rollers.move(-127);
        } else {
            front_rollers.move(0);
            indexer.move(0);
            top_rollers.move(0);
            bin_control.move(-30);
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && loader_countdown < 0) {
            match_load_ramp.toggle();
            loader_countdown = 10;
        }
        loader_countdown--;
		pros::delay(20);                               // Run for 20 ms then update
	}
}
