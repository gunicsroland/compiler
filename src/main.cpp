#include "../include/inputHandler.hpp"

auto main() -> int {
    auto* handler = new InputHandler("input.txt", "output.txt");

    handler->openFile();
    handler->replaceContent();
    handler->writeFile();
    return 0;
}