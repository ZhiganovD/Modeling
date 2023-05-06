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
int Bine(int n)
{
    if (n == 0)
    {
        return 0.0;
    } else
    {
        return (1 / sqrt(5)) * (pow((1 + sqrt(5)) / 2, n) - pow((1 - sqrt(5)) / 2, n));
    }
}

void print(std::vector<float> grid1d, std::ofstream &myfile_task)
{
    for (int i = 0; i < grid1d.size(); ++i)
    {
        myfile_task << grid1d[i] << " ";
    }
    myfile_task << '\n';
}

//(phi_t_i1 - phi_t_i - phi_t_i_1) / d^2 = (phi_t1_i - phi_t_i) / dt;

void laplas_t(std::vector<float>& grid1d, float dt, float d, std::ofstream &myfile_task)
{
    for(int i = 1; i < grid1d.size() - 1; ++i)
    {
        grid1d[i] = grid1d[i] + (dt / (pow(d, 2))) * (grid1d[i + 1] - grid1d[i] + grid1d[i - 1]);
    }
}

void laplas(std::vector<float>& grid1d)
{
    float b = (grid1d[grid1d.size() - 1] - Bine(grid1d.size() - 2) * grid1d[0]) / Bine(grid1d.size() - 1);
    for (int i = 1; i < grid1d.size() - 1; ++i)
    {
        grid1d[i] = grid1d[0] * Bine(i - 1) + b * Bine(i);
    }
}


int main()
{
    std::ifstream argv("task.json");
    json data = json::parse(argv);
    std::ofstream myfile_task;

    myfile_task.open ("task.txt");
    int rows = data["rows"];
    int col = data["columns"];
    float phi_0 = data["phi_0"];
    float phi_k = data["phi_k"];
    float d = data["step"];
    float dt = data["delta"];
    int num = data["iter"];
    std::vector<float> grid1d(rows, 0);
    grid1d[0] = phi_0;
    grid1d[rows - 1] = phi_k;

    print(grid1d, myfile_task);

    laplas(grid1d);

    print(grid1d, myfile_task);

    for (int i = 0; i < num; ++i)
    { 
        //std::cout << 'a' << '\n';
        laplas_t(grid1d, dt, d, myfile_task);
        if (i % 10 == 0)
        {
            print(grid1d, myfile_task);
        }
    }

    print(grid1d, myfile_task);

    
    return 0;
}