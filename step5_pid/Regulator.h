#include "PID.h"
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
class Regulator {
public:

    double regulate(int &ticks) {
        int error = target_speed_ - ticks;
        double unconstrained_action = pid_.getAction(error);
        double diff = unconstrained_action - prev_action_;
        diff = constrain(diff,
                         -45,
                         45);  // Prevent motor speed from changing too quickly
        double constrained_action = constrain(prev_action_ + diff, -255, 255);
        prev_action_ = constrained_action;
        return constrained_action;
    }

    void setTargetSpeed(int target) {
        target_speed_ = target;
    }

    int getTargetSpeed() {
        return target_speed_;
    }

    void printDebugOutput(HardwareSerial &serial, int &ticks) {
        serial.print("Target ticks: ");
        serial.println(target_speed_);
        serial.print("Current ticks: ");
        serial.println(ticks);
        serial.print("Action: ");
        serial.println(prev_action_);
        serial.println();
    }

private:
    PID pid_ = PID(0, 0, 0);

    double prev_action_ = 0;
    int target_speed_ = 0;
};
