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

    MyState func(double omega) const
    {
        return MyState {std::array<MP,2> {state[1], (-1) * pow(omega, 2) * sin(state[0])}};
    }

    MyState func_force(double omega, double t, double gamma, double A) const
    {
        return MyState {std::array<MP,2> {state[1], (-1) * pow(omega, 2) * sin(state[0]) - 2 * gamma * state[1] - A * cos (omega * t)}};
    }

    MyState func_damp(double omega, double gamma) const
    {
        return MyState {std::array<MP,2> {state[1], (-1) * pow(omega, 2) * sin(state[0]) - 2 * gamma * state[1]}};
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

double Quality(double gamma, double omega)
{
    return M_PI / (gamma * 2 * M_PI / omega);
}

template <class A>
class Euler
{
public:
    static A make_step_eul(A& state,  float dt, std::ofstream &myfile_e, double omega)
    {
        myfile_e << state[0] << ' ' << state[1] << '\n'; 
        auto tmp = state + state.func(omega)*dt;
        state =  tmp;
        return state;
    }

    static A make_step_hoin(A& state, float dt, std::ofstream &myfile_h, double omega)
    {
        myfile_h << state[0] << ' ' << state[1] << '\n';
        auto tmp = state + state.func(omega) * dt;
        state = state + (state.func(omega) + tmp.func(omega)) * dt / 2.0;
        return state;
    }

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

    static A make_step_hoin_damped(A& state, float dt, std::ofstream &myfile_damped, double omega, double gamma)
    {
        myfile_damped << state[0] << ' ' << state[1] << '\n';
        auto tmp = state + state.func_damp(omega, gamma) * dt;
        state = state + (state.func_damp(omega, gamma) + tmp.func_damp(omega, gamma)) * dt / 2.0;
        return state;
    }

    static A make_step_RK4_force(A& state, float dt, std::ofstream &myfile_force, double omega, double t, double gamma, double Ampl)
    {
        myfile_force << state[0] << ' ' << state[1] << '\n';
        auto k1 = state.func_force(omega, t, gamma, Ampl);
        auto y0 = state + k1 * (dt / 2);
        auto k2 = y0.func_force(omega, t + dt / 2, gamma, Ampl);
        auto y1 = state + k2 * (dt / 2);
        auto k3 = y1.func_force(omega, t + dt / 2, gamma, Ampl);
        auto y2 = state + k3 * dt;
        auto k4 = y2.func_force(omega, t + dt, gamma, Ampl);
        state = state + (k1 + k2 * 2 + k3 * 2 + k4) * (dt / 6);
        return state;
    }
};

int main()
{
    std::chrono::steady_clock sc;
    std::ifstream argv("new_input.json");
    json data = json::parse(argv);
    std::ofstream myfile_e;
    std::ofstream myfile_h;
    std::ofstream myfile_RK4;
    std::ofstream myfile_damped;
    std::ofstream myfile_force;

    myfile_e.open ("data0_1.txt");
    myfile_h.open ("data1_1.txt");
    myfile_RK4.open ("data2_1.txt");
    myfile_damped.open ("data3_1.txt");
    myfile_force.open ("data4_1.txt");

    myfile_e << data["n"] << ' ' << data["omega"] << '\n';
    myfile_h << data["n"] << ' ' << data["omega"] << '\n';
    myfile_RK4 << data["n"] << ' ' << data["omega"] << '\n';
    myfile_damped << data["n"] << ' ' << data["omega"] << '\n';
    myfile_force << data["n"] << ' ' << data["omega"] << '\n';

    MyState<double> A{std::array<double,2>{data["x0"], data["y0"]}};
    MyState<double> B{std::array<double,2>{data["x0"], data["y0"]}};
    MyState<double> C{std::array<double,2>{data["x0"], data["y0"]}};
    MyState<double> D{std::array<double,2>{data["x0"], data["y0"]}};
    MyState<double> E{std::array<double,2>{data["x0"], data["y0"]}};

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

    auto start_eu = sc.now();
    for (int i = 0; i < data["n"]; ++i)
    {
        A = Euler<MyState<double>>::make_step_eul(A, 0.01, myfile_e, data["omega"]);
    }
    auto end_eu = sc.now();

    auto start_h = sc.now();
    for (int i = 0; i < data["n"]; ++i)
    {
        B = Euler<MyState<double>>::make_step_hoin(B, 0.01, myfile_h, data["omega"]);
    }
    auto end_h = sc.now();

    auto start_RK = sc.now();
    for (int i = 0; i < data["n"]; ++i)
    {
        C = Euler<MyState<double>>::make_step_RK4(C, 0.01, myfile_RK4, data["omega"]);
    }
    auto end_RK = sc.now();

    for (int i = 0; i < data["n"]; ++i)
    {
        D = Euler<MyState<double>>::make_step_hoin_damped(D, 0.01, myfile_damped, data["omega"], data["gamma"][0]);
    }

    for (int i = 0; i < data["n"]; ++i)
    {
        E = Euler<MyState<double>>::make_step_RK4_force(E, 0.01, myfile_force, data["omega"], t, data["gamma"][0], data["ampl"]);
        t += 0.01;
    }

    /*MyState<double> X{std::array<double,2>{1.00, 2.00}};
    MyState<double> Y{std::array<double,2>{3.00, 4.00}};
    X.print(X + Y);
    X.print(X / 2);
    X.print(X * 2);
    X = Y;
    X.print(X);*/

    auto time_span_e = static_cast<std::chrono::duration<double>>(end_eu - start_eu);
    auto time_span_h = static_cast<std::chrono::duration<double>>(end_h - start_h);
    auto time_span_RK = static_cast<std::chrono::duration<double>>(end_RK - start_RK);

    std::cout << time_span_e.count() << " " << time_span_h.count() << " " << time_span_RK.count() << std::endl;
    std::cout << Quality(data["gamma"][0], data["omega"]) << std::endl;

    myfile_e.close();
    myfile_h.close();
    myfile_RK4.close();
    myfile_damped.close();
    return 0;
}