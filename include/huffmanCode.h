#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

// Структура узла дерева Хаффмана
struct Node {
    char symbol; // Символ
    double probability; // Вероятность
    Node* left; // Указатель на левое поддерево
    Node* right; // Указатель на правое поддерево

    Node(char symbol, double probability) :  symbol(symbol),
                                                    probability(probability),
                                                    left(nullptr),
                                                    right(nullptr){};
};

// Функция для сравнения узлов (по вероятности)
bool compare(Node* a, Node* b);

// Функция для построения дерева Хаффмана
Node* buildHuffmanTree(const std::vector<std::pair<char, double>>& symbolProbabilities);

// Рекурсивная функция для генерации кодов
void generateCodes(Node* root, const std::string& str, std::vector<std::string>& codes);

// Функция для освобождения памяти дерева
void deleteTree(Node* root);

// Функция определения энтропии
double entropy(const std::vector<std::pair<char, double>>& symbolProbabilities);

// функция для определения средней длины комбинации
double averageLengthCombination(const std::vector<std::pair<char,
                                double>>& symbolProbabilities,
                                const std::vector<std::string>& codes);