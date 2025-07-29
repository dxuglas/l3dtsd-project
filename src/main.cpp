#include "main.h"
#include "../include/utils/devices.h"
#include "pros/misc.h"
#include "test.h"

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
            print_odometry_debug();
            pros::delay(10);
        }
    });
}

void competition_initialize() {}

void disabled() {}

void autonomous() {}

void opcontrol() {
    chassis.start_odometry();
    int loader_countdown = 0;
    int indexer_direction_cooldown = 0;
    int indexer_direction = 1;
	while (true) {
        chassis.tank(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            front_rollers.move(127);
            indexer.move(127*indexer_direction);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            front_rollers.move(-127);
            indexer.move(-127*indexer_direction);
        } else {
            front_rollers.move(0);
            indexer.move(0);

        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            top_rollers.move(127);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            top_rollers.move(-127);
        } else {
            top_rollers.move(0);
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && loader_countdown < 0) {
            match_load_ramp.toggle();
            loader_countdown = 10;
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && indexer_direction_cooldown < 0) {
            indexer_direction *= -1;
            indexer_direction_cooldown = 10;
        }

        indexer_led_left.set_value(indexer_direction > 0 ? 0 : -indexer_direction);
        indexer_led_right.set_value(indexer_direction > 0 ? 0 : -indexer_direction);
        loader_countdown--;
        indexer_direction_cooldown--;
		pros::delay(20);                               // Run for 20 ms then update
	}
}