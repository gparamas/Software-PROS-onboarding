#include "main.h"


void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello PROS User!");
}

void disabled() {}


void competition_initialize() {}


void autonomous() {}

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mtr({1, 2});
pros::MotorGroup right_mtr({15, 17});

void display_task() {
    pros::Task task([]{ // this is a lambda -> https://en.cppreference.com/w/cpp/language/lambda
        while(true) {
            //display motor position
            pros::lcd::print(1, "left motor group pos: %lf", left_mtr.get_position(), 2);
            pros::lcd::print(3, "right motor group pos: %lf", right_mtr.get_position(), 4);

            // display motor velocity
            pros::lcd::print(5, "left motor group vel: %lf", left_mtr.get_actual_velocity(), 6);
            pros::lcd::print(7, "right motor group vel: %lf", right_mtr.get_actual_velocity(), 8);

            pros::delay(100);// delay for context switching
        }
    });
}

void opcontrol() {
    // spawn display task
    display_task();

    // opcontrol while loop
    while(true) {
        left_mtr.move(-1 * controller.get_analog(ANALOG_LEFT_Y));
        right_mtr.move(controller.get_analog(ANALOG_RIGHT_Y));
        pros::delay(10);// delay for context switching
    }
}