#include "Person.hpp"

#include <iostream>

namespace {
    template<typename fieldType>
    void fillFromJson(nlohmann::json json, const std::string& key, fieldType& field)
    {
        if(json.contains(key)) {
            json.at(key).get_to<fieldType>(field);
        }
    }
}

Person::Person(const std::string& line)
{

}

void Person::parse_and_fill(const std::string& line)
{
    m_id = 0;
    m_name = line;
}

void Person::to_json(nlohmann::json& j, const Person& p)
{

}

void Person::from_json(const nlohmann::json& json, Person& person)
{
    fillFromJson(json, "id", person.m_id);
    fillFromJson(json, "name", person.m_name);
    fillFromJson(json, "familyname", person.m_familyname);
    fillFromJson(json, "villagename", person.m_villagename);

    std::cout << person.m_name << std::endl;
}
