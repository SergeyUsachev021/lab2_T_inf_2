#include "../include/shannonFano.h"
#include "../include/huffmanCode.h"
#include "../include/task.h"

// Функция для выполнения первой задачи: кодирование символов методом Фано
void task1(std::vector<Symbol>& fanoCode)
{
    // Сортируем символы по вероятности
    sort(fanoCode.begin(), fanoCode.end(), compareFano);

    // Делим символы на группы и генерируем коды Фано
    divideSymbols(fanoCode, 0, fanoCode.size() - 1);

    // Печатаем сгенерированные коды Фано
    printFano(fanoCode);

    // Вычисляем энтропию
    double entropyNum = entropy(fanoCode);
    double maxEntropy = log2f(fanoCode.size()); // Максимальная энтропия для данной системы
    std::cout << "entropy = " << entropyNum << "\n";

    // Вычисляем среднюю длину кодов
    double averageLengthCodeCombination = averageLengthCombination(fanoCode);
    std::cout << "average length code combination = " << averageLengthCodeCombination << "\n";

    // Вычисляем избыточность
    double redundancy = 1 - (entropyNum / maxEntropy);
    std::cout << "redundancy = " << redundancy << std::endl;
}

// Функция для выполнения второй задачи: сравнение кодов Фано и Хаффмана
void task2(std::vector<Symbol>& fanoCode, std::vector<std::pair<char, double>>& symbolProbabilities, std::vector<std::string>& symbols)
{
    // Сортируем символы по вероятности
    sort(fanoCode.begin(), fanoCode.end(), compareFano);

    // Делим символы на группы и генерируем коды Фано
    divideSymbols(fanoCode, 0, fanoCode.size() - 1);

    // Печатаем коды Фано
    std::cout << "Fano code:\n";
    int i = 0;
    for (const auto& symbol : fanoCode)
    {
        std::cout << symbols[i] << ": " << symbol.code << std::endl; // Выводим символ и его код
        i += 1;
    }

    // Вычисляем среднюю длину кодов Фано
    double averageLengthCodeCombination = averageLengthCombination(fanoCode);
    std::cout << "average length Fano code combination = " << averageLengthCodeCombination << "\n";

    // Строим дерево Хаффмана на основе вероятностей символов
    Node* root = buildHuffmanTree(symbolProbabilities); // Построение дерева

    std::vector<std::string> huffmanCodes(256); // Вектор для хранения кодов Хаффмана
    generateCodes(root, "", huffmanCodes); // Генерация кодов Хаффмана

    // Печатаем коды Хаффмана
    std::cout << "Huffman code:\n";
    i = 0;
    for (const auto& pair : symbolProbabilities) {
        std::cout << symbols[i] << ": " << huffmanCodes[static_cast<unsigned char>(pair.first)] << "\n"; // Выводим символ и его код Хаффмана
        i += 1;
    }

    // Вычисляем среднюю длину кодов Хаффмана
    averageLengthCodeCombination = averageLengthCombination(symbolProbabilities, huffmanCodes);
    std::cout << "average length Huffman code combination = " << averageLengthCodeCombination << "\n";

    deleteTree(root); // Освобождаем память, удаляя дерево Хаффмана
}

// Функция для выполнения третьей задачи: вычисление энтропии и избыточности для блоков текста
void task3(std::string& line)
{
    const int maxBlockLength = 5; // Максимальная длина блока
    std::vector<std::map<std::string, int>> blocks(maxBlockLength); // Вектор для хранения частоты блоков

    // Извлечение блоков и подсчет их частоты
    for (int blockLength = 1; blockLength <= maxBlockLength; blockLength++) {
        for (int iLine = 0; iLine <= line.size() - blockLength; iLine++) {
            std::string block = line.substr(iLine, blockLength); // Извлечение блока из строки
            blocks[blockLength - 1][block] += 1; // Увеличиваем частоту блока в соответствующем словаре
        }
    }

    std::vector<int> total(5); // Вектор для хранения общего количества блоков каждой длины
    for (int length = 0; length < maxBlockLength; length++)
    {
        int totalCount = 0;
        for (const auto& pair : blocks[length])
        {
            totalCount += pair.second; // Считаем общее количество блоков данной длины
        }
        total[length] = totalCount; // Сохраняем общее количество блоков в векторе total
    }

    // Вычисление энтропии и избыточности для каждого блока
    for (int i = 0; i < maxBlockLength; i++)
    {
        double entropy = 0;
        for (const auto pair : blocks[i]) {
            double probability = static_cast<double>(pair.second) / total[i]; // Вероятность блока
            entropy += probability * log2(probability); // Обновляем значение энтропии
        }
        entropy *= -1; // Энтропия всегда положительна
        std::cout << "entropy block length " << i + 1 << " = " << entropy << std::endl;

        double maxBits = log2(blocks[i].size()); // Максимальное количество бит для данного количества уникальных блоков
        double redundancy = 1 - (entropy / maxBits); // Вычисляем избыточность

        std::cout << "redundancy block length " << i + 1 << " = " << redundancy << "\n" << std::endl;
    }
}
