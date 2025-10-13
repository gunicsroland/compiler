#include "../include/input_handler.hpp"
#include "../include/preprocessor.hpp"

auto main() -> int {
    input_handler handler("./bin/input.txt", "./bin/output.txt");
    preprocessor preprocessor;

    handler.open_file();
    std::string content = handler.get_file_content();
    preprocessor.run_all_macros(content);
    handler.set_file_content(content);
    handler.write_file();
    return 0;
}