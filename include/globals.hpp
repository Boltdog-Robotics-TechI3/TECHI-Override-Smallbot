// chat ;-;
#include "main.h"
#pragma once

inline const double wheelDiameter = 2.75;
inline const double trackWidth = 12.5;
inline const double gearRatio = 1;

// Drivetrain Motors
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup frontLeftDrive({12, -15});
inline pros::MotorGroup frontRightDrive({11, -14}); 
inline pros::MotorGroup backLeftDrive({18, -20});
inline pros::MotorGroup backRightDrive({17, -16});

// Intake
inline pros::Motor intake(5);
inline pros::adi::Pneumatics intakeLift('A', false);

inline XDrivetrain drivetrain(&frontLeftDrive, &frontRightDrive, &backLeftDrive, &backRightDrive, wheelDiameter, trackWidth, gearRatio);

inline pros::IMU imu(8);

inline OdomSensors odometry(&imu);

inline PIDController Lateral(6, 0.015, 5);
inline PIDController Turn(70, .2, 0);

inline XChassis chassis(&drivetrain, &odometry ,&Lateral, &Turn);