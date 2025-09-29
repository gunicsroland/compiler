#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "inputHandler.hpp"

class Preprocessor {
    public:
    Preprocessor();
    ~Preprocessor() = default;

    int replaceContent(std::string& content);

    private:
    const std::string lex_struct_file = "lex_struct.txt";
    std::map<std::string, std::string> macros;

    void readLexStruct();
};

#endif
