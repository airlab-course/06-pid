class Driver {
public:
    Driver(int input_a, int input_b) {
        pinMode(input_a, OUTPUT);
        pinMode(input_b, OUTPUT);
        this->pin_a_ = input_a;
        this->pin_b_ = input_b;
    }

    void writeValue(int value) {
        value = constrain(value, -255, 255);
        if (value < 0) {
            analogWrite(pin_a_, abs(value));
            analogWrite(pin_b_, 0);
        } else {
            analogWrite(pin_b_, value);
            analogWrite(pin_a_, 0);
        }
    }

    void stop(){
        this->writeValue(0);
    }

private:
    int pin_a_, pin_b_;
};
