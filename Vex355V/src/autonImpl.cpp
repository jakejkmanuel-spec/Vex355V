#include "helpers.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/llemu.hpp" // IWYU pragma: keep
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/rtos.hpp"
#include "autonImpl.hpp"

void blueRightAuton(){
    
    chassis.setPose(0,0,0);
    //RIGHTBLUE/RIGHT
    setIntake1(120);
    chassis.moveToPoint(0, 17, 5000);
    chassis.moveToPoint(-8, 30, 5000);
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
    //distSensorLeft();
    blueRightAuton();
    
}
void redRightAuton(){
    blueRightAuton();
    
}
void  redLeftAuton(){
    blueRightAuton();
    
}
void skillsAuton(){

    //move to loader
    chassis.setPose(0, 9, 90);
    chassis.moveToPoint(49.2, 9, 5000,{.maxSpeed = 70}); 

    pros::delay(500);
    toungue.extend();
  
    pros::delay(100); 
    chassis.turnToHeading ( -180, 5000);
    pros::delay(1000); 

    //distance sensor reset  
   // pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
    //NEED THIS DELAY TO LET POS UPDATE BEFORE TURNING
    float distance = 72-((distSensorLeft.get_distance())/25.4);
    pros::delay(100);
    chassis.setPose(distance,10, 180); 
    //load balls
    setIntake1( 120);
    chassis.moveToPoint(54, 0, 1000, { .maxSpeed = 60});
    chassis.moveToPoint(54, -5, 2000, { .maxSpeed = 20});
    chassis.moveToPoint(54, -7, 3000, { .maxSpeed = 5});
    chassis.moveToPoint(54, -1, 5000, { .forwards = false});
    chassis.moveToPoint(54, -6, 5000, { .maxSpeed = 40});
    pros::delay(700);
    chassis.moveToPoint(54, 10, 5000, { .forwards = false});
    setIntake1(0); 

   
    //move to other side
    chassis.moveToPoint(32, 35, 5000, {.forwards = false,  .minSpeed=62, .earlyExitRange=4}); 
    toungue.retract();
    chassis.moveToPoint(36, 75, 5000, {.forwards = false, .minSpeed=62, .earlyExitRange=2}); //change back to 40
   // chassis.moveToPoint(50, 100, 5000, {.forwards = false, .maxSpeed = 70, }); 
    chassis.moveToPoint(55, 102, 5000, {.forwards = false, .maxSpeed = 70, }); 
     setIntake1(0);

      //distance sensor reset  
    pros::delay(50);
    chassis.turnToHeading(180, 1000);
    pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
    pros::delay(800); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.setPose((72-(distSensorLeft.get_distance())/25.4),107, 180); 
    pros::delay(200);


   //score loaded balls
   chassis.turnToHeading(0, 1000); // turn to face goal
    pros::delay(50); // wait for a moment to stabilize
    //chassis.moveToPoint(53, 100, 1500, {.forwards = false, .maxSpeed = 70});
    chassis.moveToPose(54, 90, 0, 5000, {.forwards = false, .maxSpeed = 70});
    //chassis.turnToHeading(0, 50); // turn to face goal
    pros::delay(500); // wait for a moment to stabilize
    setIntake1( 120) ;
    setIntake2(120);  
    pros::delay(2300); // wait for a moment to shoot


    //second loader
    setIntake1( 0);
    setIntake2(0);  
    toungue.extend();
    setIntake1( 120) ;
    
    
    chassis.moveToPoint(54, 115, 5000, {.maxSpeed = 80, .minSpeed=30, .earlyExitRange=4});
    chassis.moveToPoint(54, 125 , 5000, {.maxSpeed = 50});
    pros::delay(1000);
    chassis.moveToPoint(54, 120, 1000, {.forwards = false});
    chassis.moveToPoint(54, 126, 1000); 
    pros::delay(700);

    //final shoot
  chassis.moveToPoint(55, 89, 4000, {.forwards = false, .maxSpeed = 65});
  pros::delay(800); // wait for a moment to stabilize
      setIntake2(120);
    chassis.moveToPoint(55, 89, 4000, {.forwards = false, .maxSpeed = 10});  
    setIntake1( 120);
    // pros::delay(500);
    // setIntake1( -70) ;
    // setIntake2(-70);
    // pros::delay(50); //jam reverse
    // setIntake1( 120) ;
    // setIntake2(120);
    // pros::delay(200);
    // setIntake1( -70);
    // pros::delay(50); //jam reverse
    // setIntake1( 120);
    pros::delay(2500);
    

    chassis.moveToPoint(55, 100, 5000);

    
    chassis.turnToHeading(90,1000);

    setIntake1( 0);
    setIntake2(0);  
    toungue.retract();
/*
    //travel
    chassis.moveToPoint(40, 100, 5000, {.forwards = false});

          //distance sensor reset  
     
    pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
    pros::delay(1000); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.setPose(45,109-(distSensorLeft.get_distance())/25.4, 90); 
    chassis.moveToPoint(-36, 85, 5000, {.forwards = false, .minSpeed=72, .earlyExitRange=6});
    chassis.moveToPoint(-41, 85, 5000, {.forwards = false, .maxSpeed = 55});


//     //REFLECTION

   pros::delay(500);
    toungue.extend();
    
    pros::delay(100); 
    setIntake1(120);
    chassis.turnToHeading ( 0, 5000);

    //distance sensor reset  
    pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
   pros::delay(1000); //NEED THIS DELAY TO LET POS UPDATE BEFORE TURNING
    chassis.setPose(-(72-(distSensorLeft.get_distance())/25.4),95, 0); 

    //load balls
    chassis.moveToPoint(-53, 109, 1000, {.maxSpeed = 80});
    pros::delay(2700);
    chassis.moveToPoint(-53, 101, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.moveToPoint(-53, 110, 1000, {.maxSpeed = 80});
    pros::delay(300);

    //move to other side
    chassis.moveToPoint(-53, 95, 5000, {.forwards = false}); 
    pros::delay(500);
    toungue.retract();
    chassis.moveToPoint(-36, 67, 5000, {.forwards = false,  .minSpeed=82, .earlyExitRange=6}); 
    chassis.moveToPoint(-40, 28, 5000, {.forwards = false, .minSpeed=62, .earlyExitRange=6}); //change back to 40
   // chassis.moveToPoint(50, 100, 5000, {.forwards = false, .maxSpeed = 70, }); 
    chassis.moveToPoint(-69, -5, 5000, {.forwards = false, .maxSpeed = 70 }); 
    setIntake1(0);

         //distance sensor reset  
      pros::delay(50);
   chassis.turnToHeading(0, 500);
    pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
   pros::delay(1000); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.setPose(-(72-(distSensorLeft.get_distance())/25.4),12, 0); 

   //score loaded balls
   chassis.turnToHeading(180, 500); // turn to face goal
     chassis.moveToPoint(-56, 20, 5000, {.forwards = false, .maxSpeed = 80});
    chassis.turnToHeading(180, 25); // turn to face goal
     setIntake1( 120) ;
    setIntake2(120);
    pros::delay(2500); // wait for a moment to shoot
     
    //second loader
     setIntake1( 0) ;
    setIntake2(0);
    toungue.extend();
    setIntake1( 120);
    
    chassis.moveToPoint(-55, -5, 5000, {.maxSpeed = 80, .minSpeed=30, .earlyExitRange=4});
    chassis.moveToPoint(-55, -16.5, 5000, {.maxSpeed = 50});
    pros::delay(2700);
    chassis.moveToPoint(-55, -12, 1000, {.forwards = false});
    chassis.moveToPoint(-55, -17, 1000); 
    pros::delay(300);

    //final shoot
    chassis.moveToPoint(-55, 20, 2000, {.forwards = false, .maxSpeed = 70});
    pros::delay(1000); // wait for a moment to stabilize
     setIntake1( 120) ;
    setIntake2(120);   
    pros::delay(2000);*/


     pros::delay(5000); 
     

}