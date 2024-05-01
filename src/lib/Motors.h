#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Encoder.h>



#ifndef V3

#define pin_PWMA 11
#define pin_PWMB 12
#define pin_AIN1 0
#define pin_AIN2 1
extern Encoder ENCB;
#define pin_BIN1 13
#define pin_BIN2 15
//#define pin_STBY 11
extern Encoder ENCA;

#endif
#ifdef V3

#define pin_PWMA 4
#define pin_PWMB 9  /* this was originally 9      became 11*/
#define pin_AIN1 6
#define pin_AIN2 5
extern Encoder ENCA;
#define pin_BIN1 7
#define pin_BIN2 8
extern Encoder ENCB;
#define pin_STBY 14

#endif


class Motors {

    public:

        void enableMotors();
        void disableMotors();
        void setLeftMotorSpeed(int speed);
        void setRightMotorSpeed(int speed);
        void setMotorsSpeed(int speed);
        void setLeftMotorDirection(bool forward);
        void setRightMotorDirection(bool forward);
        void setMotorsDirection(bool forward);
        void setClockWise();
        void setCClockWise();
        void setStraight();
        int getlefttick();
        void setlefttick(int set);
        int getrighttick();
        void setrighttick(int set);
        void setTick(int set);

};

extern Motors* motors_instance;

#endif