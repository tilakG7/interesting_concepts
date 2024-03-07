#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input_file("my_data.txt");
    std::ofstream output_file("my_result.txt");
    if(!input_file) {
        std::cerr << "Failed to open input file!" << std::endl;
    }
    if(!output_file) {
        std::cerr << "Failed to open output file!" << std::endl;
    }

    std::string line;
    while(getline(input_file, line)) {
        std::cout << line << std::endl;
        output_file << line << std::endl;
    }
    
}