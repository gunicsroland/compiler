#ifndef LEXER_HPP
#define LEXER_HPP

#include <map>
#include <string>
#include <vector>

class lexer{
    public:
        explicit lexer(const std::string& content);

    private:
        
        std::string content;
        std::vector<std::string> symbol_table;
        int symbol_table_index;
        std::map<std::string, std::string> replaces;

        auto create_symbol_table_index(const std::string& symbol) -> std::string;
        void main_replace();
        void replace_keyword();
        void read_in_replaces();
};

#endif
