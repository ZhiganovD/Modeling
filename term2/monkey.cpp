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

void random1(int first, int second, int third, int n, std::ofstream &myfile_rand)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, n); // define the range

    float count = 0.0;

    for (int f = 0; f < 1000; ++f)
    {
        std::vector<int> arr;
        for (int i = 0; i < n; ++i)
        {
            arr.push_back(distr(gen));
        }

        while ((arr[arr.size() - 1] != third) || (arr[arr.size() - 2] != second) || (arr[arr.size() - 3] != first))
        {
            arr.push_back(distr(gen));
        }
        count += arr.size();
    }

    myfile_rand << first << second << third << " " << count / 1000.0 << std::endl;
}


int main()
{
    std::ifstream argv("rand_input.json");
    json data = json::parse(argv);
    std::ofstream myfile_rand;

    myfile_rand.open ("data3.0.txt");
    int n = data["map"];

    for(int i = 1; i < n + 1; ++i)
    {
        for(int j = 1; j < n + 1; ++j)
        {
            for(int k = 1; k < n + 1; ++k)
            {
                random1(i, j, k, n, myfile_rand);
            }
        }
    }
    return 0;
}