#include "Node.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

std::vector<bool> code;
std::map<char, std::vector<bool> > table;

// Функция для освобождения памяти дерева
void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    // Исходная строка для построения кодовой таблицы
    std::string str = "it is my striiiiing!!!!";

    // Построение частотной таблицы
    std::map<char, int> map;
    frequency(map, str);

    // Создание списка узлов
    std::list<Node*> list;
    build_map(list, map);

    // Создание дерева Хаффмана
    Node* root = create_tree(list);

    // Построение кодовой таблицы
    build_table(root, code, table);

    // Кодирование исходной строки и запись в файл
    std::vector<bool> encodedBits;

   
    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        std::vector<bool> v = table[c];
        encodedBits.insert(encodedBits.end(), v.begin(), v.end());
    }


    std::ofstream outfile("encoded.txt", std::ios::binary);
    if (!outfile) {
        std::cerr << "can't open encoded.txt for writing" << std::endl;
        return 1;
    }
    char byte = 0;
    int count = 0;

    for (size_t i = 0; i < encodedBits.size(); ++i) {
        byte = byte | (encodedBits[i] << (7 - count));
        ++count;
        if (count == 8) {
            outfile.write(&byte, 1);
            count = 0;
            byte = 0;
        }
    }
    if (count != 0) { 
        outfile.write(&byte, 1);
    }
    outfile.close();

 
    std::vector<bool> encodedBitsFromFile;

    std::ifstream infile("encoded.txt", std::ios::binary);
    if (!infile) {
        std::cerr << "cant open encoded.txt for reading" << std::endl;
        return 1;
    }

    char readByte;
    while (infile.read(&readByte, 1)) {
        for (int i = 7; i >= 0; --i) {
            bool bit = (readByte >> i) & 1;
            encodedBitsFromFile.push_back(bit);
        }
    }
    infile.close();

    std::string decodedStr = decode_sequence(root, encodedBitsFromFile);
    std::cout << "Decoded: " << decodedStr << std::endl;

 
    deleteTree(root);

    return 0;
}
