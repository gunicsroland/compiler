#include "../include/preprocessor.hpp"

Preprocessor::Preprocessor() {
    readLexStruct();
}

int Preprocessor::replaceContent(std::string& content) {
    std::string slc_regex = R"(//[^\r\n]*)";
    std::string mlc_regex = R"(/\*[\s\S]*?\*/)";

    size_t pos = 0;
    for (const auto& [key, value] : macros) {
        while((pos = content.find(key, pos)) != std::string::npos) {
            content.replace(pos, key.length(), value);
        }
    }
    return 0;
}

void Preprocessor::readLexStruct() {
    std::ifstream stream_in(lex_struct_file);
        std::string line;
        while (std::getline(stream_in, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }

            size_t delimiter_pos = line.find('=');
            if (delimiter_pos != std::string::npos) {
                std::string key = line.substr(0, delimiter_pos);
                std::string value = line.substr(delimiter_pos + 1);
                macros[key] = value;
            }
        }
}