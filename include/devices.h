#ifndef _DEVICES_H_
#define _DEVICES_H_

#include "api.h"

using namespace pros;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

#define LEFT_MOTOR_PORTS {9, 10}
#define RIGHT_MOTOR_PORTS {-11, -12}
#define INTAKE_PORTS {4, -3}
#define INTAKE_PNEUMATIC_PORTS {'e'}

#define L1_OUTTAKE_PORTS {-17,18}
#define L2_OUTTAKE_PORTS {-17,-18,19}
#define L3_OUTTAKE_PORTS {-17,-18,-19}

pros::MotorGroup left_mg(LEFT_MOTOR_PORTS);
pros::MotorGroup right_mg(RIGHT_MOTOR_PORTS);
pros::MotorGroup intake_mg(INTAKE_PORTS);
pros::adi::Pneumatics intake_pneum(INTAKE_PNEUMATIC_PORTS, 1, 1);

pros::MotorGroup l1_out(L1_OUTTAKE_PORTS);
pros::MotorGroup l2_out(L2_OUTTAKE_PORTS);
pros::MotorGroup l3_out(L3_OUTTAKE_PORTS);

#endif