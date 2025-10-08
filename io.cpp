#include <iostream>
#include <fstream>
#include <stdlib.h>

int main() {

    using namespace std;
    
    std::string input_file = "./input.txt";
    std::string output_file = "./output.txt";

    std::ifstream readFile(input_file);
    std::string input = "";
    
    if (readFile.is_open()) {
        std::string line;
        while (getline(readFile, line)) {
            input = line;        
        }
    }

    std::cout << input << std::endl;
    return 0;
}