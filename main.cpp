#include "FamilyTree.hpp"

#include <iostream>

int main()
{
    FamilyTree family_tree;
    family_tree.generate("../myfamily.json");
    family_tree.display();
    return 0;
}
