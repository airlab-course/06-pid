#include <stdint.h>
#include "Driver.h"

const int in1 = 8;
const int in2 = 9;
Driver driver{in1, in2};

const int enA = 2;
const int enB = 3;

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
    Serial.print("Ticks : ");
    Serial.println(ticks);
}
