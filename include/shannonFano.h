#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>

struct Symbol
{
    char symbol;
    double probability;
    std::string code;
    Symbol (char symbol, double probability): symbol(symbol), probability(probability){};
};

// Функция сравнения вериятности
bool compareFano(const Symbol& a, const Symbol& b);

// Функция для деления массива символов на две группы
void divideSymbols(std::vector<Symbol>& symbols, int left, int right);

// вывод кода Шеннона Фано
void printFano(std::vector<Symbol>& symbols);

// Функция определения энтропии
double entropy(const std::vector<Symbol>& symbols);
// функция для определения средней длины комбинации
double averageLengthCombination(const std::vector<Symbol>& symbols);