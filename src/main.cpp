#include "../include/inputHandler.hpp"
#include "../include/preprocessor.hpp"

auto main() -> int {
    InputHandler handler("./bin/input.txt", "./bin/output.txt");
    Preprocessor preprocessor;

    handler.openFile();
    std::string content = handler.get_file_content();
    preprocessor.runAllMacros(content);
    handler.set_file_content(content);
    handler.writeFile();
    return 0;
}