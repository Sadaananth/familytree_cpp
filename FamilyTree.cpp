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

void FamilyTree::read(const std::string& filename)
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
        for(auto family_json : families_json) {
            Family family;
            family.from_json(family_json, m_persons_map);
        }

    } else {
        std::cout << "File is not open" << std::endl;
    }
}

void FamilyTree::display()
{
    for(auto [person_name, person] : m_persons_map) {
        person->display();
    }
}

void FamilyTree::output_file(const std::string& filename)
{
    m_output_file = filename;
}

void FamilyTree::generate()
{
    if(m_output_file.empty()) {
        throw std::runtime_error("Output File is empty");
    }

    std::ofstream stream(m_output_file);
    if(!stream.is_open()) {
        throw std::runtime_error("Unable to open File " + m_output_file);
    }

    stream << "{" << std::endl;

    stream << "graph myfamily {" << std::endl;

    stream << "}" << std::endl;

    stream << "}" << std::endl;

    stream.close();
}
