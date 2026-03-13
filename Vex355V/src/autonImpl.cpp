#include "helpers.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/llemu.hpp" // IWYU pragma: keep
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/rtos.hpp"
#include "autonImpl.hpp"

static constexpr double kMmToIn = 1.0 / 25.4;
static constexpr int   kDistSamples = 7;          // odd for median

static double mmToIn(double mm) { return mm * kMmToIn; }

static double medianOf(std::array<double, kDistSamples>& a) {
  std::sort(a.begin(), a.end());
  return a[a.size() / 2];
}

// Robust distance read (median filter + range gate). Returns false if invalid.
static double readDistanceInFiltered(pros::Distance& distSensor) {

   static constexpr int   kDistSamples = 7;          // odd for median
   static constexpr int   kDistSampleDelayMs = 10;    // 7 samples => ~56ms
   //static constexpr double kDistMinIn = 2.0;         // reject too-close / bad reads
   //static constexpr double kDistMaxIn = 70.0;
   std::array<double, kDistSamples> samples{};

  for (int i = 0; i < kDistSamples; ++i) {
    const double mm = (double)(distSensor.get_distance());
    samples[i] = mmToIn(mm);
    pros::delay(kDistSampleDelayMs);
  }

  return medianOf(samples);

  //if (std::isnan(med) || med < kDistMinIn || med > kDistMaxIn) return false;
 
}
void blueRightAuton(){

    
    chassis.setPose(0,15,0);
    //RIGHTBLUE/RIGHT
    setIntake1(120);
    //chassis.moveToPoint(0, 15, 10000, {.minSpeed=62, .earlyExitRange=2});
    chassis.moveToPoint(10, 45, 7000, {.maxSpeed = 60});
    pros::delay(1200);
    chassis.turnToHeading(160, 1000);
    chassis.moveToPoint(35.5, 13, 5000 , {.maxSpeed = 80});
  
    toungue.extend();
  
    chassis.turnToHeading(180,1000);
    pros::delay(750);


    chassis.moveToPoint(35.5, 3.8, 1500, {.maxSpeed = 50});
    // Cool Hack . It never reach target so will hit the delay.
    chassis.moveToPoint(35.5, 0,650, {.maxSpeed = 7});
   
    chassis.moveToPoint(35.5, 34, 3500, {.forwards = false, .maxSpeed = 70});
    pros::delay(800);
    setIntake2(120);
    // Cool Hack . It never reach target so will hit the delay.
    chassis.cancelAllMotions();
    chassis.moveToPoint(35.5, 50, 2000, {.forwards = false, .maxSpeed = 5});
    //pros::delay(1000);
    
    // //throw away extra balls
    // setIntake2(70);

    // chassis.moveToPoint(35.5, 3.8, 1500, {.maxSpeed = 50});
    // chassis.moveToPoint(35.5, 2.8,800, {.maxSpeed = 7});

    pros::delay(3000);


}

