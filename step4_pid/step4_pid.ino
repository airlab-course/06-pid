#include <stdint.h>
#include "Regulator.h"
#include "Driver.h"

const int in1 = 8;
const int in2 = 9;
Driver driver{in1, in2};

const int enA = 2;
const int enB = 3;

long previous_time;
long regulation_period = 50;

Regulator regulator = Regulator();
int ticks = 0;

void setup() {
    Serial.begin(115200);
    setupPinMode();
    driver.stop();
    attachInterrupt(digitalPinToInterrupt(enA), count_ticks, RISING);
}

void setupPinMode() {
    pinMode(enA, INPUT);
    pinMode(enB, INPUT);
}

void count_ticks() {
    int current_b = digitalRead(enB);
    if (current_b == LOW) {
        ticks--;
    } else {
        ticks++;
    }
}

void loop() {

    if (millis() - previous_time > regulation_period) {
        regulator.printDebugOutput(Serial, ticks);
        double constrained_action = regulator.regulate(ticks);
        ticks = 0;
        driver.writeValue(constrained_action);
        previous_time = millis();
    }

    if (Serial.available()) {
        int target_mm = 0;
        char command = Serial.read();
        switch (command) {
            case 'm':target_mm = Serial.parseInt();
                regulator.setTargetSpeed(target_mm);
                break;
            case 't':Serial.print("Target: ");
                Serial.print(regulator.getTargetSpeed());
                Serial.println();
                break;
        }
    }
}
