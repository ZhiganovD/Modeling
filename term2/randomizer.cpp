#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cmath>
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;

void random1(int k, int n, std::ofstream &myfile_rand)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, k); // define the range

    for(int i = 0; i < n; ++i)
    {
        myfile_rand << distr(gen) << ' ';
    }

    myfile_rand << std::endl;
}

void random2(int k, int n, std::ofstream &myfile_rand)
{
    srand (static_cast <unsigned> (time(0)));

    for(int i = 0; i < n; ++i)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / k);
        myfile_rand << r << ' ';
    }

    myfile_rand << std::endl;
}

void norm_distr(float mu, float sigma, int n, std::ofstream &myfile_rand)
{
    std::normal_distribution<> d{mu, sigma};

    std::random_device rd{};
    std::mt19937 gen{rd()};

    for(int i = 0; i < n; ++i)
    {
        myfile_rand << d(gen) << '\n';
    }

    myfile_rand << std::endl;
}

int main()
{
    std::ifstream argv("rand_input.json");
    json data = json::parse(argv);
    std::ofstream myfile_rand;

    myfile_rand.open ("data1.0.txt");
    
    //random1(data["k"], data["n"], myfile_rand);
    //random2(data["k"], data["n"], myfile_rand);
    norm_distr(data["mu"], data["sigma"], data["n"], myfile_rand);
    return 0;
}