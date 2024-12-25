#include "../include/shannonFano.h"


bool compareFano(const Symbol& a, const Symbol& b)
{
    return a.probability > b.probability;
}

void divideSymbols(std::vector<Symbol>& symbols, int left, int right)
{
    if (left >= right) return;
    else if (right-left == 1)
    {
        symbols[left].code += "1";
        symbols[right].code += "0";
    }
    else
    {
    double total = 0;
    for (int i = left; i<=right; i++)
    {
        total += symbols[i].probability;
    }

    double prob = 0;
    double cumul = 1;
    int index = -1;
    for (int i = left; i <= right; ++i)
    {
        prob += symbols[i].probability;

        if ( cumul > std::abs(total - 2*prob) || (prob > total && i == left))
        {
            symbols[i].code += "1";
            cumul = std::abs(total - 2*prob);
        }
        else
        {
            symbols[i].code += "0";
            if (index < 0)
            {
                index = i;
            }
        }
    }
    if (index < 0)
    {
        index = left+1;
    }

    divideSymbols(symbols, left, index - 1);
    divideSymbols(symbols, index, right);
    }
}

void printFano(std::vector<Symbol>& symbols)
{
    for (const auto& symbol : symbols)
    {
        std::cout<< symbol.symbol << " "<< symbol.code << std::endl;
    }
}

// Функция определения энтропии
double entropy(const std::vector<Symbol>& symbols)
{
    double entropy = 0;

    for (const auto& symbol : symbols){
        entropy += symbol.probability * log2f(symbol.probability);
    }
    entropy *= -1;

    return entropy;
}

// функция для определения средней длины комбинации
double averageLengthCombination(const std::vector<Symbol>& symbols)
{
    double averageLengthCombination = 0;

    for (const auto& symbol : symbols){
        averageLengthCombination += symbol.probability * symbol.code.length();
    }
    return averageLengthCombination;
}