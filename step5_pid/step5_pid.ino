#include <stdint.h>
#include "Regulator.h"
#include "Driver.h"

const int in1 = 8;
const int in2 = 9;
Driver driver{in1, in2};

const int enA = 2;
const int enB = 3;

int ticks;
long previous_time;
long previous_command_time;

long regulation_period = 50;
long command = 0;
long command_period = 1000;
int command_pointer = 0;
Regulator regulator = Regulator();

double song[34][2] = {
    {26, 0.5},
    {45, 0.75},
    {58, 0.25},
    {53, 0.5},
    {45, 1.0},
    {80, 0.5},
    {69, 1.5},
    {53, 1.5},
    {45, 0.75},
    {58, 0.25},
    {53, 0.5},
    {40, 1.0},
    {49, 0.5},
    {26, 1.5},
    {26, 0.875},
    {-27, 0.125},
    {26, 0.5},
    {45, 0.75},
    {58, 0.25},
    {53, 0.5},
    {45, 1.0},
    {80, 0.5},
    {101, 1.0},
    {94, 0.5},
    {87, 1.0},
    {69, 0.5},
    {87, 0.75},
    {80, 0.25},
    {74, 0.5},
    {26, 1.0},
    {58, 0.5},
    {45, 1.5},
    {45, 1.0},
    {-27, 1.0},
};

void setup() {
    Serial.begin(115200);
    setupPinMode();
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
        // regulator.print_debug_output(Serial, ticks);
        double constrained_action = regulator.regulate(ticks);
        ticks = 0;
        driver.writeValue(constrained_action);
        previous_time = millis();
    }

    if (millis() - previous_command_time > command_period) {
        driver.stop();
        delay(50);
        command = song[command_pointer][0] * 0.4;
        command_period = song[command_pointer][1] * 1000;
        regulator.setTargetSpeed(command);
        previous_command_time = millis();
        command_pointer++;
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
