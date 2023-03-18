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

class ComplexNum {
public:
    float prob;
    float value;

    ComplexNum(float prob, float value): prob(prob), value(value) {}
};

void random_walk(ComplexNum right, ComplexNum left, int n, std::ofstream &myfile_rand, float start, int particles)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 1); // define the range
    float open = start;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < particles; ++j)
        {
            myfile_rand << start << ' ';
            int k = distr(gen);
            if(k == 0)
            {
                start += right.value;
            } else
            {
                start += left.value;
            }
        }
        myfile_rand << std::endl;
    }

}




int main()
{
    std::ifstream argv("rand_walk.json");
    json data = json::parse(argv);
    std::ofstream myfile_rand;

    myfile_rand.open ("data_rand_walk.txt");
    int n = data["steps"];
    float k = data["path"];
    float p = data["prob"];
    float start = data["start"];
    int particles = data["particles"];

    ComplexNum right(k, p);
    ComplexNum left(k, (-1) * p);

    random_walk(right, left, n, myfile_rand, start, particles);

    
    return 0;
}