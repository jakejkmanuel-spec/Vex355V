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
    chassis.moveToPoint(9, 40, 7000, {.maxSpeed = 60});
    pros::delay(1200);
    chassis.turnToHeading(170, 1000);
    chassis.moveToPoint(33.5, 13, 5000);
    chassis.turnToHeading(180,1000);
    pros::delay(750);

    toungue.extend();

    chassis.moveToPoint(34, 3.8, 1500, {.maxSpeed = 50});
    chassis.moveToPoint(34, 2.8,800, {.maxSpeed = 7});
   
    chassis.moveToPoint(34, 33.7, 3500, {.forwards = false, .maxSpeed = 70});
    pros::delay(800);
    setIntake2(120);
    pros::delay(1000);
    
    //throw away extra balls
    setIntake2(70);

    chassis.moveToPoint(34, 3.8, 1500, {.maxSpeed = 50});
    chassis.moveToPoint(34, 2.8,800, {.maxSpeed = 7});

    pros::delay(3000);


}

void blueLeftAuton(){
   
    chassis.setPose(0,0,0);
    //RIGHTBLUE/RIGHT
    setIntake1(120);
    chassis.moveToPoint(0, 17, 5000);
    chassis.moveToPoint(-9, 40, 7000, {.maxSpeed = 60});
    pros::delay(1200);
    chassis.turnToHeading(-170, 1000);
    chassis.moveToPoint(-33.5, 13, 5000);
    chassis.turnToHeading(-180,1000);
    pros::delay(750);

    toungue.extend();

    chassis.moveToPoint(-34, 3.8, 1500, {.maxSpeed = 50});
    chassis.moveToPoint(-34, 2.8,800, {.maxSpeed = 7});
   
    chassis.moveToPoint(-34, 33.7, 3500, {.forwards = false, .maxSpeed = 70});
    pros::delay(800);
    setIntake2(120);
    pros::delay(1000);
    
    //throw away extra balls
      setIntake2(70);
    chassis.moveToPoint(-34, 3.8, 1500, {.maxSpeed = 50});
    chassis.moveToPoint(-34, 2.8,800, {.maxSpeed = 7});

    pros::delay(3000);
    
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

    wing.extend();

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
    chassis.moveToPoint(54, -7, 3000, { .maxSpeed = 20});
    chassis.moveToPoint(54, -1, 5000, { .forwards = false});
    chassis.moveToPoint(54, -6, 5000, { .maxSpeed = 40});
    pros::delay(200);
    chassis.moveToPoint(54, 5, 5000, { .forwards = false});
    setIntake1(0); 

   
    //move to other side
    chassis.moveToPoint(65, 30, 5000, {.forwards = false,  .minSpeed=62, .earlyExitRange=4}); 
    toungue.retract();
    chassis.moveToPoint(63, 85, 5000, {.forwards = false, .minSpeed=62, .earlyExitRange=2}); //change back to 40
   // chassis.moveToPoint(50, 100, 5000, {.forwards = false, .maxSpeed = 70, }); 
    chassis.moveToPoint(52, 100, 5000, {.forwards = false, .maxSpeed = 70, }); 
     setIntake1(0);

      //distance sensor reset  
    pros::delay(50);
    chassis.turnToHeading(0, 1000);
    pros::lcd::print(7, "X: %f", 72-((distSensorRight.get_distance())/25.4));
    pros::delay(1000); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.setPose((72-(distSensorRight.get_distance())/25.4),107, 0); 
    pros::delay(200);


   //score loaded balls
   //chassis.turnToHeading(0, 1000); // turn to face goal
    //pros::delay(50); // wait for a moment to stabilize
    chassis.moveToPose(54, 90, 0, 3000, {.forwards = false, .maxSpeed = 70});
    //chassis.turnToHeading(0, 50); // turn to face goal
    pros::delay(600); // wait for a moment to stabilize
    setIntake1( 120) ;
    setIntake2(120);
    setIntake2(-120); //loook down
    pros::delay(50); //jam reverse
    setIntake2(120);
    //pros::delay(200); // wait for a moment to shoot


    //second loader
    toungue.extend();
    
    
    chassis.moveToPoint(54, 115, 5000, {.maxSpeed = 80, .minSpeed=30, .earlyExitRange=4});
    
    setIntake2(0);  
    
    chassis.moveToPoint(54, 125 , 2000, {.maxSpeed = 50});
    pros::delay(1000);
    chassis.moveToPoint(54, 120, 1000, {.forwards = false});
    chassis.moveToPoint(54, 126, 1000); 
    pros::delay(2000);

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
    pros::delay(800);
    

    chassis.moveToPoint(55, 100, 5000);

    
    chassis.turnToHeading(90,1000);

    setIntake1( 0);
    setIntake2(0);  
    toungue.retract();

    //travel
    chassis.moveToPoint(40, 100, 5000, {.forwards = false});

//TAPED____________________________________________________________    UNNCOMMENT ABOVE TO TEST AUTON FULLY
          //distance sensor reset  
     
    pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
    pros::delay(1000); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.setPose(45,109-(distSensorLeft.get_distance())/25.4, 90); 
    chassis.moveToPoint(-34, 85, 5000, {.forwards = false, .minSpeed=72, .earlyExitRange=6});
    chassis.moveToPoint(-41, 85, 5000, {.forwards = false, .maxSpeed = 50});


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
    chassis.moveToPoint(-52.5, 115, 1000, {.maxSpeed = 50});
    pros::delay(2300);
    //chassis.moveToPoint(-52.5, 106, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.moveToPoint(-52.5, 117, 2800, {.maxSpeed = 9});
    chassis.moveToPoint(-52.5, 105, 5000, { .forwards = false});
    wing.extend(); //not needed for full

    //move to other side
    chassis.moveToPoint(-66, 82, 5000, {.forwards = false,  .minSpeed=62, .earlyExitRange=4}); //76
       
    setIntake1(0); 
    
    //chassis.moveToPoint(-66, 80, 5000, {.forwards = false}); //76

    toungue.retract();
    chassis.moveToPoint(-71, 30, 5000, {.forwards = false,  .minSpeed=32, .earlyExitRange=4}); //change back to 40
    chassis.moveToPoint(-70, 18, 5000, {.forwards = false, .maxSpeed = 50}); //change back to 40
    chassis.moveToPoint(-56, 4, 5000, {.forwards = false, .maxSpeed = 70, }); 
     setIntake1(0);


//          //distance sensor reset  
      pros::delay(50);
   chassis.turnToHeading(180, 1000);

   pros::lcd::print(7, "X: %f", 72-((distSensorRight.get_distance())/25.4));
   pros::delay(1000); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.setPose(-(72-(distSensorRight.get_distance())/25.4),4, 180); 

   //score loaded balls
   //chassis.turnToHeading(0, 1000); // turn to face goal
    //pros::delay(50); // wait for a moment to stabilize
    chassis.moveToPose(-52, 20, 180, 2500, {.forwards = false, .maxSpeed = 70});
    //chassis.turnToHeading(0, 50); // turn to face goal
    pros::delay(1000); // wait for a moment to stabilize
    setIntake1( 120) ;
    setIntake2(120);
    // setIntake2(-120); //loook down
    // pros::delay(50); //jam reverse
    setIntake2(120);
    pros::delay(200); // wait for a moment to shoot

    
    //second loader
    toungue.extend();
    setIntake1( 120);
    
    chassis.moveToPoint(-53, 2, 5000, {.maxSpeed = 80, .minSpeed=30, .earlyExitRange=4});
    
    setIntake2(0);


    chassis.moveToPoint(-53, -11, 5000, {.maxSpeed = 50});
    pros::delay(1000);
    chassis.moveToPoint(-53, -3, 5000, { .forwards = false});
    chassis.moveToPoint(-53, -12, 5000, { .maxSpeed = 40});
    pros::delay(1500);
    chassis.moveToPoint(-53, 5, 5000, { .forwards = false});
    setIntake1(0); 



    //final shoot
    chassis.moveToPoint(-52, 20, 2000, {.forwards = false, .maxSpeed = 70});
    pros::delay(1000); // wait for a moment to stabilize
     setIntake1( 120) ;
    setIntake2(120);   
    pros::delay(1200);
    toungue.retract();
    
    //PARK
    chassis.moveToPoint(-52, 4, 5000);
    setIntake2(0);
    chassis.moveToPoint(-38,-20, 2000);    
    chassis.turnToHeading(95,1500);
    chassis.moveToPoint(-45,-20, 2000, {.forwards = false});    

    chassis.moveToPoint(-10, -23, 5000);



     pros::delay(5000); 
     

}