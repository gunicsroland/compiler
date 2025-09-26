#include "inputHandler.hpp"

int main() {
    InputHandler* handler = new InputHandler("input.txt", "output.txt");

    handler->openFile();
    handler->replaceContent();
    handler->writeFile();
    return 0;
}