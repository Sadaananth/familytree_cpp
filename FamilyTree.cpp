#include "FamilyTree.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <regex>

#include "inc/json.hpp"

FamilyTree::FamilyTree()
{

}

void FamilyTree::generate(const std::string& filename)
{
    std::ifstream stream(filename);

    if (stream.is_open()) {
        
        nlohmann::json input_json;
        stream >> input_json;
        stream.close();

        if(!input_json.contains("Families")) {
            return;
        }
        
        auto families_json = input_json["Families"];
        for(auto family : families_json) {
            Family family;
            Family::from_json(each, family);

            m_family_list.emplace_back(family);
        }

        for(auto& family : m_family_list) {
            
        }
    
    } else {
        std::cout << "File is not open" << std::endl;
    }
}
