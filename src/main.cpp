#include "main.h"

#define LEFT_MOTOR_PORTS {1, 2}
#define RIGHT_MOTOR_PORTS {3, 4}
#define INTAKE_PORTS {5, -6}

const float DEADZONE = 3;


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::MotorGroup left_mg(LEFT_MOTOR_PORTS);
  pros::MotorGroup right_mg(RIGHT_MOTOR_PORTS);
  pros::MotorGroup intake_mg(INTAKE_PORTS);
  left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intake_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  while (1) {
    int dir = master.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
    int turn = master.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick

    // if joystick is in deadzone, it counts as zero
    // prevents unintentional drift
    if (abs(dir) < DEADZONE)
      dir = 0;
    if (abs(turn) < DEADZONE)
      turn = 0;

    if (dir && turn == 0) {
      left_mg.brake();
      right_mg.brake();
    } else {
      left_mg.move(dir - turn);  // Sets left motor voltage
      right_mg.move(dir + turn); // Sets right motor voltage
    }

    if (master.get_digital(DIGITAL_R2))
      intake_mg.move(127);
    if (master.get_digital(DIGITAL_R1))
      intake_mg.move(-127);
    if (master.get_digital(DIGITAL_R1) == master.get_digital(DIGITAL_R2))
      intake_mg.brake();

    pros::delay(2);
  }
}