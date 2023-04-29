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

class Object {
public:
    float x_b;
    float x_e;
    float y_b;
    float y_e;
    //float size;
    Object(float x_b, float x_e, float y_b, float y_e): x_b(x_b), x_e(x_e), y_b(y_b), y_e(y_e) {}


};

class Laser {
public:
    float x_0;
    float y_0;
    float angle;

    Laser(float x_0, float y_0, float angle): x_0(x_0), y_0(y_0), angle(angle) {}

    bool do_interact(Object hit, Net grid):
        if 


};


class Net {
public:
    float x_max;
    float y_max;
    float x_min;
    float y_min;
    
    Net(float x_max, float y_max, float x_min, float y_min): x_max(x_max), y_max(y_max), x_min(x_min), y_min(y_min) {}



    
};

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


    
    return 0;
}