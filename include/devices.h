#ifndef _DEVICES_H_
#define _DEVICES_H_

#include "api.h"

using namespace pros;

pros::Controller master(pros::E_CONTROLLER_MASTER);

#define LEFT_MOTOR_PORTS {1, 2}
#define RIGHT_MOTOR_PORTS {3, 4}
#define INTAKE_PORTS {5, -6}
#define INTAKE_PNEUMATIC_PORTS {'a'}

pros::MotorGroup left_mg(LEFT_MOTOR_PORTS);
pros::MotorGroup right_mg(RIGHT_MOTOR_PORTS);
pros::MotorGroup intake_mg(INTAKE_PORTS);
pros::adi::Pneumatics intake_pneum(INTAKE_PNEUMATIC_PORTS, 1, 0);

#endif