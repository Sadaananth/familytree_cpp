#include "Family.hpp"
#include "Utils.hpp"
#include <iostream>

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
    for(auto parent : m_parent_list) {

    }

    for(auto parent : m_parent_list) {
        for(auto children : m_children_list) {
            stream << "\"" << parent.name() << "\" -- \"" << children.name() << "\"\n";
        }
    }
}
