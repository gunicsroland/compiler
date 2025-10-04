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

    auto runAllMacros(std::string& content) -> int;
    auto runSimpleMacros(std::string& content) -> int;
    auto runRegexMacros(std::string& content) -> int;

    private:
    std::string lex_struct_file = "lex_struct.txt";
    std::map<std::string, std::string> simple_macros;
    std::map<std::string, std::string> regex_macros;

    void readLexStruct();
};

#endif
