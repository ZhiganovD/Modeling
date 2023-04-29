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

std::vector<std::vector<float>> grid2d;


//float laplas_t(float phi_t_i1, float phi_t_i, float phi_t_i_1, float d, float phi_t1_i, float dt)
//{
    //(phi_t_i1 - phi_t_i - phi_t_i_1) / d^2 = (phi_t1_i - phi_t_i) / dt;
//}

float laplas(float n, std::vector<std::reference_wrapper<float>> grid1d)
{
    if ((n == 0) || (n == 1))
    {
        return grid1d[n];
    }
    return laplas(n - 1, grid1d) + laplas(n - 2, grid1d);
}

int main()
{
    std::ifstream argv("task.json");
    json data = json::parse(argv);
    //std::ofstream myfile_rand;

    //myfile_rand.open ("task.txt");
    int rows = data["rows"];
    int col = data["columns"];
    float phi_0 = data["phi_0"];
    float phi_k = data["phi_k"];
    float x;
    std::vector<std::reference_wrapper<float>> grid1d;
    grid1d.push_back(phi_0);
    grid1d.push_back(x);

    for (int i = 0; i < grid1d.size(); ++i)
    {
        grid1d[i] = laplas(i, grid1d);
    }

    for (int i = 0; i < grid1d.size(); ++i)
    {
        std::cout << grid1d[i];
    }

    
    return 0;
}