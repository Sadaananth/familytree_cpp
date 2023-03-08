#include "FamilyTree.hpp"
#include "utils/Utils.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

namespace {
    template<typename streamType>
    void fill_parent(const std::string& first, const std::string& helper, const std::string& second, streamType& stream) {
        stream << "\t\t\"" << first << "\" -- \"" << helper << "\" -- \"" << second << "\"" << std::endl;
        stream << "\t\t\"" << helper << "\" [shape=circle, label=\"\", style=invis, height=0.01, width=0.01]" << std::endl;
    }

    template<typename streamType>
    void fill_relation(const std::string& first, const std::string& second, streamType& stream) {
        stream << "\t\t\"" << first << "\" -- \"" << second << "\"" << std::endl;
    }

    template<typename streamType>
    void fill_children_helper(const std::string& first, const std::string& second, streamType& stream) {
        if(first.empty()) {
            stream << "\"" << second << "\"";
            return;
        }

        stream << " -- \"" << second << "\"";
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
    stream << "node [shape=box]\n" << std::endl;

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
                stream << "\t{" << std::endl;
                stream << "\t\trank=same;" << std::endl;
                //std::cout << "\t" << name << std::endl;

                person.value()->visited(true);

                std::string parent_helper = name + "_";

                if(person.value()->has_spouse()) {
                    for(auto spouse : person.value()->spouse_list()) {
                        //std::cout << "\t" << spouse << std::endl;
                        fill_parent(name, parent_helper, spouse, stream);
                    }
                }

                stream << "\t}" << std::endl;
                stream << "\t{" << std::endl;
                stream << "\t\trank=same;" << std::endl;

                std::stringstream children_stream;
                std::stringstream helper_stream;

                if(person.value()->has_children()) {
                    auto count = person.value()->children_list().size();
                    auto index = 0;
                    std::string joint_helper;
                    std::string prev_helper = "";
                    for(auto child : person.value()->children_list()) {
                        std::string child_helper = parent_helper + child + "_";
                        //std::cout << "\t" << child << std::endl;
                        //fill_relation(parent_helper, child, stream);
                        fill_children_helper(prev_helper, child_helper, helper_stream);
                        fill_relation(child_helper, child, children_stream);
                        stream << "\t\t\"" << child_helper << "\" [shape=circle, label=\"\", style=invis, height=0.01, width=0.01]" << std::endl;
                        if(index == (count/2)) {
                            joint_helper = child_helper;
                        }
                        ++index;
                        prev_helper = child_helper;
                    }

                    //children_stream << "\t{" << std::endl;
                    //children_stream << "\t\trank=same;" << std::endl;
                    fill_relation(parent_helper, joint_helper, children_stream);
                    //children_stream << "\t}" << std::endl;
                }

                stream << "\t\t" << helper_stream.str() << std::endl;
                stream << "\t}" << std::endl;
                stream << children_stream.str() << std::endl;
                stream << "\t}" << std::endl;

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
