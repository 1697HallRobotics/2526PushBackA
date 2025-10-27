#include "main.h"

const int32_t DEADZONE = 3;
const float speed = 1;

/**
 * initialize -> competition initialize -> autonomous -> disabled -> op control -> disabled
 */

/**
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  drive_rf.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  drive_rb.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  drive_lf.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  drive_lb.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  intake_mg.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  l3_out.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void disabled() {
  brake();
}

/**
 * This is intended for competition-specific initialization routines, 
 * such as an autonomous selector on the LCD.
 */
void competition_initialize() {}

void autonomous() {}

void operator_ctrl() {
  pros::Controller* controller = partner.is_connected() ? &partner : &master;

  if (controller->get_digital(DIGITAL_R2))
      intake_mg.move(127);
  if (controller->get_digital(DIGITAL_R1))
    intake_mg.move(-127);
  if (controller->get_digital(DIGITAL_R1) == controller->get_digital(DIGITAL_R2))
    intake_mg.brake();
  
  if (controller->get_digital_new_release(DIGITAL_X))
    intake_pneum.toggle();
  if (controller->get_digital(DIGITAL_A))
    intake_pneum.extend();
  if (controller->get_digital(DIGITAL_B))
    intake_pneum.retract();
  
  if(controller->get_digital(DIGITAL_DOWN))
    l1_out.move(127);
  if(controller->get_digital(DIGITAL_LEFT))
    l2_out.move(127);
  if(controller->get_digital(DIGITAL_UP))
    l3_out.move(127);
  if(controller->get_digital(DIGITAL_RIGHT))
    l1_out.move(-127);
  if(controller->get_digital(DIGITAL_DOWN) + controller->get_digital(DIGITAL_LEFT) + controller->get_digital(DIGITAL_RIGHT) + controller->get_digital(DIGITAL_UP) > 1)
    l3_out.brake();
}

void opcontrol() {

  while (1) {
    int32_t dir_y = master.get_analog(ANALOG_LEFT_Y);
    int32_t dir_x = master.get_analog(ANALOG_LEFT_Y);
    int32_t turn = master.get_analog(ANALOG_RIGHT_X);

    float dir_mult = 127 * speed / (abs(dir_y) + abs(dir_x));

    // if joystick is in deadzone, it counts as zero (prevents unintentional drift)

    dir_y *= abs(dir_y) > DEADZONE;
    turn *= abs(turn) > DEADZONE;

    if (dir_y || dir_x || turn) {
      drive_rf.move((dir_y + dir_x) * dir_mult - turn);
      drive_rb.move((dir_y - dir_x) * dir_mult - turn);
      drive_lf.move((dir_y - dir_x) * dir_mult + turn);
      drive_lb.move((dir_y + dir_x) * dir_mult + turn); 
    } else {
      brake();
    }

    operator_ctrl();

    pros::delay(5);
  }
}

void brake() {
  drive_rf.brake();
  drive_rb.brake();
  drive_lf.brake();
  drive_lb.brake();
}