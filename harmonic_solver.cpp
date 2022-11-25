#include <iostream>
#include <vector>

double const pi = 3.14;
// Parametr of differential equation
double const omega2 = 1.0;
bool const DEBUG = 0;

struct State {
    double x;
    double v;

    State(): x(0.0), v(0.0) {}
    State(double x_, double v_) : x(x_), v(v_) {}

    void set_state(double x_, double v_) {
        x = x_;
        v = v_;
    }

    State mult() {
        State t(v, -omega2 * x);
        return t;
    }

    void print() {
        std::cout << "x: " << x << " | " << "v: " << v << "\n";
    }

    void write() {
        std::cout << x << "\t" << v << "\n";
    }

    State& operator=(const State& lhs) {
        if (this == &lhs) {
            return *this;
        }

        x = lhs.x;
        v = lhs.v;

        return *this;
    }

    friend State operator+(const State& lhs, const State& rhs);
    friend State operator*(const State& lhs, double val);
    friend State operator/(const State& lhs, double val);
};

State operator+(const State& lhs, const State& rhs) {
    State t(lhs.x + rhs.x, lhs.v + rhs.v);

    return t;
}

State operator*(const State& lhs, double val) {
    State t(lhs.x * val, lhs.v * val);

    return t;
}

State operator/(const State& lhs, double val) {
    State t(lhs.x / val, lhs.v / val);

    return t;
}

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Wrong amount of parametrs!!!" << std::endl;
        return -1;
    }

    // Parametr of solver
    double t_left = std::atof(argv[1]);
    double t_right = std::atof(argv[2]) * 2 * pi;
    size_t N = std::atoi(argv[3]); // Number of points
    double dt = (t_right - t_left) / (N - 1);
    char solver_type = *argv[4];

    std::cout << "t_left: " << t_left << "\n";
    std::cout << "t_right: " << t_right << "\n";
    std::cout << "N: " << N << "\n";

    // Initial condition and grid
    State init_state(0.0, 1.0);
    std::vector<State> grid;
    grid.push_back(init_state);

    if (DEBUG) {
        std::cout << "1\t";
        init_state.print();
    } else {
        init_state.write();
    }

    State curr_state;
    for (size_t i = 1; i < N; i++) {
        if (solver_type == 'E') {
            // Euler's method
            curr_state = grid[i-1] + grid[i-1].mult() * dt;
        } else if (solver_type == 'H') {
            // Heun's method
        curr_state = grid.back() + (grid.back().mult() + (grid.back() + grid.back().mult() * dt).mult()) * dt / 2.0;
        }

        grid.push_back(curr_state);

        if (DEBUG) {
            std::cout << i+1 << "\t";
            curr_state.print();
        } else {
            curr_state.write();
        }
    }

    return 0;
}
