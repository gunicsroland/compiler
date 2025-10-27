#include "../include/input_handler.hpp"
#include "../include/preprocessor.hpp"
#include <iostream>

auto main(int argc, char *argv[]) -> int {
    std::string input_file;
    std::string output_file;

    if(argc == 2){
        input_file = std::string(argv[1]);
        output_file = "./o.txt";
    }
    if(argc == 3){
        input_file = std::string(argv[1]);
        output_file = std::string(argv[2]);
    }
    else{
        std::cout << "Wrong usage of mock compiler" << '\n';
        std::cout << "compiler input_file [output_file]" << '\n';
    }

    input_handler handler(input_file, output_file);
    preprocessor preprocessor;

    handler.open_file();
    std::string content = handler.get_file_content();
    preprocessor.run_all_macros(content);
    handler.set_file_content(content);
    handler.write_file();
    return 0;
}