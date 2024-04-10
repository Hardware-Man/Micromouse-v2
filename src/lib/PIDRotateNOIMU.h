#ifndef PIDROTATENOIMU_H
#define PIDROTATENOIMU_H

#include <Arduino.h>

class PIDRotateNOIMU {
    //this class will contain the relevant code for the PIDStraight command. This command will just use two nested PID loops, the inner
    //using the "black magic" straight drive trick using the IMU heading, and the outer scaling it by the encoder values.

    public:
        double kP = 0.1;
        double kI = 0.00;//0.00001;
        double kD = 0.0;

        void rotate_to_angle(double target_position);
};

extern PIDRotateNOIMU* pidrotatenoimu_instance;

#endif