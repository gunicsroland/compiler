#include <iostream>

#include "../include/input_handler.hpp"
#include "../include/lexer.hpp"
#include "../include/preprocessor.hpp"

auto main(int argc, char* argv[]) -> int {
    std::string input_file;
    std::string output_file;

    std::vector<std::string> args(argv, argv + argc);

    if (argc == 2) {
        input_file = args[1];
        output_file = "./o.txt";
    } else if (argc == 3) {
        input_file = args[1];
        output_file = args[2];
    } else {
        std::cout << "Wrong usage of mock compiler" << '\n';
        std::cout << "compiler input_file [output_file]" << '\n';
        return 1;
    }

    input_handler handler(input_file, output_file);
    preprocessor preprocessor;

    handler.open_file();
    std::string content = handler.get_file_content();
    preprocessor.run_all_macros(content);

    handler.set_file_content(content);
    handler.write_file();

    lexer lexer(content);
    std::vector<token> tokens = lexer.content_to_tokens();
    for (token const& t : tokens) {
        std::cout << t;
    }

    return 0;
}