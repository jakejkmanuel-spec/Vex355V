#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/llemu.hpp"
#include "helpers.hpp"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"


pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::MotorGroup left_mg({-2, -3, -12},pros::MotorGearset::blue);   
pros::MotorGroup right_mg({8, 9, 10}, pros::MotorGearset::blue);  


// drivetrain settings
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              11.45, //track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm 
                              2 // horizontal drift is 2 (for now)
);


pros::Imu imu(18); //main imu sensor  MAKE SURE TO CHECK PORTS OF BOTH IMUS
//avg with other imu on port 18 when calling setpose

// horizontal tracking wheel encoder
// pros::Rotation horizontal_encoder(4);

// vertical tracking wheel encoder
pros::Rotation vertical_encoder(16);
// horizontal tracking wheel

 // lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, 2.625); 

// vertical tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -0.375); 
// odometry settings

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(12, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              9, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(3.4, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              17, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// // input curve for steer input during driver control
// lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
//                                   10, // minimum output where drivetrain will move out of 127
//                                   1.019 // expo curve gain
// );

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve

);


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
	
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */


void initialize() {
    pros::lcd::initialize();

    imu.reset();
    //imu2.reset();
    
    while (imu.is_calibrating()) {
        pros::lcd::set_text(0, "Calibrating IMU...");
        pros::delay(20);
    }
    //pros::Task intakeTask1(intake1Task);
    //pros::Task intakeTask2(intake2Task);
    

    chassis.calibrate();
    pros::lcd::set_text(0, "IMU Ready!");

    pros::Task screen_task([]() {
        while (true) {
            pros::lcd::print(1, "X: %f", chassis.getPose().x);
            pros::lcd::print(2, "Y: %f", chassis.getPose().y);
            pros::lcd::print(3, "Theta: %f", chassis.getPose().theta);

            pros::lcd::print(4, "IMU Heading: %f", imu.get_heading());
            //pros::lcd::print(5, "AVG IMU Heading: %f", avgImuHeading(imu.get_heading(), imu2.get_heading()));
            pros::lcd::print(6, "IMU Orientation: %f", imu.get_physical_orientation());

            pros::lcd::print(7, "Rotation Sensor: %i", vertical_encoder.get_position());
            pros::delay(100);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

int auton_selection = 0; // Global variable to store selected autonomous routine

// List of autonomous routines
const char* auton_names[] = {
    "Blue Right Side",
    "Blue Left Side",
    "Red Right Side",
    "Red Left Side",
    "Skills",
    "None"
};



void competition_initialize() {
    pros::lcd::initialize();


    // pros::lcd::print(2, "Selected: %s", auton_names[auton_selection]);
    
    //for debugging
    // while (true){
    //     pros::lcd::print(3, "Potentiometer: %d", aSelector.get_value());
    //     pros::delay(20);
    // }

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
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


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol() {
    competition_initialize();
    //autonomous();
    //pros::delay(500); // delay after autonomous end
    
    
    while (true) {
        pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
                         (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
                         (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
        
        if(master.get_digital_new_press(DIGITAL_A) && master.get_digital_new_press(DIGITAL_B)){
            autonomous();
        }
         //Hack to fix PROS key stroke issues. it gives button press even when it not pressed.
        int r1State = master.get_digital(DIGITAL_R1) ;
        setIntake1(r1State * 127);
        if(r1State == 0){
        setIntake1(master.get_digital(DIGITAL_R2) * -127);
        }

        int l1State =  master.get_digital(DIGITAL_L1);
	    setIntake2(l1State* 127);
        if(l1State == 0){
            setIntake2(master.get_digital(DIGITAL_L2) * -127);
        }


		if (master.get_digital_new_press(DIGITAL_Y)) {
		toungue.extend();
		}
		if (master.get_digital_new_press(DIGITAL_RIGHT)) {
		toungue.retract();
		}
		
		if (master.get_digital_new_press(DIGITAL_UP)) {
		//intake1Speed = 120;
        }
		

        // **Tank drive control**
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(leftY, rightY);

        pros::delay(25);  // Prevents CPU overuse
    }
}