void blueLeftAuton(){
   
    chassis.setPose(4.176,14.138,-20.57);
    //RIGHTBLUE/RIGHT
    setIntake1(127);
    wing.extend();

    //chassis.moveToPoint(0, 17, 5000, {});
    chassis.moveToPoint(-4.28, 31.13, 7000, { .minSpeed = 30, .earlyExitRange = 4});
    pros::delay(500);
    toungue.extend();
    chassis.moveToPoint(-9.64, 42.4, 7000, {.maxSpeed = 40});

    //pros::delay(100);
    //chassis.turnToHeading(-150, 1000,{ .minSpeed = 30, .earlyExitRange = 2});
    chassis.moveToPoint(-28.5, 20, 5000, { .minSpeed = 30, .earlyExitRange = 4});
    //chassis.turnToHeading(180,1000);
    toungue.retract();
    chassis.moveToPoint(-28.5, 30, 5000, {.forwards = false, .maxSpeed = 70});
    chassis.moveToPose(-28.5, 34,180, 1500, {.forwards = false});
    pros::delay(100);
    setIntake2(120);
    // Cool Hack . It never reach target so will hit the delay.
    chassis.moveToPoint(-30, 37, 200, {.forwards = false, .maxSpeed = 5});
    int x = chassis.getPose().x;
    //pros::delay(1000);
    chassis.moveToPoint(x, 17, 5000, { .minSpeed = 30, .earlyExitRange = 2});
    chassis.moveToPoint(x+6.5, 25, 5000, {.forwards = false,.minSpeed = 30, .earlyExitRange = 4});
    chassis.turnToHeading(180, 1000, { .minSpeed = 30, .earlyExitRange = 2});
    wing.retract();
    chassis.moveToPoint(x+6.5, 45, 5000, {.forwards = false});

    
    //_______
    
    // pros::delay(300);
    // wing.retract();
    //chassis.moveToPoint(-20, 45, 700, {.forwards = false,.minSpeed = 30, .earlyExitRange = 4});
    
    
    
    
    // chassis.setPose(0,0,180);    
    // chassis.swingToHeading(0, lemlib::DriveSide::LEFT,4000, {.direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE}); 

    
    pros::delay(3000);
    
}
void redRightAuton(){
    blueRightAuton();
    
}
void  redLeftAuton(){
    
    
    chassis.setPose(0,15,0);
    //RIGHTBLUE/RIGHT
    setIntake1(120);
    //chassis.moveToPoint(0, 15, 10000, {.minSpeed=62, .earlyExitRange=2});
    chassis.moveToPoint(-10, 45, 7000, {.maxSpeed = 60});
    pros::delay(1200);
    chassis.turnToHeading(-160, 1000);
    chassis.moveToPoint(-30, 13, 5000 , {.maxSpeed = 80});
  
    toungue.extend();
    wing.extend();

    chassis.turnToHeading(180,1000);
    pros::delay(750);


    chassis.moveToPoint(-31, 3.8, 1500, {.maxSpeed = 50});
    // Cool Hack . It never reach target so will hit the delay.
    chassis.moveToPoint(-31, 0,600, {.maxSpeed = 7});
   
    chassis.moveToPoint(-30, 37, 3500, {.forwards = false, .maxSpeed = 70});
    pros::delay(800);
    setIntake2(120);
    // Cool Hack . It never reach target so will hit the delay.
    chassis.cancelAllMotions();
    chassis.moveToPoint(-30, 50, 2000, {.forwards = false, .maxSpeed = 5});
    //pros::delay(1000);
    
    // //throw away extra balls
    // setIntake2(70);

    // chassis.moveToPoint(-35.5, 3.8, 1500, {.maxSpeed = 50});
    // chassis.moveToPoint(-35.5, 2.8,800, {.maxSpeed = 7});

    pros::delay(3000);


}
void skillsAuton(){

    //move to loader
    chassis.setPose(0, 9, 90);
    chassis.moveToPoint(49.2, 9, 5000,{.maxSpeed = 75}); 
    //chassis.waitUntilDone();

    pros::delay(500);
    toungue.extend();
  
    pros::delay(100); 
    chassis.turnToHeading ( -180, 5000);
    pros::delay(1000); 
    wing.extend();

    //float distance = 72-((distSensorLeft.get_distance())/25.4);
    float distance = 72- readDistanceInFiltered(distSensorLeft);
    pros::delay(100);
    chassis.setPose(distance,10, 180); 
    //load balls
    setIntake1( 120);
    chassis.moveToPoint(54, 0, 1000, { .maxSpeed = 60});
    chassis.moveToPoint(54, -6, 2000, { .maxSpeed = 30});
    chassis.moveToPoint(54, -4, 2000, { .forwards = false});
    chassis.moveToPoint(54, -7, 1500, { .maxSpeed = 20});
    chassis.moveToPoint(54, 5, 1000, { .forwards = false});
    pros::delay(300);
    setIntake1(0); 

   
    //move to other side
    chassis.moveToPoint(63, 28, 3000, {.forwards = false,  .minSpeed=62, .earlyExitRange=2}); 
    toungue.retract();
    chassis.moveToPoint(63, 85, 4000, {.forwards = false, .minSpeed=62, .earlyExitRange=2}); //change back to 40
   // chassis.moveToPoint(50, 100, 5000, {.forwards = false, .maxSpeed = 70, }); 
    chassis.moveToPoint(50, 100, 3000, {.forwards = false, .maxSpeed = 70}); 

      //distance sensor reset  
    chassis.turnToHeading(0, 1000);
    //pros::lcd::print(7, "X: %f", 72-((distSensorRight.get_distance())/25.4));
    //pros::delay(1000); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    chassis.waitUntilDone();
//    chassis.cancelMotion();   // if exists
    pros::delay(20);
    //chassis.setPose((72-(distSensorRight.get_distance())/25.4),107, 0); 
    chassis.setPose(72-readDistanceInFiltered(distSensorRight),107, 0); 
    
    pros::delay(20);


   //score loaded balls
   //chassis.turnToHeading(0, 1000); // turn to face goal
    //pros::delay(50); // wait for a moment to stabilize
    chassis.moveToPose(53, 89, 0, 2300, {.forwards = false, .maxSpeed = 70});
    //chassis.turnToHeading(0, 50); // turn to face goal
    //pros::delay(1500); // wait for a moment to stabilize
    pros::delay(2000); // wait for a moment to load
    setIntake1( 120) ;
    setIntake2(120);
    setIntake2(-120); //loook down
    pros::delay(50); //jam reverse
    setIntake2(120);
    pros::delay(1500); // wait for a moment to load
    //pros::delay(200); // wait for a moment to shoot


    //second operation to load from stack
    toungue.extend();
    
    chassis.moveToPoint(53, 115, 4000, {.maxSpeed = 80, .minSpeed=30, .earlyExitRange=4});
    setIntake2(0);  
    
    chassis.moveToPoint(53, 124 , 2000, {.maxSpeed = 50});
     chassis.moveToPoint(53, 126, 2500, {.maxSpeed = 10}); 
    // chassis.moveToPoint(53, 120, 1000, {.forwards = false});
    // chassis.moveToPoint(53, 124.5, 1000); 
    // pros::delay(2000);

    //final shoot
  chassis.moveToPoint(54, 95,  2000, {.forwards = false, .minSpeed=30, .earlyExitRange=2});
  chassis.moveToPose(54, 89,0,  1000, {.forwards = false, .maxSpeed = 65});
//  pros::delay(800); // wait for a moment to stabilize
    chassis.waitUntilDone();
    setIntake2(120);
    //HACK intake 2 starts too late placeholder below
    chassis.moveToPoint(54, 89, 4000, {.forwards = false, .maxSpeed = 10});  
    setIntake1( 120);

    pros::delay(2300);
    
    chassis.moveToPoint(54, 100, 5000);
    chassis.turnToHeading(90,2000); //CHANGE BACK

    setIntake1( 0);
    setIntake2(0);  
    toungue.retract();

    //Travel to reflection point .Second phasse of skills auton.
    chassis.moveToPose(40, 100,90, 5000, {.forwards = false});
    chassis.waitUntilDone(); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    pros::delay(20);
 //TAPED___________________________________________   UNNCOMMENT ABOVE TO TEST AUTON FULLY
   
    chassis.setPose(45,109-readDistanceInFiltered(distSensorLeft), 90); 
    // //new value for recheck
    // chassis.moveToPose(47, 80.7,90, 5000, {.forwards = false});
    // chassis.waitUntilDone(); //NEED THIS DELAY TO LET ROBOT GET TO POINT BEFORE SETTING POSE
    // chassis.setPose(47,109-(distSensorLeft.get_distance())/25.4, 90); 

    int y = 92;
    chassis.moveToPoint(-34, 85, 4000, {.forwards = false, .minSpeed=72, .earlyExitRange=6});
    chassis.moveToPoint(-44, y, 4000, {.forwards = false, .maxSpeed = 50});


  //REFLECTION : right in front of 3rd match loader.

   pros::delay(500);
    toungue.extend();
    
    pros::delay(100); 
    setIntake1(120);
    chassis.turnToHeading ( 0, 700);
    
    //distance sensor reset  
    pros::lcd::print(7, "X: %f", 72-((distSensorLeft.get_distance())/25.4));
    pros::delay(700);
    //chassis.waitUntilDone();
    //chassis.setPose(-(72-(distSensorLeft.get_distance())/25.4),95, 0); 
    chassis.setPose(-(72-readDistanceInFiltered(distSensorLeft)),y, 0); 

    //load balls
    chassis.moveToPoint(-52.5, 112, 1000, {.maxSpeed = 50});
    pros::delay(1500);
    //chassis.moveToPoint(-52.5, 106, 1000, {.forwards = false, .maxSpeed = 80});
    chassis.moveToPoint(-52.5, 115, 2800, {.maxSpeed = 50});
    chassis.moveToPoint(-52.5, 108, 2000, { .forwards = false});
  //REVERSE 
    // chassis.moveToPoint(-52.5, 117, 1800, {.maxSpeed = 50});
    // pros::delay(2000);

    wing.extend(); //not needed for full


    //move to other 4th quarter.
    chassis.moveToPoint(-66, 82, 5000, {.forwards = false,  .minSpeed=62, .earlyExitRange=4}); //76
       
    setIntake1(0); 
    
    //chassis.moveToPoint(-66, 80, 5000, {.forwards = false}); //76
    pros::delay(200);
    toungue.retract();
    chassis.moveToPoint(-71, 30, 5000, {.forwards = false,  .minSpeed=32, .earlyExitRange=2}); //change back to 40
    chassis.moveToPoint(-71.5, 18, 5000, {.forwards = false, .maxSpeed = 50}); //change back to 40
    chassis.moveToPoint(-56, 4, 5000, {.forwards = false, .maxSpeed = 70, }); 
     setIntake1(0);

   //distance sensor reset  
   pros::delay(50);
   chassis.turnToHeading(180, 1000);

   pros::lcd::print(7, "X: %f", 72-((distSensorRight.get_distance())/25.4));
    chassis.waitUntilDone();
    pros::delay(20);

   //chassis.setPose(-(72-(distSensorRight.get_distance())/25.4),4, 180); 
   chassis.setPose(-(72- readDistanceInFiltered(distSensorRight)),4, 180); 
    
    pros::delay(20);

   //score loaded balls
   //chassis.turnToHeading(0, 1000); // turn to face goal
    //pros::delay(50); // wait for a moment to stabilize
    setIntake1( 120) ;
    chassis.moveToPose(-50.5, 22, 180, 2500, {.forwards = false, .maxSpeed = 70});
    //chassis.turnToHeading(0, 50); // turn to face goal
  pros::delay(1000);    
    setIntake2(120);
    // setIntake2(-120); //loook down
    // pros::delay(50); //jam reverse
    setIntake2(120);
    pros::delay(1800); // wait for a moment to shoot

    
    //second loader
    toungue.extend();
    setIntake1( 120);
    chassis.moveToPoint(-53, 2, 5000, {.maxSpeed = 80, .minSpeed=30, .earlyExitRange=4});
    setIntake2(0);


    chassis.moveToPoint(-54.5, -13, 3000, {.maxSpeed = 50});
    pros::delay(1000);
    chassis.moveToPoint(-54.5, -10, 3000, { .forwards = false});
    chassis.moveToPoint(-54.5, -17, 4000, { .maxSpeed = 8});
    //TRIED EVERY SINGLE DELAY HERE 
    chassis.waitUntilDone();
    pros::delay(1000);
    chassis.moveToPoint(-52, 7, 5000, { .forwards = false});

    //final shoot
    chassis.moveToPoint(-50, 22, 2000, {.forwards = false, .maxSpeed = 70});
    pros::delay(700);
    setIntake2(120);   
    //pros::delay(1000); // wait for a moment to stabilize
//    setIntake1( 120) ;
    pros::delay(1500);
    toungue.retract();
    
    //PARKING Task
   // chassis.setPose(-50, 22, 180);
    
     chassis.moveToPoint(-52, 7, 5000);
    chassis.waitUntilDone();
     chassis.swingToHeading(90,lemlib::DriveSide::LEFT, 1000, {.minSpeed = 127, .earlyExitRange = 20});


    chassis.moveToPose( -4, -10,  180,  3000 ,{.minSpeed = 80, .earlyExitRange = 20});
    chassis.moveToPoint(-4, -25, 5000, {.minSpeed = 80, .earlyExitRange = 5});

 
     pros::delay(5000); 
    
}
    

void fixParking(){
    chassis.setPose(chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta); // just for park test.
    chassis.moveToPoint(-50, 16, 500);
  
    chassis.moveToPose( -34, 11,  90,  3000,{.forwards = true, .maxSpeed = 90});
    chassis.moveToPose( 2, 18,  -180,  3000,{.forwards = true, .maxSpeed = 90});
    chassis.waitUntilDone();

    //MAX SPEED TO PARK
    chassis.moveToPoint(0, -16, 10000,{.maxSpeed = 120});
    setIntake1( 120) ;
    setIntake2(120);  
    pros::delay(5000); 
}
