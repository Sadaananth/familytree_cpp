#include "Person.hpp"
#include "Utils.hpp"

#include <iostream>

Person::Person(const std::string& line)
{

}

void Person::to_json(nlohmann::json& json, const Person& person)
{
    json["id"] = person.m_id;
    json["name"] = person.m_name;
    json["sex"] = person.m_sex;
    json["parent"] = person.m_is_parent;
    json["villagename"] = person.m_villagename;
    json["familyname"] = person.m_familyname;
}

void Person::from_json(const nlohmann::json& json, Person& person)
{
    utils::fillFromJson(json, "id", person.m_id);
    utils::fillFromJson(json, "name", person.m_name);
    utils::fillFromJson(json, "sex", person.m_sex);
    utils::fillFromJson(json, "parent", person.m_is_parent);
    utils::fillFromJson(json, "villagename", person.m_villagename);
    utils::fillFromJson(json, "bornfamily", person.m_familyname);
}

void Person::set_family_name(const std::string& family_name)
{
    m_familyname = family_name;
}
