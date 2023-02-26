#pragma once

#include <vector>
#include "Person.hpp"

class Family
{
public:
    Family();
    ~Family() {}

    static void from_json(const nlohmann::json& j, Family& family);

    void get_stream(std::stringstream& stream);
private:
    std::vector<Person> m_parent_list;
    std::vector<Person> m_children_list;

    std::string m_family_name;

};
