#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "enums.hpp"

class token {
    public:
        token(const std::string& lexeme, token_type type);
        [[nodiscard]] auto get_type() const;
        [[nodiscard]] auto get_lexeme() const;
    private:
        std::string _lexeme;
        token_type _type;
};

auto operator<<(std::ostream& out, const token& t) -> std::ostream&;

class lexer{
    public:
        explicit lexer(const std::string& content);
        
        auto content_to_tokens() -> std::vector<token>;
    private:
        std::vector<std::pair<std::regex, token_type>> token_patterns;
        std::string content;

        void read_in_token_types();
};

#endif
