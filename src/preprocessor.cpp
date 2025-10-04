#include "../include/preprocessor.hpp"
#include <regex>
#include <stdbool.h>

Preprocessor::Preprocessor() {
    readLexStruct();
}

//std::string slc_regex = R"(//[^\r\n]*)";
    //std::string mlc_regex = R"(/\*[\s\S]*?\*/)";

auto Preprocessor::runAllMacros(std::string& content) -> int {
    runSimpleMacros(content);
    runRegexMacros(content);
    return 0;

    
}

auto Preprocessor::runSimpleMacros(std::string& content) -> int {
    size_t pos = 0;
    for (const auto& [key, value] : simple_macros) {
        while((pos = content.find(key, pos)) != std::string::npos) {
            content.replace(pos, key.length(), value);
        }
    }
    return 0;
}

auto Preprocessor::runRegexMacros(std::string& content) -> int {
    for (const auto& [key, value] : regex_macros) {
        std::regex rgx(key);
        content = std::regex_replace(content, rgx, value);
    }
    return 0;
}

void Preprocessor::readLexStruct() {
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

            size_t delimiter_pos = line.find('=');
            if (delimiter_pos != std::string::npos) {
                std::string key = line.substr(0, delimiter_pos);
                std::string value = line.substr(delimiter_pos + 1);
                (in_regex_section ? regex_macros[key] : simple_macros[key]) = value;
            }
        }
}