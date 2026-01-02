
#include "globals.hpp"

//motors
pros::Motor intake1Motor(20,pros::v5::MotorGears::blue);
pros::Motor intake2Motor(-13,pros::v5::MotorGears::blue);  

//pneumatics
pros::adi::Pneumatics toungue('A', false);
pros::adi::Pneumatics wing('B', false);
//pros::adi::Pneumatics door('A', false);

//sensors
//pros::Imu imu2(19); //secondary imu sensor

