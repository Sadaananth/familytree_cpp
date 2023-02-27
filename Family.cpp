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

void Family::from_json(const nlohmann::json& json, std::map<std::string, std::shared_ptr<Person>>& persons_map)
{
    std::string family_name;
    utils::fillFromJson(json, "name", family_name);

    if(json.contains("members")) {
        
        std::vector<std::string> parents_list;
        std::vector<std::string> children_list;
        
        for(auto member : json["members"]) {

            std::shared_ptr<Person> person = std::make_shared<Person>();
            person->set_family_name(family_name);
            person->from_json(member);

            if(person->is_parent()) {
                parents_list.emplace_back(person->name());
            } else {
                children_list.emplace_back(person->name());
            }

            if(auto person_old = utils::getFromMapOrOptional(persons_map, person->name()); person_old.has_value()) {
                person_old.value()->update_person(person);
                persons_map.erase(person->name());
            }
            persons_map[person->name()] = person;

        }

        for(auto parent : parents_list) {
            if(auto parent_itr = utils::getFromMapOrOptional(persons_map, parent); parent_itr.has_value()) {
                for(auto child : children_list) {
                    parent_itr.value()->update_child(child);
                }
            }
        }

        for(auto child : children_list) {
            if(auto child_itr = utils::getFromMapOrOptional(persons_map, child); child_itr.has_value()) {
                for(auto parent : parents_list) {
                    child_itr.value()->update_parent(parent);
                }
            }
        }
    }
}
