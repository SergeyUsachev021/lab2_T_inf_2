#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <fstream>
#include <cstring> 
#include <cerrno>  

#include "../include/huffmanCode.h"
#include "../include/shannonFano.h"
#include "../include/task.h"

// Основная функция
int main() {
    std::cout << "TASK 1:" << std::endl;

    // Инициализация вектора символов с их вероятностями для задачи 1
    std::vector<Symbol> fanoCode = {
        {'A', 0.28}, {'B', 0.22}, {'C', 0.15}, {'D', 0.11},
        {'E', 0.11}, {'F', 0.07}, {'G', 0.04}, {'H', 0.02}
    };

    // Выполнение первой задачи: кодирование символов методом Фано
    task1(fanoCode);
    std::cout << std::endl;

    std::cout << "TASK 2:" << std::endl;

    // Инициализация векторов для второй задачи
    std::vector<std::pair<std::string, double>> taskVar =
    {
        {"Z1", 0.9},
        {"Z2", 0.1}
    };

    fanoCode = {}; // Очищаем вектор кодов Фано
    std::vector<std::pair<char, double>> huffmanCode = {}; // Вектор для хранения кодов Хаффмана

    std::vector<std::string> symbol(20); // Вектор для хранения символов
    char ci = 65; // Начальный символ (ASCII 'A')
    int i = 0;

    // Генерация всех возможных комбинаций символов и их вероятностей
    for (const auto pair1 : taskVar)
    {
        for (const auto pair2 : taskVar)
        {
            for (const auto pair3 : taskVar)
            {
                // Вычисляем вероятность комбинации и добавляем в векторы кодов Фано и Хаффмана
                fanoCode.push_back({ci, pair1.second * pair2.second * pair3.second});
                huffmanCode.push_back({ci, pair1.second * pair2.second * pair3.second});
                symbol[i] = pair1.first + pair2.first + pair3.first; // Формируем строку из символов
                ci += 1; // Переход к следующему символу
                i += 1; // Увеличиваем индекс для символов
            }
        }
    }

    // Выполнение второй задачи: сравнение кодов Фано и Хаффмана
    task2(fanoCode, huffmanCode, symbol);

    std::cout << std::endl;

    // Открытие файла для чтения текста
    std::ifstream file("../words.txt");
    if (!file.is_open()) // Проверка успешности открытия файла
    {
        std::cerr << "not open: " << strerror(errno) << std::endl; // Вывод ошибки, если файл не открылся
        file.close(); // Закрываем файл (хотя он уже не открыт)
        return 1; // Завершаем программу с ошибкой
    }

    std::string line; 
    std::getline(file, line); // Чтение строки из файла
    file.close(); // Закрываем файл после чтения

    // Выполнение третьей задачи: анализ строки на основе блоков
    task3(line);

    return 0; // Завершение программы успешно
}
