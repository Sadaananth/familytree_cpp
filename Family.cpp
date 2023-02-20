#include "Family.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <regex>

#include "inc/json.hpp"

Family::Family()
{

}

void Family::generate(const std::string& filename)
{
    std::ifstream stream(filename);

    if (stream.is_open()) {
        std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        auto itr = nlohmann::json::parse(str);
        stream.close();
    } else {
        std::cout << "File is not open" << std::endl;
    }
}
