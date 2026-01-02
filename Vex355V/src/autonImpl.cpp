#include "globals.hpp"
#include "helpers.hpp"
#include "pros/rtos.hpp"

void blueRightAuton(){
    
    chassis.setPose(0,0,0);
        //RIGHTBLUE/RIGHT
    setIntake1(120);
    chassis.moveToPoint(0, 17, 5000, {.maxSpeed = 80});
    chassis.moveToPoint(-8, 30, 5000, {.maxSpeed = 80});
    pros::delay(1000);
    chassis.turnToHeading(-170, 500);
    chassis.moveToPoint(-25, 0, 5000);
    pros::delay(750);

    toungue.extend();

    chassis.turnToHeading(-200, 500);
    chassis.moveToPoint(-19, -11, 1500);
    setIntake1(0);
    pros::delay(300);
    chassis.moveToPoint(-20, -9, 1500, {.forwards = false});
    pros::delay(300);
    chassis.moveToPoint(-20, -15.5, 700, {.maxSpeed = 80});
    pros::delay(500);
    setIntake1(120);
    pros::delay(1600);
    
     //RESET POS AT LOADER
    chassis.setPose(-25,-10,-180);
    chassis.moveToPoint(-23, 34, 1500, {.forwards = false});
    pros::delay(1000);
    setIntake2(120);
    pros::delay(3000);

    setIntake2(0);
    setIntake1(0);
}

void blueLeftAuton(){
    blueRightAuton();
    
}
void redRightAuton(){
    blueRightAuton();
    
}
void  redLeftAuton(){
    blueRightAuton();
    
}
void skillsAuton(){
    
}