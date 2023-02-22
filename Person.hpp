#pragma once

#include "json.hpp"

#include <string>

class Person
{
public:
    Person() {}
    Person(const std::string& line);
    ~Person() {}


    static void to_json(nlohmann::json& j, const Person& p);
    static void from_json(const nlohmann::json& j, Person& p);

private:
    void parse_and_fill(const std::string& line);

    uint32_t m_id;
    std::string m_name;
    std::string m_familyname;
    std::string m_villagename;
};
