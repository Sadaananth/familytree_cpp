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
        
        nlohmann::json input_json;
        stream >> input_json;

        if(input_json.contains("Families")) {
            
            auto person_list = input_json["Families"];
            for(auto each : person_list) {
                Person person;
                Person::from_json(each, person);
            }
        }
        stream.close();
    
    } else {
        std::cout << "File is not open" << std::endl;
    }
}
