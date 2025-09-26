#include "../include/InputHandler.hpp"

int main() {
    auto* handler = new InputHandler("input.txt", "output.txt");

    handler->openFile();
    handler->replaceContent();
    handler->writeFile();
    return 0;
}