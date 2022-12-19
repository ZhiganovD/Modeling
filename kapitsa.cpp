#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>
#include "json.hpp"
using json = nlohmann::json;

template <typename MP>
class MyState
{
public:
    std::array<MP,2> state;

    MyState(std::array<MP,2> state): state(state) {}

    MP operator[](int i) const { return state[i]; }

    MyState copy(const std::array<MP,2>& s)
    {
        std::copy_n(s.begin(), s.size(), state.begin());
    }


    MyState func_force(double nu, double t, double l, double A, double g) const
    {
        return MyState {std::array<MP,2> {state[1], (-1) * (A * pow(nu, 2) * cos(nu * t) + g) * sin(state[0]) * (1 / l)}};
    }

    MyState operator+( MyState y) 
    {
        return MyState {std::array<MP,2> {state[0] + y[0], state[1] + y[1]}};
    }

    MyState operator*(double const a) 
    {
        return MyState {std::array<MP,2> {state[0] * a, state[1] * a}};
    }

    MyState operator/(double const a) 
    {
        return MyState {std::array<MP,2> {state[0] / a, state[1] / a}};
    }

    void operator=(MyState y) 
    {
        state[0] = y[0];
        state[1] = y[1];
    }

    void print(MyState y)
    {
        std::cout << y[0] << " " << y[1] << std::endl;
    }
};


template <class A>
class Euler
{
public:
    static A make_step_RK4(A& state, float dt, std::ofstream &myfile_RK4, double omega)
    {
        myfile_RK4 << state[0] << ' ' << state[1] << '\n';
        auto k1 = state.func(omega);
        auto y0 = state + k1 * (dt / 2);
        auto k2 = y0.func(omega);
        auto y1 = state + k2 * (dt / 2);
        auto k3 = y1.func(omega);
        auto y2 = state + k3 * dt;
        auto k4 = y2.func(omega);
        state = state + (k1 + k2 * 2 + k3 * 2 + k4) * (dt / 6);
        return state;
    }

    static A make_step_RK4_force(A& state, float dt, std::ofstream &myfile_force, double nu, double t, double g, double a, double l)
    {
        myfile_force << state[0] << ' ' << state[1] << '\n';
        auto k1 = state.func_force(nu, t, l, a, g);
        auto y0 = state + k1 * (dt / 2);
        auto k2 = y0.func_force(nu, t + dt / 2, l, a, g);
        auto y1 = state + k2 * (dt / 2);
        auto k3 = y1.func_force(nu, t + dt / 2, l, a, g);
        auto y2 = state + k3 * dt;
        auto k4 = y2.func_force(nu, t + dt, l, a, g);
        state = state + (k1 + k2 * 2 + k3 * 2 + k4) * (dt / 6);
        return state;
    }
};

int main()
{
    std::chrono::steady_clock sc;
    std::ifstream argv("kapitsa_input.json");
    json data = json::parse(argv);
    std::ofstream myfile_k;

    myfile_k.open ("data0_2.txt");

    myfile_k << data["n"] << ' ' << data["n"] << '\n';

    MyState<double> A{std::array<double,2>{data["x0"], data["y0"]}};


    auto k = data["xk"];
    const double & my_value = data["xk"];
    double h = (static_cast<double>(data["xk"]) - static_cast<double>(data["x0"])) / static_cast<double>(data["n"]);
    double t = 0;
    /*for (int i = 0; i < data["n"]; ++i)
    {
        A = Euler<MyState<double>>::make_step_eul(A, 0.01, myfile_e, data["omega"]);
        B = Euler<MyState<double>>::make_step_hoin(B, 0.01, myfile_h, data["omega"]);
        C = Euler<MyState<double>>::make_step_RK4(C, 0.01, myfile_RK4, data["omega"], t);
        t += 0.01;
    }*/

   
    auto start_k = sc.now();
    for (int i = 0; i < data["n"]; ++i)
    {
        A = Euler<MyState<double>>::make_step_RK4_force(A, 0.01, myfile_k, data["nu"], t, data["g"], data["ampl"], data["l"]);
        t += 0.01;
    }
    auto end_k = sc.now();
    /*MyState<double> X{std::array<double,2>{1.00, 2.00}};
    MyState<double> Y{std::array<double,2>{3.00, 4.00}};
    X.print(X + Y);
    X.print(X / 2);
    X.print(X * 2);
    X = Y;
    X.print(X);*/

    auto time_span_k = static_cast<std::chrono::duration<double>>(end_k - start_k);

    std::cout << time_span_k.count() << std::endl;

    myfile_k.close();
    return 0;
}