#include "Person.hpp"
#include "Utils.hpp"

#include <iostream>

namespace {
    template<typename titleType, typename dataType>
    void displayValues(const titleType& title, const dataType& data, uint32_t level)
    {
        for(auto i = 0; i < level; i++) {
            std::cout << "\t";
        }

        std::cout << title << ": " << data << std::endl;
    }
}

Person::Person(const std::string& line)
{

}

void Person::to_json(nlohmann::json& json)
{
    json["id"] = m_id;
    json["name"] = m_name;
    json["sex"] = m_sex;
    json["villagename"] = m_villagename;
    json["familyname"] = m_familyname;
}

void Person::from_json(const nlohmann::json& json)
{
    utils::fillFromJson(json, "id", m_id);
    utils::fillFromJson(json, "name", m_name);
    utils::fillFromJson(json, "sex", m_sex);
    utils::fillFromJson(json, "villagename", m_villagename);
    utils::fillFromJson(json, "bornfamily", m_familyname);
}

void Person::update_person(std::shared_ptr<Person>& person)
{
    utils::updateOnDiff(m_name, person->m_name);
    utils::updateOnDiff(m_familyname, person->m_familyname);
    utils::updateOnDiff(m_id, person->m_id);
    utils::updateOnDiff(m_sex, person->m_sex);
    utils::updateOnDiff(m_villagename, person->m_villagename);

    if(m_parents_list.size() != person->m_parents_list.size()) {
        for(auto parent : m_parents_list) {
            if(std::find(person->m_parents_list.begin(), person->m_parents_list.end(), parent) == person->m_parents_list.end()) {
                person->m_parents_list.emplace_back(parent);
            }
        }
    }

    if(m_children_list.size() != person->m_children_list.size()) {
        for(auto child : m_children_list) {
            if(std::find(person->m_children_list.begin(), person->m_children_list.end(), child) == person->m_children_list.end()) {
                person->m_children_list.emplace_back(child);
            }
        }
    }

    if(m_spouse_list.size() != person->m_spouse_list.size()) {
        for(auto spouse : m_spouse_list) {
            if(std::find(person->m_spouse_list.begin(), person->m_spouse_list.end(), spouse) == person->m_spouse_list.end()) {
                person->m_spouse_list.emplace_back(spouse);
            }
        }
    }
}

void Person::update_parent(const std::string& parent)
{
    m_parents_list.emplace_back(parent);
}

void Person::update_child(const std::string& child)
{
    m_children_list.emplace_back(child);
}

void Person::update_spouse(const std::string& spouse)
{
    m_spouse_list.emplace_back(spouse);
}

void Person::set_family_name(const std::string& family_name)
{
    m_familyname = family_name;
}

const std::string& Person::name() const
{
    return m_name;
}

void Person::display() const
{
    displayValues("name", m_name, 0);
    displayValues("id", m_id, 1);
    displayValues("family_name", m_familyname, 1);
    displayValues("village name", m_villagename, 1);
    
    displayValues("Parents", "", 1);
    for(auto parent : m_parents_list) {
        displayValues("", parent, 2);
    }

    displayValues("Children", "", 1);
    for(auto child : m_children_list) {
        displayValues("", child, 2);
    }

    displayValues("Spouses", "", 1);
    for(auto spouse : m_spouse_list) {
        displayValues("", spouse, 2);
    }
}

bool Person::has_parents() const
{
    return m_parents_list.size() > 0;
}

bool Person::has_spouse() const
{
    return m_spouse_list.size() > 0;
}

std::vector<std::string> Person::parent_list() const
{
    return m_parents_list;
}

std::vector<std::string> Person::spouse_list() const
{
    return m_spouse_list;
}
