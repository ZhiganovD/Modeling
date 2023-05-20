#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "json.hpp"
#include <fstream>
#include <chrono>
#include <ctime>
#include <vector>
using json = nlohmann::json;
using namespace std::chrono;
//#pragma omp parallel for num_threads(4)


void print(std::vector<float> grid1d, std::ofstream &myfile_task)
{
    for (int i = 0; i < grid1d.size(); ++i)
    {
        myfile_task << grid1d[i] << " ";
    }
    myfile_task << '\n';
}

void print_2d(std::vector<std::vector<float>> grid2d, std::ofstream &myfile_task, int rows, int col)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            myfile_task << grid2d[i][j] << ' ';
        }
        myfile_task << std::endl;
    }
    myfile_task << '\n';
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


void streams_1d(std::vector<float>& grid1d, float sigma, float step, float delta)
{
    for (int i = 1; i < grid1d.size() - 1; ++i)
    {
        float j_left = (grid1d[i] - grid1d[i - 1]) * sigma / step;
        float j_right = (grid1d[i + 1] - grid1d[i]) * sigma / step;
        float j_sum = (j_right - j_left) / step;

        grid1d[i] += j_sum * delta;
    }
}

void streams_2d(std::vector<std::vector<float>>& grid2d, float sigma, float step, float delta, float rows, float col)
{
    for (int j = 1; j < col -1; ++j)
    {
        grid2d[0][j] = grid2d[1][j];
        grid2d[rows - 1][j] = grid2d[rows - 2][j];
    }
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < col -1; ++j)
        {
            float j_left = (grid2d[i][j] - grid2d[i][j - 1]) * sigma / step;
            float j_right = (grid2d[i][j + 1] - grid2d[i][j]) * sigma / step;
            float j_down = (grid2d[i][j] - grid2d[i - 1][j]) * sigma / step;
            float j_up = (grid2d[i + 1][j] - grid2d[i][j]) * sigma / step;
            float j_sum = (j_right - j_left) / step + (j_up - j_down) / step;

            grid2d[i][j] += j_sum * delta;
        }
    }
}




int main()
{
    std::ifstream argv("task.json");
    json data = json::parse(argv);
    std::ofstream myfile_task_1d;
    std::ofstream myfile_task_2d;

    myfile_task_1d.open ("task_1d.txt");
    myfile_task_2d.open ("task_2d.txt");
    int const rows = data["rows"];
    int const col = data["columns"];
    float phi_0 = data["phi_0"];
    float phi_k = data["phi_k"];
    float d = data["step"];
    float dt = data["delta"];
    int num = data["iter"];
    float sigma = data["sigma"];
    std::vector<float> grid1d(rows, 0);
    std::vector<std::vector<float>> grid2d;
    grid2d.resize(rows, std::vector<float>(col));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            grid2d[i].push_back(0);
        }
    }
    for (int i = 0; i < rows; ++i)
    {
        grid2d[i][0] = 2 * phi_0 - grid2d[i][1];
        grid2d[i][col - 1] = 2 * phi_k - grid2d[i][col - 2];
    }
    grid1d[0] = 2 * phi_0 - grid1d[1];
    grid1d[rows - 1] = 2 * phi_k - grid1d[rows - 2];

    //print(grid1d, myfile_task_1d);
    //print_2d(grid2d, myfile_task_2d, rows, col);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < num; ++i)
    { 
        //streams_1d(grid1d, sigma, d, dt);
        streams_2d(grid2d, sigma, d, dt, rows, col);
        //print(grid1d, myfile_task_1d);
    }
    print_2d(grid2d, myfile_task_2d, rows, col);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    std::cout <<  duration.count() << std::endl;

    
    return 0;
}