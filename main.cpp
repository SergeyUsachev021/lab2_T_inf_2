#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <fstream>
#include <cstring> // Для strerror
#include <cerrno>  // Для errno

#include "../include/huffmanCode.h"
#include "../include/shannonFano.h"
#include "../include/task.h"

// Основная функция
int main() {
    std::cout << "TASK 1:" << std::endl;
    std::vector<Symbol> fanoCode = {
        {'A', 0.28}, {'B', 0.22}, {'C', 0.15}, {'D', 0.11},
        {'E', 0.11}, {'F', 0.07}, {'G', 0.04}, {'H', 0.02}
    };
    task1(fanoCode);
    std::cout << std::endl;




    std::cout << "TASK 2:" << std::endl;

    std::vector<std::pair<std::string, double>> taskVar =
    {
        {"Z1", 0.9},
        {"Z2", 0.1}
    };

    fanoCode = {};
    std::vector<std::pair<char, double>> huffmanCode = {};

    std::vector<std::string> symbol(20);
    char ci = 65;
    int i = 0;
    for (const auto pair1 : taskVar)
    {
        for (const auto pair2 : taskVar)
        {
            for (const auto pair3 : taskVar)
            {
                fanoCode.push_back({ci, pair1.second*pair2.second*pair3.second});
                huffmanCode.push_back({ci, pair1.second*pair2.second*pair3.second});
                symbol[i] = pair1.first+pair2.first+pair3.first;
                ci+=1;
                i+=1;
            }
        }
    }

    task2(fanoCode, huffmanCode, symbol);

    std::cout<< std::endl;



    std::ifstream file("../words.txt");
    if(!file.is_open())
    {
        std::cerr << "not open: " << strerror(errno) << std::endl;
        file.close();
        return 1;
    }
    std::string line;
    std::getline(file, line);
    file.close();

    task3(line);

    return 0;
}