#include "FamilyTree.hpp"
#include "Utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <regex>

#include "inc/json.hpp"

namespace {
    template<typename streamType>
    void fill_relation(const std::string& first, const std::string& second, streamType& stream) {
        stream << "\t\"" << first << "\" -- \"" << second << "\"" << std::endl;
    }
}

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

    stream << "graph myfamily {" << std::endl;

    if(m_persons_map.size() > 0) {
        auto itr = m_persons_map.begin();
        //auto root_name = find_root(itr->second->name());
        draw_family(itr->second->name(), stream);
    }

    stream << "}" << std::endl;

    stream.close();
}

std::string FamilyTree::find_root(const std::string& name)
{
    auto person = utils::getFromMapOrOptional(m_persons_map, name);
    if(person.has_value() && !person.value()->is_visited()) {
        person.value()->visited(true);
        if(person.value()->has_parents()) {
            for(auto parent : person.value()->parent_list()) {
                return find_root(parent);
            }
        }

        if(person.value()->has_spouse()) {
            for(auto spouse : person.value()->spouse_list()) {
                return find_root(spouse);
            }
        }
    } else {
        return name;
    }

    return "";
}

bool FamilyTree::is_any_spouse_visited(const std::shared_ptr<Person>& person)
{
    if(person->has_spouse()) {
        for(auto spouse : person->spouse_list()) {
            auto spouse_itr = utils::getFromMapOrOptional(m_persons_map, spouse);
            if(spouse_itr.has_value() && spouse_itr.value()->is_visited()) {
                //std::cout << spouse << " visited for " << person->name() << std::endl;
                return true;
            }
        }
    }

    return false;
}

void FamilyTree::draw_family(const std::string& name, std::ofstream& stream)
{
    //std::cout << "Entering for " << name << std::endl;
    auto person = utils::getFromMapOrOptional(m_persons_map, name);
    if(person.has_value()) {

        if(!person.value()->is_visited()) {

            if(person.value()->has_spouse() && !is_any_spouse_visited(person.value())) {
                stream << "{" << std::endl;
                //std::cout << "\t" << name << std::endl;

                person.value()->visited(true);

                if(person.value()->has_spouse()) {
                    for(auto spouse : person.value()->spouse_list()) {
                        //std::cout << "\t" << spouse << std::endl;
                        fill_relation(name, spouse, stream);
                    }
                }

                if(person.value()->has_children()) {
                    for(auto child : person.value()->children_list()) {
                        //std::cout << "\t" << child << std::endl;
                        fill_relation(name, child, stream);
                    }
                }

                stream << "}" << std::endl;

                if(person.value()->has_spouse()) {
                    for(auto spouse : person.value()->spouse_list()) {
                        //std::cout << "Searching " << spouse << " from " << name << std::endl;
                        draw_family(spouse, stream);
                    }
                }

                if(person.value()->has_children()) {
                    for(auto child : person.value()->children_list()) {
                        //std::cout << "Searching " << child << " from " << name << std::endl;
                        draw_family(child, stream);
                    }
                }
            }

            if(person.value()->has_parents()) {
                for(auto parent : person.value()->parent_list()) {
                    //std::cout << "Searching " << parent << " from " << name << std::endl;
                    draw_family(parent, stream);
                }
            }

        } else {
            //std::cout << "Skipping person " << name << std::endl;
        }
    }
}
