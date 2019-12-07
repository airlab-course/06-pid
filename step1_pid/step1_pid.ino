#include "Driver.h"

int in1 = 8;
int in2 = 9;
Driver driver{in1, in2};

void setup() {
    Serial.begin(115200);
    driver.stop();
}

void loop() {
    if (Serial.available()) {
        int value = Serial.parseInt();
        driver.writeValue(value);
    }
}
