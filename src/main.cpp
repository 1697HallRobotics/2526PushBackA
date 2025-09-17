#include "main.h"

#define LEFT_MOTOR_PORTS {1, 2}
#define RIGHT_MOTOR_PORTS {3, 4}
#define INTAKE_PORTS {5, -6}
#define INTAKE_PNEUMATIC_PORTS {'a'}

const int8_t DEADZONE = 3;

/**
 * initialize -> competition initialize -> autonomous -> disabled -> op control -> disabled
 */

/**
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  intake_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void disabled() {
  left_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  right_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  left_mg.brake();
  right_mg.brake();
}

/**
 * This is intended for competition-specific initialization routines, 
 * such as an autonomous selector on the LCD.
 */
void competition_initialize() {}

void autonomous() {}

void opcontrol() {

  while (1) {
    int32_t dir = master.get_analog(ANALOG_LEFT_Y);
    int32_t turn = master.get_analog(ANALOG_RIGHT_X);

    // if joystick is in deadzone, it counts as zero (prevents unintentional drift)

    dir *= abs(dir) > DEADZONE;
    turn *= abs(turn) > DEADZONE;

    if (dir || turn) {
      left_mg.move(dir - turn);
      right_mg.move(dir + turn);
    } else {
      left_mg.brake();
      right_mg.brake();
    }

    if (master.get_digital(DIGITAL_R2))
      intake_mg.move(127);
    if (master.get_digital(DIGITAL_R1))
      intake_mg.move(-127);
    if (master.get_digital(DIGITAL_R1) == master.get_digital(DIGITAL_R2))
      intake_mg.brake();
    if (master.get_digital(DIGITAL_A))
      intake_pneum.toggle();

    pros::delay(2);
  }
}