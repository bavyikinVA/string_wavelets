#include <iostream>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::vector<double>> morlet_wavelet(std::vector<double> data, int data_size, std::vector<double> scales, int weight_size)
{
    std::vector<std::vector<double>> coef(weight_size, std::vector<double>(data_size));
    for (int i = 0; i < weight_size; i++)
    {
        for (int j = 0; j < data_size; j++)
        {
            double w0 = 0;
            for (int k = 0; k < data_size; k++)
            {
                double t = (double)(k - j) / scales[i];
                w0 = w0 + data[k] * 0.75 * exp(-(t * t) / 2) * cos(6 * t);
            }
            coef[i][j] = (w0 / sqrt(scales[i]));
        }
    }
    return coef;
}

int main()
{
    std::ifstream fin("C:\\Users\\bavyk\\source\\repos\\epic_parallel\\epic_parallel\\input.txt");
    std::string line;
    std::vector<double> data;

    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        double dat;
        while (iss >> dat)
        {
            data.push_back(dat);
        }
    }
    fin.close();
    int data_size = data.size();
    int scales_size = 100;
    std::vector<double> scales;
    for (int i = 0; i < scales_size; i++)
    {
        scales.push_back(i + 1);
    }

    double time = (double)clock() / CLOCKS_PER_SEC;
    printf("start_morlet");
    std::vector<std::vector<double>> result = morlet_wavelet(data, data_size, scales, scales_size);
    double time_diff = (((double)clock()) / CLOCKS_PER_SEC) - time;

    std::ofstream fout("C:\\Users\\bavyk\\source\\repos\\string_wavelets\\string_wavelets\\output.txt");

    // Вывод результатов
    double time2 = ((double)clock()) / CLOCKS_PER_SEC;
    for (int i = 0; i < scales_size; i++)
    {
        for (int j = 0; j < data_size; j++)
        {
            fout << std::to_string(result[i][j]) << " ";
        }
        fout << std::endl;
    }
    fout.close();

    double time_diff2 = (((double)clock()) / CLOCKS_PER_SEC) - time2;
    printf("The elapsed time is %lf seconds\n", time_diff);
    printf("The elapsed time is %lf seconds\n", time_diff2);

    system("pause");

    return 0;
}
