#include "core/FamilyTree.hpp"

#include "Logger.hpp"

using namespace Sada;

int main(int argc, char**argv)
{
    std::string input_file = "Sample.json";
    std::string output_file = "output.dot";

    Logger::instance().add_sink(Logger::Sink::file, LogLevel::Info, "familytree.log");
    Logger::instance().add_sink(Logger::Sink::console, LogLevel::Info);

    for(auto index = 1; index < argc; index++) {
        if(strcmp(argv[index], "-i") == 0) {
            input_file = argv[index + 1];
            index++;
        } else if(strcmp(argv[index], "-o") == 0) {
            output_file = argv[index + 1];
            index++;
        }
    }

    LOG_INFO << "Input File: " << input_file;
    LOG_INFO << "Output File: " << output_file;

    FamilyTree family_tree;
    family_tree.read(input_file);
    family_tree.output_file(output_file);
    //family_tree.display();
    family_tree.generate();
    return 0;
}
