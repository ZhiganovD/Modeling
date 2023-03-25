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
#include <vector>
using json = nlohmann::json;

float reccur(int n, float x, float a)
{
    if (n == 0)
    {
        return x;
    }

    return a * reccur(n - 1, x, a) * (1 - reccur(n - 1, x, a));

}

float func(float x, float a)
{
    return a * x * (1 - x);
}

void random_joke(int n, float a, float x0, int k, std::ofstream &myfile_rand)
{
    float parts[k];
    std::fill_n(parts, k, x0);

    for (int i = 0; i < n; ++i)
    {   
        for (int j = 0; j < k; ++j)
        {
            myfile_rand << parts[j] << ' ';
            float alpha = ((j + 1) * a) / k; 
            parts[j] = func(parts[j], alpha);
        }
        myfile_rand << std::endl;
    }
    
    for (int i = 0; i < k; ++i)
    {
        myfile_rand << ((i + 1) * a) / k << ' ';
    }

}

int main()
{
    std::ifstream argv("joke.json");
    json data = json::parse(argv);
    std::ofstream myfile_rand;

    myfile_rand.open ("joke.txt");
    int n = data["steps"];
    float a = data["alpha"];
    float x0 = data["x0"];
    int particles = data["particles"];


    random_joke(n, a, x0, particles, myfile_rand);

    
    return 0;
}