#include "FamilyTree.hpp"
#include "utils/Utils.hpp"

#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "Logger.hpp"

using namespace Sada;

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
        LOG_ERROR << filename << " file is not open";
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
                LOG_DEBUG << spouse << " visited for " << person->name();
                return true;
            }
        }
    }

    return false;
}

void FamilyTree::draw_family(const std::string& name, std::ofstream& stream)
{
    LOG_DEBUG << "Entering for " << name;
    auto person = utils::getFromMapOrOptional(m_persons_map, name);
    if(person.has_value()) {

        if(!person.value()->is_visited()) {

            if(person.value()->has_spouse() && !is_any_spouse_visited(person.value())) {
                stream << "{" << std::endl;
                stream << "\t{" << std::endl;
                stream << "\t\trank=same;" << std::endl;
                LOG_DEBUG << "\t" << name;

                person.value()->visited(true);

                std::string parent_helper = name + "_";

                if(person.value()->has_spouse()) {
                    for(auto spouse : person.value()->spouse_list()) {
                        LOG_DEBUG << "\t" << spouse;
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
                        LOG_DEBUG << "\t" << child;
                        fill_children_helper(prev_helper, child_helper, helper_stream);
                        fill_relation(child_helper, child, children_stream);
                        stream << "\t\t\"" << child_helper << "\" [shape=circle, label=\"\", style=invis, height=0.01, width=0.01]" << std::endl;
                        if(index == (count/2)) {
                            joint_helper = child_helper;
                        }
                        ++index;
                        prev_helper = child_helper;
                    }

                    fill_relation(parent_helper, joint_helper, children_stream);
                }

                stream << "\t\t" << helper_stream.str() << std::endl;
                stream << "\t}" << std::endl;
                stream << children_stream.str() << std::endl;
                stream << "\t}" << std::endl;

                if(person.value()->has_spouse()) {
                    for(auto spouse : person.value()->spouse_list()) {
                        LOG_DEBUG << "Searching " << spouse << " from " << name;
                        draw_family(spouse, stream);
                    }
                }

                if(person.value()->has_children()) {
                    for(auto child : person.value()->children_list()) {
                        LOG_DEBUG << "Searching " << child << " from " << name;
                        draw_family(child, stream);
                    }
                }
            }

            if(person.value()->has_parents()) {
                for(auto parent : person.value()->parent_list()) {
                    LOG_DEBUG << "Searching " << parent << " from " << name;
                    draw_family(parent, stream);
                }
            }

        } else {
            LOG_DEBUG << "Skipping person " << name;
        }
    }
}
