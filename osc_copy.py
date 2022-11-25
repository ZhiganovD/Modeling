#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

std::vector<double> func(std::vector<double> &f, double omega)
{
    std::vector<double> k;
    k.push_back(f[1]);
    k.push_back((-1) * pow(omega, 2) * f[0]);
    return k;
}

std::vector<double> operator+(std::vector<double> const &x, std::vector<double> const &y) 
{
    std::vector<double> f;
    f.push_back(x[0] + y[0]);
    f.push_back(x[1] + y[1]);
    return f;
}

std::vector<double> operator*(std::vector<double> const &x, double const a) 
{
    std::vector<double> f;
    f.push_back(x[0] * a);
    f.push_back(x[1] * a);
    return f;
}

std::vector<double> operator/(std::vector<double> const &x, double const a) 
{
    std::vector<double> f;
    f.push_back(x[0] / a);
    f.push_back(x[1] / a);
    return f;
}

void euler (std::vector<double> &f, double h, std::ofstream &myfile_e, double omega)
{
    myfile_e << f[0] << ' ' << f[1] << '\n'; 
    f = f + func(f, omega) * h;
    
}

void heun (std::vector<double> &f, std::vector<double> &g, double h, std::ofstream &myfile_h, double omega)
{
    myfile_h << f[0] << ' ' << f[1] << '\n';
    g = f + func(f, omega) * h;
    f = f + (func(f, omega) + func(g, omega)) * h / 2.0;
}



void main(int argc, char *argv[])
{
    if (argc != 5){
        std::cout << "WRONG NUMBER OF PARAMETERS!!!" << std::endl;
        exit(1);
    }
    else{
        int a = std::atof(argv[2]);
    }
    std::ofstream myfile_e;
    std::ofstream myfile_h;
    std::ofstream myfile_acc;
    myfile_e.open ("data.txt");
    myfile_h.open ("data1.txt");
    myfile_acc.open ("data2.txt");
    double x0, y0, xk, n, x, y, h, omega;
    //std::cin >> x0 >> y0 >> xk >> n >> omega;
    myfile_e << argv[3] << ' ' << argv[4] << '\n';
    myfile_h << argv[3] << ' ' << argv[4] << '\n';
    std::vector <double> f;
    std::vector <double> g;
    std::vector <double> l;
    f.push_back(argv[0]);
    f.push_back(argv[1]);
    l.push_back(argv[0]);
    l.push_back(argv[1]);
    g.push_back(0);
    g.push_back(0);
    h = (argv[2] - argv[0]) / int(argv[3]);
    for (int i = 0; i < int(argv[3]); ++i)
    {
        euler(f, h, myfile_e, argv[4]);
        heun(l, g, h, myfile_h, argv[4]);
    }


    myfile_e.close();
    myfile_h.close();
    myfile_acc.close();

}