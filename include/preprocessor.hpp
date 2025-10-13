#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>

class preprocessor {
  public:
    preprocessor();

    auto run_all_macros(std::string& content) -> int;
    auto run_simple_macros(std::string& content) -> int;
    auto run_regex_macros(std::string& content) -> int;

  private:
    std::string lex_struct_file = "./bin/lex_struct.txt";
    std::map<std::string, std::string> simple_macros;
    std::map<std::string, std::string> regex_macros;

    void read_lex_struct();
};

#endif
