#include "../include/lexer.hpp"

#include <algorithm>
#include <fstream>
#include <regex>
#include <vector>


lexer::lexer(const std::string& new_content) : content(new_content),
    symbol_table_index(0){
        read_in_replaces();
}

auto lexer::create_symbol_table_index(const std::string& symbol) -> std::string{
    int act_index = 0;

    if(std::find(symbol_table.begin(), symbol_table.end(), symbol) != symbol_table.end()){
        symbol_table.push_back(symbol);
        act_index = symbol_table_index++;
    }
    else {
        // Find the index of the symbol in the symbol_table vector
        auto it = std::find(symbol_table.begin(), symbol_table.end(), symbol);
        act_index = static_cast<int>(std::distance(symbol_table.begin(), it));
    }

    std::string res = "00" + std::to_string(act_index);
    return res.substr(res.length() - 3);
}

void lexer::main_replace(){
    std::regex variables("([a-z_]+)");
    std::regex consts("([0-9]+)");


    //TODO(roland): https://stackoverflow.com/questions/48365482/how-to-use-boost-regex-replace-with-a-lambda-function
    std::string new_content;
    auto it = content.cbegin();
    auto end = content.cend();
    for(std::smatch match; std::regex_search(it, end, match, consts); it = match[0].second){
        new_content += match.prefix();
        new_content += create_symbol_table_index(match.str());
    }
    new_content.append(it, end);
    content = new_content;

    new_content.clear();
    it = content.cbegin();
    end = content.cend();
    for(std::smatch match; std::regex_search(it, end, match, variables); it = match[0].second){
        new_content += match.prefix();
        new_content += create_symbol_table_index(match.str());
    }
    new_content.append(it, end);
    content = new_content;

    replace_keyword();
}

void lexer::replace_keyword(){
    for(auto const& [key, value] : replaces){
        content = std::regex_replace(content, std::regex(key), value);
    }
}

void lexer::read_in_replaces(){
    std::ifstream stream_in("lexer_struct.txt");
    std::string line;

    while(std::getline(stream_in, line)){
        if(line.empty() || line[0] == '#'){
            continue;
        }

        size_t const delimiter_pos = line.find('=');
        if(delimiter_pos != std::string::npos){
            std::string const key = line.substr(0, delimiter_pos);
            std::string const value = line.substr(delimiter_pos + 1);
            replaces[key] = value;
        }
    }
}