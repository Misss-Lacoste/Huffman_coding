#include "Node.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>
std::vector<bool> code; //рекурсия для самого сжатия по Хаффману
std::map<char, std::vector<bool>> table; //глоб.словарь, в кот хран код Хаффмана для каждого символа во входном тексте

void deleteTree(Node* node) { //функция рекурсивно удаляет бин.дерево(для освобождения памяти)
    if (node) {
        deleteTree(node->left); //удаляем левые-правые поддеревья
        deleteTree(node->right);
        delete node;
    }
}

int main() { //функция для чтения файла и его анализа
    std::string filename = "Book.txt";
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1;
    }

    std::string str;
    std::string line;
    while (std::getline(inputFile, line)) {
        str += line + "\n"; //предотвращает разрыв строк во время чтения файла
    }
    inputFile.close();

    std::map<char, int> map; //создаем словарь для хранения каждого символа во входном тексте
    frequency(map, str);

    std::list<Node*> list; //строим дерево Хаффмана. создаем список для хранения указателей на узловые объекты
    build_map(list, map); //создаем узел для для каждого символа в словаре

    Node* root = create_tree(list); //вызов ф для постройки дерева из списка узлов. мерджит 2 узла с наим.частотой встречаемости, пока не останется 1 узел

    build_table(root, code, table); //рекурсивно обходит дерево. Т.е. 0 для левого дитя, 1 для правого

    std::vector<bool> encodedBits; //созд. пустой вектор для хранения закодированных битов

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        std::vector<bool> v = table[c]; //Получает код Хаффмана (вектор битов) для текущего символа c из таблицы
        encodedBits.insert(encodedBits.end(), v.begin(), v.end());
        //Добавляет код Хаффмана v в конец вектора encodedBits. использует функцию вставки для эффективного добавления всех элементов v в encodedBits
    }

    // Запись количества закодированных битов в файл
    size_t numBits = encodedBits.size(); //получает кол-во закодированных битов
    std::ofstream outfile("encoded.bin", std::ios::binary); 
    outfile.write(reinterpret_cast<const char*>(&numBits), sizeof(numBits)); //число закодированных битов 

    char byte = 0;
    int count = 0;

    for (size_t i = 0; i < encodedBits.size(); ++i) { 
        byte = byte | (encodedBits[i] << (7 - count)); //превращаем биты в байты
        ++count;
        if (count == 8) { //проверяем, "собрался" ли байт(он же из 8 битов, да)
            outfile.write(&byte, 1);
            count = 0; //снова начинаем считать и собирать следующий байт
            byte = 0;
        }
    }
    if (count != 0) {
        outfile.write(&byte, 1);
    }
    outfile.close();

    std::vector<bool> encodedBitsFromFile;

    // Считывание количества закодированных битов из файла
    size_t numBitsFromFile = 0;
    std::ifstream infile("encoded.bin", std::ios::binary);
    infile.read(reinterpret_cast<char*>(&numBitsFromFile), sizeof(numBitsFromFile)); //считываем количество закодированных битов

    char readByte;
    while (infile.read(&readByte, 1) && encodedBitsFromFile.size() < numBitsFromFile) {
        for (int i = 7; i >= 0; --i) {
            bool bit = (readByte >> i) & 1; //извлекаем каждый бит из байта(антоним для побитового или)
            encodedBitsFromFile.push_back(bit);
        }
    }
    infile.close();

    // Ограничить количество бит, обрабатываемых для декодирования
    encodedBitsFromFile.resize(numBitsFromFile);

    std::string decodedStr = decode_sequence(root, encodedBitsFromFile); //раскодируем закодированные биты
    std::cout << "decoded" << decodedStr << std::endl;

    std::ofstream outFile("decompressed_output.txt");
    if (!outFile) {
        std::cerr << "cant open for writing" << std::endl;
        return 1;
    }
    outFile << decodedStr;
    outFile.close();
    std::cout << "data has written to decompressed_output.txt" << std::endl;

    deleteTree(root);

    return 0;
}

