
#include <cmath>
#include "globals.hpp"
//#include "pros/rtos.hpp"


void setIntake1(int speed) {
    //pros::lcd::print(5, "Intake1 Speed: %d", speed);
    
    intake1Motor.move(speed);
    //pros::delay(10);
}

void setIntake2(int speed) {
    //pros::lcd::print(8, "Intake2 Speed: %d", speed);

    intake2Motor.move(speed);
    //pros::delay(10);
}


double avgImuHeading(double h1, double h2) {
    // convert degrees → unit circle
    
    double x = cos(h1 * M_PI / 180.0) + cos(h2 * M_PI / 180.0);
    double y = sin(h1 * M_PI / 180.0) + sin(h2 * M_PI / 180.0);

    double ang = atan2(y, x) * 180.0 / M_PI;
    return fmod((ang + 360.0), 360.0);
}

