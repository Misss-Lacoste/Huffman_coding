
int main() {

    std::map<char, int> map;
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        map[c]++;
    }

    std::map<char, int>::iterator i;
    for (i = map.begin(); i != map.end(); i++) {
        std::cout << i->first << ":" << i->second << std::endl;
    }
    return 0;
}