#include "Person.hpp"

Person::Person(const std::string& line)
{

}

void Person::parse_and_fill(const std::string& line)
{
    m_id = 0;
    m_name = line;
}
