#include <iostream>
#include <regex>
#include <vector>

#include "../include/lexer.hpp"

inline auto token_type_to_string(token_type t) {
    switch (t) {
    case token_type::IF:
        return "IF";
    case token_type::ELSE:
        return "ELSE";
    case token_type::WHILE:
        return "WHILE";
    case token_type::FOR:
        return "FOR";
    case token_type::RETURN:
        return "RETURN";
    case token_type::FUNCTION:
        return "FUNCTION";
    case token_type::VAR:
        return "VAR";
    case token_type::LET:
        return "LET";
    case token_type::CONST:
        return "CONST";
    case token_type::TRUE_:
        return "TRUE";
    case token_type::FALSE_:
        return "FALSE";
    case token_type::NULL_:
        return "NULL";
    case token_type::FLOAT_LITERAL:
        return "FLOAT_LITERAL";
    case token_type::NUMBER:
        return "NUMBER";
    case token_type::PLUS:
        return "PLUS";
    case token_type::MINUS:
        return "MINUS";
    case token_type::MULTIPLY:
        return "MULTIPLY";
    case token_type::DIVIDE:
        return "DIVIDE";
    case token_type::LPAREN:
        return "LPAREN";
    case token_type::RPAREN:
        return "RPAREN";
    case token_type::SEMICOLON:
        return "SEMICOLON";
    case token_type::EQUALS:
        return "EQUALS";
    case token_type::NOT_EQUALS:
        return "NOT_EQUALS";
    case token_type::LESS_THAN_OR_EQUAL:
        return "LESS_THAN_OR_EQUAL";
    case token_type::GREATER_THAN_OR_EQUAL:
        return "GREATER_THAN_OR_EQUAL";
    case token_type::LESS_THAN:
        return "LESS_THAN";
    case token_type::GREATER_THAN:
        return "GREATER_THAN";
    case token_type::ASSIGN:
        return "ASSIGN";
    case token_type::LBRACE:
        return "LBRACE";
    case token_type::RBRACE:
        return "RBRACE";
    case token_type::COMMA:
        return "COMMA";
    case token_type::IDENTIFIER:
        return "IDENTIFIER";
    case token_type::STRING_LITERAL:
        return "STRING_LITERAL";
    case token_type::CHARACTER_LITERAL:
        return "CHARACTER_LITERAL";
    default:
        return "UNKNOWN";
    }
}

token::token(std::string const& lexeme, token_type type)
    : _lexeme(lexeme), _type(type) {}

auto token::get_lexeme() const {
    return _lexeme;
}
auto token::get_type() const {
    return _type;
}
auto operator<<(std::ostream& out, token const& t) -> std::ostream& {
    out << "<" << token_type_to_string(t.get_type()) << ":" << t.get_lexeme()
        << ">\n";
    return out;
}

lexer::lexer(std::string const& new_content) : content(new_content) {
    read_in_token_types();
}

void lexer::read_in_token_types() {
    token_patterns = {
        {std::regex(R"(IF)"), token_type::IF},
        {std::regex(R"(ELSE)"), token_type::ELSE},
        {std::regex(R"(WHILE)"), token_type::WHILE},
        {std::regex(R"(FOR)"), token_type::FOR},
        {std::regex(R"(RETURN)"), token_type::RETURN},
        {std::regex(R"(FUNCTION)"), token_type::FUNCTION},
        {std::regex(R"(VAR)"), token_type::VAR},
        {std::regex(R"(LET)"), token_type::LET},
        {std::regex(R"(CONST)"), token_type::CONST},
        {std::regex(R"(TRUE)"), token_type::TRUE_},
        {std::regex(R"(FALSE)"), token_type::FALSE_},
        {std::regex(R"(NULL)"), token_type::NULL_},
        {std::regex(R"(\d+\.\d+)"), token_type::FLOAT_LITERAL},
        {std::regex(R"(\d+)"), token_type::NUMBER},
        {std::regex(R"(\+)"), token_type::PLUS},
        {std::regex(R"(\-)"), token_type::MINUS},
        {std::regex(R"(\*)"), token_type::MULTIPLY},
        {std::regex(R"(/)"), token_type::DIVIDE},
        {std::regex(R"(\()"), token_type::LPAREN},
        {std::regex(R"(\))"), token_type::RPAREN},
        {std::regex(R"(;)"), token_type::SEMICOLON},
        {std::regex(R"(==)"), token_type::EQUALS},
        {std::regex(R"(!=)"), token_type::NOT_EQUALS},
        {std::regex(R"(<=)"), token_type::LESS_THAN_OR_EQUAL},
        {std::regex(R"(>=)"), token_type::GREATER_THAN_OR_EQUAL},
        {std::regex(R"(<)"), token_type::LESS_THAN},
        {std::regex(R"(>)"), token_type::GREATER_THAN},
        {std::regex(R"(=)"), token_type::ASSIGN},
        {std::regex(R"(\{)"), token_type::LBRACE},
        {std::regex(R"(\})"), token_type::RBRACE},
        {std::regex(R"(,)"), token_type::COMMA},
        {std::regex(R"([a-z_][a-z0-9_]*)", std::regex_constants::icase),
         token_type::IDENTIFIER},
        {std::regex(R"("(?:[^"\\]|\\.)*")"), token_type::STRING_LITERAL},
        {std::regex(R"('(?:[^'\\]|\\.)*')"), token_type::CHARACTER_LITERAL}};
}

auto lexer::content_to_tokens() -> std::vector<token> {
    std::vector<token> tokens_list;
    std::smatch match;
    size_t i = 0;

    while (i < content.size()) {
        // Skip whitespace
        if (std::isspace(static_cast<unsigned char>(content[i])) != 0) {
            ++i;
            continue;
        }

        bool matched = false;

        for (auto const& [pattern, type] : token_patterns) {
            std::string remaining = content.substr(i);

            if (std::regex_search(remaining, match, pattern,
                                  std::regex_constants::match_continuous)) {
                std::string lexeme = match.str();
                tokens_list.emplace_back(lexeme, type);

                i += lexeme.size();
                matched = true;
                break;
            }
        }

        if (!matched) {
            std::cerr << "Unexpected character: " << content[i]
                      << " at position " << i << "\n";
            ++i; // skip unknown character
        }
    }

    return tokens_list;
}