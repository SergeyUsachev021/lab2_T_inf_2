#include "../include/shannonFano.h"
#include "../include/huffmanCode.h"
#include "../include/task.h"


void task1(std::vector<Symbol>& fanoCode)
{
    sort(fanoCode.begin(), fanoCode.end(), compareFano);

    divideSymbols(fanoCode, 0, fanoCode.size()-1);

    printFano(fanoCode);

    double entropyNum = entropy(fanoCode);
    double maxEntropy = log2f(fanoCode.size());
    std::cout << "entropy = " << entropyNum << "\n";

    double averageLengthCodeCombination = averageLengthCombination(fanoCode);
    std::cout << "average lenght code combination = " << averageLengthCodeCombination << "\n";

    double redundancy = 1 - (entropyNum/maxEntropy);
    std::cout << "redundancy = " << redundancy << std::endl;

}


void task2(std::vector<Symbol>& fanoCode, std::vector<std::pair<char, double>>& symbolProbabilities, std::vector<std::string>& symbols)
{
    sort(fanoCode.begin(), fanoCode.end(), compareFano);

    divideSymbols(fanoCode, 0, fanoCode.size()-1);

    std::cout << "Fano code:\n";
    int i = 0;
    for (const auto& symbol : fanoCode)
    {
        std::cout<< symbols[i] << ": "<< symbol.code << std::endl;
        i+=1;
    }

    double averageLengthCodeCombination = averageLengthCombination(fanoCode);
    std::cout << "average lenght Fano code combination = " << averageLengthCodeCombination << "\n";



    Node* root = buildHuffmanTree(symbolProbabilities); // Построение дерева

    std::vector<std::string> huffmanCodes(256); // Вектор для хранения кодов Хаффмана
    generateCodes(root, "", huffmanCodes); // Генерация кодов

    std::cout << "Huffman code:\n";
    i = 0;
    for (const auto& pair : symbolProbabilities) {
        std::cout << symbols[i] << ": " << huffmanCodes[static_cast<unsigned char>(pair.first)] << "\n";
        i+=1;
    }

    averageLengthCodeCombination = averageLengthCombination(symbolProbabilities, huffmanCodes);
    std::cout << "average lenght Huffman code combination = " << averageLengthCodeCombination << "\n";

    deleteTree(root); // Освобождаем память
}


void task3(std::string& line)
{

    const int maxBlockLength = 5;
    std::vector<std::map<std::string, int>> blocks(maxBlockLength);

    for (int blockLength = 1; blockLength <= maxBlockLength; blockLength++) {
        for (int iLine = 0; iLine <= line.size() - blockLength; iLine++) {
            std::string block = line.substr(iLine, blockLength); // Извлечение блока
            blocks[blockLength - 1][block] += 1; // Увеличиваем частоту блока
        }
    }

    std::vector<int> total(5);
    for (int length = 0; length < maxBlockLength; length++)
    {
        int totalCount = 0;
        for (const auto& pair : blocks[length])
        {
            totalCount += pair.second; // Считаем общее количество блоков
        }
        total[length] = totalCount;
    }


    for (int i = 0; i < maxBlockLength; i++)
    {
        double entropy = 0;
        for (const auto pair : blocks[i]) {
            double probability = static_cast<double>(pair.second) / total[i];
            entropy += probability * log2(probability);
        }
        entropy *= -1;
        std::cout << "entropy blok length " << i+1 << " = " << entropy << std::endl;

        double maxBits = log2(blocks[i].size());
        double redundancy = 1- (entropy/maxBits);

        std::cout << "redundancy blok length " << i+1 << " = " << redundancy << "\n" << std::endl;
    }
}
