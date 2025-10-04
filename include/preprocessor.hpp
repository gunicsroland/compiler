#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "inputHandler.hpp"

class Preprocessor {
  public:
    Preprocessor();
    ~Preprocessor() = default;

    auto runAllMacros(std::string& content) -> int;
    auto runSimpleMacros(std::string& content) -> int;
    auto runRegexMacros(std::string& content) -> int;

  private:
    std::string lex_struct_file = "./bin/lex_struct.txt";
    std::map<std::string, std::string> simple_macros;
    std::map<std::string, std::string> regex_macros;

    void readLexStruct();
};

#endif
