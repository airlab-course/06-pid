class PID {
public:

    PID(double lc, double ic, double dc) {
        linear_coefficient_ = lc;
        integral_coefficient_ = ic;
        diff_coefficient_ = dc;
    }

    double getAction(double new_error) {
        shiftErrors(new_error);

        double linear_action = linear_coefficient_ * errors[0];

        error_integral_ += (errors[1] + errors[0]) / (2 * regulation_period_);
        double integral_action = integral_coefficient_ * error_integral_;

        double error_derivative = (3 * errors[0] - 4 * errors[1] + errors[2]) /
            (2 * regulation_period_);
        double differential_action = diff_coefficient_ * error_derivative;

        double action = linear_action + integral_action + differential_action;

        return action;
    }

private:
    double linear_coefficient_;
    double integral_coefficient_;
    double diff_coefficient_;
    double error_integral_;
    double errors[3] = {0, 0, 0};
    long regulation_period_ = 50;

    void shiftErrors(double new_error) {
        errors[2] = errors[1];
        errors[1] = errors[0];
        errors[0] = new_error;
    }
};