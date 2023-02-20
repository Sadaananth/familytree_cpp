#pragma once

#include <string>

class Person
{
public:
    Person(const std::string& line);
    ~Person() {}

private:
    void parse_and_fill(const std::string& line);

    uint32_t m_id;
    std::string m_name;
    std::string m_familyname;
    std::string m_villagename;
};
