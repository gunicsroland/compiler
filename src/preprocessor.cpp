#include "../include/preprocessor.hpp"
#include <regex>

preprocessor::preprocessor() {
    read_lex_struct();
}

// std::string slc_regex = R"(//[^\r\n]*)";
// std::string mlc_regex = R"(/\*[\s\S]*?\*/)";

auto preprocessor::run_all_macros(std::string& content) -> int {
    run_simple_macros(content);
    run_regex_macros(content);
    return 0;
}

auto preprocessor::run_simple_macros(std::string& content) -> int {
    size_t pos = 0;
    for (auto const& [key, value] : simple_macros) {
        while ((pos = content.find(key, pos)) != std::string::npos) {
            content.replace(pos, key.length(), value);
        }
    }
    return 0;
}

auto preprocessor::run_regex_macros(std::string& content) -> int {
    for (auto const& [key, value] : regex_macros) {
        std::regex const rgx(key);
        content = std::regex_replace(content, rgx, value);
    }
    return 0;
}

void preprocessor::read_lex_struct() {
    std::ifstream stream_in(lex_struct_file);
    std::string line;
    bool in_regex_section = false;

    while (std::getline(stream_in, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        if (line == "[SIMPLE_MACROS]") {
            in_regex_section = false;
            continue;
        }
        if (line == "[REGEX_MACROS]") {
            in_regex_section = true;
            continue;
        }

        size_t const delimiter_pos = line.find('=');
        if (delimiter_pos != std::string::npos) {
            std::string const key = line.substr(0, delimiter_pos);
            std::string const value = line.substr(delimiter_pos + 1);
            (in_regex_section ? regex_macros[key] : simple_macros[key]) = value;
        }
    }
}