#ifndef _DEVICES_H_
#define _DEVICES_H_

#include "api.h"

using namespace pros;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

#define RIGHT_FRONT -1
#define RIGHT_BACK -2
#define LEFT_FRONT 3
#define LEFT_BACK 4

#define INTAKE_PORTS {5, -6}
#define INTAKE_PNEUMATIC_PORTS {'a'}

#define L1_OUTTAKE_PORTS {-17,18}
#define L2_OUTTAKE_PORTS {-17,-18,19}
#define L3_OUTTAKE_PORTS {-17,-18,-19}

pros::Motor drive_rf(RIGHT_FRONT);
pros::Motor drive_rb(RIGHT_BACK);
pros::Motor drive_lf(LEFT_FRONT);
pros::Motor drive_lb(LEFT_BACK);

pros::MotorGroup intake_mg(INTAKE_PORTS);
pros::adi::Pneumatics intake_pneum(INTAKE_PNEUMATIC_PORTS, 1, 1);

pros::MotorGroup l1_out(L1_OUTTAKE_PORTS);
pros::MotorGroup l2_out(L2_OUTTAKE_PORTS);
pros::MotorGroup l3_out(L3_OUTTAKE_PORTS);

#endif