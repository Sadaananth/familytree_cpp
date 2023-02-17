#pragma once

#include <string>

class Person
{
public:
    Person();
    ~Person() {}

private:
    uint32_t m_id;
    std::string m_name;
    std::string m_familyname;
    std::string m_villagename;
};
