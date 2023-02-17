#pragma once

#include <vector>
#include "Person.hpp"

class Family
{
public:
    Family();
    ~Family() {}

    void generate(const std::string& filename);
private:
    std::vector<Person> person;
};
