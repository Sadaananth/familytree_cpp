#include "FamilyTree.hpp"

#include <iostream>

int main()
{
    FamilyTree family_tree;
    family_tree.read("../myfamily.json");
    family_tree.output_file("output.dot");
    //family_tree.display();
    family_tree.generate();
    return 0;
}
