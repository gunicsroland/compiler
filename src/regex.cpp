#include "../include/regex.hpp"
#include <sstream>
#include <vector>

auto split(const std::string& text, char delimiter) -> std::vector<std::string> {
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

auto join(const std::vector<std::string>& elements, const std::string& delimiter = " ") -> std::string {
    std::ostringstream oss;
    for (size_t i = 0; i < elements.size(); ++i) {
        oss << elements[i];
        if (i + 1 < elements.size()) {
            oss << delimiter;
        }
    }
    return oss.str();
}

auto regexM::numbers() -> const std::unordered_map<std::string, std::string>& {
    static const std::unordered_map<std::string, std::string> numbers_map = {
        {"firststate", "q0"},
        {"finalstates", "q2q3"},
        {"finalstate", "q2"},
        {"errorstate", "err"},
        {"q0+", "q1"},
        {"q0-", "q1"},
        {"q0d", "q2"},
        {"q1d", "q2"},
        {"q2d", "q2"}
    };
    return numbers_map;
}

regexM::regexM() : _state(numbers().at("firststate"))
            , _finalstate(numbers().at("finalstate")),
             _errorstate(numbers().at("errorstate")), _index(0){}

auto regexM::is_finalstate(const std::string& key, const std::string& value) -> bool{
    return value.find(key) != std::string::npos;
}

[[nodiscard]] auto regexM::convert(char c) -> char{
    if (std::isdigit(c) != 0) { 
        return 'd';
    }
    if (std::isalpha(c) != 0){
        return 'l';
    } 
    return c;
}

[[nodiscard]] auto regexM::delta(const std::string& a, char s) const -> std::string{
    std::string na = a + regexM::convert(s);
        if (regexM::numbers().find(na) != regexM::numbers().end()) {
            return regexM::numbers().at(na);
        }
        return _errorstate;
}

auto regexM::set_input(const std::string& str) -> void {
    _input = str;
}

auto regexM::match() -> bool{
    _index = 0;
    _state = numbers().at("firststate");
    while (_index < static_cast<int>(_input.size()) && _state != _errorstate) {
        _state = delta(_state, _input[_index]);
        _index++;
    }

    return (_state == _finalstate && _state != _errorstate);
}


auto regexM::match(std::string& text) -> bool{
    _input = text;

    return regexM::match();
}

auto regexM::matches(std::string& text_corpus) -> std::vector<std::string> {
    std::vector<std::string> matches;

    std::vector<std::string> elements = split(text_corpus, ' ');
    for (std::string x : elements){
        if (regexM::match(x)){
            matches.push_back(x);
        }
    }

    return matches;
}

auto regexM::replace(std::string& text_corpus, std::string& replace_to) -> std::string{
    std::vector<std::string> matches;

    std::vector<std::string> elements = split(text_corpus, ' ');
    for (auto & element : elements){
        if(regexM::match(element)){
            element = replace_to;
        }
    }

    return join(elements);
}
