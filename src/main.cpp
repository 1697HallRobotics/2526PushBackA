#include "main.h"

const int32_t DEADZONE = 3;
const float speed = 1;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
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

int quadrant = 0;
	while (true)
	{
		//if there is a pneumatics system someone needs to code it!!! I can't figure out how

    pros::delay(5);
  }
}

void brake() {
  drive_rf.brake();
  drive_rb.brake();
  drive_lf.brake();
  drive_lb.brake();
}
