#include "Family.hpp"

#include <fstream>
#include <iostream>

Family::Family()
{

}

void Family::generate(const std::string& filename)
{
    std::ifstream stream(filename);

    if (stream.is_open()) {
        std::string line;
        while (std::getline(stream, line)) {
            std::cout << line << std::endl;
        }
        stream.close();
    } else {
        std::cout << "File is not open" << std::endl;
    }
}
