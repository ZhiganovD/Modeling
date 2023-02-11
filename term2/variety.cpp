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

bool random1(int k, int n)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, k); // define the range

    int arr[k + 1];
    std::fill(arr, arr + k + 1, 0);

    for(int i = 0; i < n; ++i)
    {
        arr[distr(gen)] += 1;
    }
    bool out = true;
    for(int i = 1; i < k + 1; ++i)
    {
        if(arr[i] == 0)
        {
            out = false;
        }
    } 

    return out;
}


int main()
{
    std::ifstream argv("rand_input.json");
    json data = json::parse(argv);
    std::ofstream myfile_rand;

    myfile_rand.open ("data2.0.txt");

    float t = 1000.0;
    float count = 0.0;
    
    for (int i = 0; i < t; ++i)
    {
        if(random1(static_cast<int>(data["k"]), data["n"]))
        {
            ++count;
        }
    }
    std::cout << count / t << std::endl;
    std::cout << count << std::endl;
    return 0;
}