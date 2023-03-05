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

    void read(const std::string& filename);

    void display();

    void output_file(const std::string& filename);
    void generate();
private:
    std::string find_root(const std::string& name);

    std::map<std::string, std::shared_ptr<Person>> m_persons_map;

    std::string m_output_file;
};
