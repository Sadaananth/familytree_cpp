#include "Family.hpp"

#include <fstream>
#include <iostream>
#include <regex>

Family::Family()
{

}

void Family::generate(const std::string& filename)
{
    std::ifstream stream(filename);

    if (stream.is_open()) {
        std::string line;
        while (std::getline(stream, line)) {
            if(line[0] == '#') {
                continue;
            } else if(line[0] == 't' || line[0] == ' ') {
                line = std::regex_replace(line, std::regex("^ +"), "");
                std::cout << "Found children " << line << std::endl;
            } else {
                line = std::regex_replace(line, std::regex("^ +"), "");
                line = std::regex_replace(line, std::regex("^\n"), "");
                if(line[0] == EOF) {
                    std::cout << "End of file" << std::endl;
                } else if(line.size() > 0) {
                    std::cout << "Parent " << line << std::endl;
                }
            }
        }
        stream.close();
    } else {
        std::cout << "File is not open" << std::endl;
    }
}
