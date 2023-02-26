#include "Family.hpp"
#include "Utils.hpp"
#include <iostream>

namespace {
    std::string get_helper(const std::string& name) {
        return std::string("\"") + name + std::string("\"") + std::string(" [ style=invis ]\n");
    }
}

Family::Family()
{

}

void Family::from_json(const nlohmann::json& json, Family& family)
{
    utils::fillFromJson(json, "name", family.m_family_name);

    if(json.contains("members")) {
        for(auto member : json["members"]) {
            Person person;
            person.set_family_name(family.m_family_name);
            Person::from_json(member, person);

            if(person.is_parent()) {
                family.m_parent_list.emplace_back(person);
            } else {
                family.m_children_list.emplace_back(person);
            }

            nlohmann::json person_json;
            Person::to_json(person_json, person);
            std::cout << person_json.dump(4) << std::endl;
        }
    }
}

void Family::get_stream(std::stringstream& stream)
{
    auto helper_node = "helper";
    stream << "{\nrank = same\n";
    stream << get_helper(helper_node);
    for(auto parent: m_parent_list) {
        stream << "\"" << parent.name() << "\" -- \"" << helper_node << "\"\n";
    }
    stream << "}\n";

    auto helper_node2 = "helper2";
    stream << "{\n\"" << helper_node2 << "\" [ style=invis] \n";
    stream << "\"" << helper_node << "\" -- \"" << helper_node2 << "\"}\n";

    stream << "{\n";
    for(auto children : m_children_list) {
        stream << "\"" << helper_node2 << "\" -- \"" << children.name() << "\"\n";
    }
    stream << "}\n";
}
