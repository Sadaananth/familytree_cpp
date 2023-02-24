#pragma once

#include <vector>
#include "Person.hpp"

class Family
{
public:
    Family();
    ~Family() {}

    static void from_json(const nlohmann::json& j, Family& family);
private:
    std::vector<Person> m_persons_list;

    std::string m_family_name;

};
