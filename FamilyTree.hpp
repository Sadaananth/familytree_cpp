#pragma once

#include <map>
#include <memory>
#include "Family.hpp"
#include "Person.hpp"

class FamilyTree
{
public:
    FamilyTree();
    ~FamilyTree() {}

    void generate(const std::string& filename);

    void display();
private:

    std::map<std::string, std::shared_ptr<Person>> m_persons_map;
};
