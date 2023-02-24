#pragma once

#include <vector>
#include "Family.hpp"

class FamilyTree
{
public:
    FamilyTree();
    ~FamilyTree() {}

    void generate(const std::string& filename);
private:
    std::vector<Family> m_family_list;
};
