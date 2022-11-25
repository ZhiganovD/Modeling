#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <vector>
#include <array>
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

    MyState operator+( MyState y) 
    {
        return MyState {std::array<MP,2> {state[0] + y[0], state[1] + y[1]}};
    }

    MyState operator*(double const a) 
    {
        return MyState {std::array<MP,2> {state[0] * a, state[1] * a}};
    }

    MyState& operator/(double const a) 
    {
        return MyState {std::array<MP,2> {state[0] / a, state[1] / a}};
    }

    MyState& operator=(MyState& y) 
    {
        return MyState {std::array<MP,2> {y[0], y[1]}};
    }
};

template <class A>
class Euler
{
public:
    static A make_step(A& state,  float dt, std::ofstream &myfile_e, double omega)
    {
        myfile_e << state[0] << ' ' << state[1] << '\n'; 
        auto tmp = state + state.func(omega)*dt;
        state =  tmp;
        return state;
    }
};

int main()
{
    std::ifstream argv("new_input.json");
    json data = json::parse(argv);
    std::ofstream myfile_e;
    std::ofstream myfile_h;
    std::ofstream myfile_acc;
    myfile_e.open ("data0_1.txt");
    myfile_h.open ("data1_1.txt");
    myfile_acc.open ("data2_1.txt");
    myfile_e << data["n"] << ' ' << data["omega"] << '\n';
    MyState<double> A{std::array<double,2>{data["x0"], data["y0"]}};
    auto k = data["xk"];
    const double & my_value = data["xk"];
    double h = (static_cast<double>(data["xk"]) - static_cast<double>(data["x0"])) / static_cast<double>(data["n"]);
    for (int i = 0; i < data["n"]; ++i)
    {
        A = Euler<MyState<double>>::make_step(A, 0.01, myfile_e, data["omega"]);
    }

    //auto step = Euler<MyState<double>>::make_step(A, 0.01, myfile_e, data["omega"]);

    std::cout << "hello" << std::endl;
    //std::cout << step[0] << step[1] << std::endl;

    return 0;
}