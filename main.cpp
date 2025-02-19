#include "Node.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>
std::vector<bool> code;
std::map<char, std::vector<bool>> table;

void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    std::string str = "it is my striiiiing!!!!";

    std::map<char, int> map;
    frequency(map, str);

    std::list<Node*> list;
    build_map(list, map);

    Node* root = create_tree(list);

    build_table(root, code, table);

    std::vector<bool> encodedBits;

    for (size_t i = 0; i < str.length(); i++) {
        char c = str[i];
        std::vector<bool> v = table[c];
        encodedBits.insert(encodedBits.end(), v.begin(), v.end());
    }

    // Запись количества закодированных битов в файл
    size_t numBits = encodedBits.size();
    std::ofstream outfile("encoded.bin", std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(&numBits), sizeof(numBits));

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

    // Считывание количества закодированных битов из файла
    size_t numBitsFromFile = 0;
    std::ifstream infile("encoded.bin", std::ios::binary);
    infile.read(reinterpret_cast<char*>(&numBitsFromFile), sizeof(numBitsFromFile));

    char readByte;
    while (infile.read(&readByte, 1) && encodedBitsFromFile.size() < numBitsFromFile) {
        for (int i = 7; i >= 0; --i) {
            bool bit = (readByte >> i) & 1;
            encodedBitsFromFile.push_back(bit);
        }
    }
    infile.close();

    // Ограничить количество бит, обрабатываемых для декодирования
    encodedBitsFromFile.resize(numBitsFromFile);

    std::string decodedStr = decode_sequence(root, encodedBitsFromFile);
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