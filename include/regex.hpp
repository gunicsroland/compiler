#ifndef REGEX_HPP
#define REGEX_HPP

#include <string>
#include <unordered_map>

class regexM {
    private:
        std::string _input;
        std::string _state;
        std::string _finalstate;
        std::string _errorstate;
        int _index;

        static auto is_finalstate(const std::string& key, const std::string& value) -> bool;
        [[nodiscard]] static  auto convert(char c) -> char;
        [[nodiscard]] auto delta(const std::string& a, char s) const -> std::string;

    public:
        regexM();
        auto set_input(const std::string& str) ->void;
        auto match() -> bool;
        auto match(std::string& text) -> bool;
        static auto numbers() -> const std::unordered_map<std::string, std::string>&;
        auto matches(std::string& text_corpus) -> std::vector<std::string>;
        auto replace(std::string& text_corpus, std::string& replace_to) -> std::string;
};

#endif
