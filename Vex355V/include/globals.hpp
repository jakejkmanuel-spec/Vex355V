
#pragma once
#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "lemlib/chassis/chassis.hpp" 
#include "pros/distance.hpp"

//motors
extern pros::Motor intake1Motor;
extern pros::Motor intake2Motor;
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;

// //pnematics
 extern pros::adi::Pneumatics toungue;
 extern pros::adi::Pneumatics wing;
 extern pros::adi::Pneumatics flap;

 //sensors
extern pros::Distance distSensorLeft;
extern pros::Distance distSensorRight;

//extern pros::Imu imu2;

// //potentiometer
// extern pros::ADIAnalogIn aSelector;

// extern pros::adi::Pneumatics doinker;
