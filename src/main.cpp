#include "core/FamilyTree.hpp"

#include <iostream>

int main(int argc, char**argv)
{
    std::string input_dir = "../";
    std::string input_file = "Sample.json";
    std::string output_file = "output.dot";

    for(auto index = 1; index < argc; index++) {
        if(strcmp(argv[index], "-i") == 0) {
            input_file = argv[index + 1];
            index++;
        } else if(strcmp(argv[index], "-o") == 0) {
            output_file = argv[index + 1];
            index++;
        }
    }

    std::cout << "Input File: " << input_file << std::endl;
    std::cout << "Output File: " << output_file << std::endl;

    FamilyTree family_tree;
    family_tree.read(input_dir + input_file);
    family_tree.output_file(output_file);
    //family_tree.display();
    family_tree.generate();
    return 0;
}
