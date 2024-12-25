#include "../include/shannonFano.h"

// Функция для сравнения двух символов по вероятности (по убыванию)
bool compareFano(const Symbol& a, const Symbol& b)
{
    return a.probability > b.probability; // Сравниваем вероятности символов
}

// Функция для деления символов на две группы в процессе кодирования
void divideSymbols(std::vector<Symbol>& symbols, int left, int right)
{
    if (left >= right) return; // Базовый случай: если нет символов для деления
    else if (right - left == 1) // Если осталось только два символа
    {
        symbols[left].code += "1"; // Присваиваем код '1' первому символу
        symbols[right].code += "0"; // Присваиваем код '0' второму символу
    }
    else // Если больше двух символов
    {
        double total = 0; // Переменная для хранения общей вероятности

        // Суммируем вероятности всех символов в текущем диапазоне
        for (int i = left; i <= right; i++)
        {
            total += symbols[i].probability;
        }

        double prob = 0; // Переменная для накопления вероятности
        double cumul = 1; // Переменная для отслеживания разницы между группами
        int index = -1; // Индекс разделяющего символа

        // Проходим по всем символам и определяем, как их разделить
        for (int i = left; i <= right; ++i)
        {
            prob += symbols[i].probability; // Накопление вероятности

            // Условие для определения, к какой группе добавить текущий символ
            if (cumul > std::abs(total - 2 * prob) || (prob > total && i == left))
            {
                symbols[i].code += "1"; // Добавляем '1' к коду символа
                cumul = std::abs(total - 2 * prob); // Обновляем разницу
            }
            else
            {
                symbols[i].code += "0"; // Добавляем '0' к коду символа
                if (index < 0) // Если индекс еще не установлен
                {
                    index = i; // Устанавливаем индекс разделяющего символа
                }
            }
        }

        // Если индекс не был установлен, устанавливаем его на следующий элемент
        if (index < 0)
        {
            index = left + 1;
        }

        // Рекурсивно делим левую и правую части символов
        divideSymbols(symbols, left, index - 1);
        divideSymbols(symbols, index, right);
    }
}

// Функция для печати символов и их соответствующих кодов
void printFano(std::vector<Symbol>& symbols)
{
    for (const auto& symbol : symbols)
    {
        std::cout << symbol.symbol << " " << symbol.code << std::endl; // Выводим символ и его код
    }
}

// Функция для вычисления энтропии системы символов
double entropy(const std::vector<Symbol>& symbols)
{
    double entropy = 0; // Инициализация переменной энтропии

    for (const auto& symbol : symbols){
        entropy += symbol.probability * log2f(symbol.probability); // Вычисляем вклад каждого символа в энтропию
    }
    entropy *= -1; // Энтропия всегда положительна

    return entropy; // Возвращаем вычисленную энтропию
}

// Функция для вычисления средней длины кодовых комбинаций
double averageLengthCombination(const std::vector<Symbol>& symbols)
{
    double averageLengthCombination = 0; // Инициализация переменной средней длины

    for (const auto& symbol : symbols){
        averageLengthCombination += symbol.probability * symbol.code.length(); // Суммируем произведение вероятности на длину кода каждого символа
    }
    
    return averageLengthCombination; // Возвращаем среднюю длину комбинации кодов
}
