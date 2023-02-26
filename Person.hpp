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

    void set_family_name(const std::string& family_name);

    const std::string& name() const;

    bool is_parent() const;

private:
    uint32_t m_id;
    std::string m_name;
    bool m_is_parent;
    std::string m_sex;
    std::string m_familyname;
    std::string m_villagename;
};
