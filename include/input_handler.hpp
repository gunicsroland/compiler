#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <string>

class input_handler {
  public:
    input_handler() = default;
    explicit input_handler(std::string input_file_name)
        : input_file_name_m(std::move(input_file_name)) {}
    input_handler(std::string input_file_name, std::string output_file_name)
        : input_file_name_m(std::move(input_file_name)),
          output_file_name_m(std::move(output_file_name)) {}

    input_handler(input_handler const&) = default;
    input_handler& operator=(input_handler const&) = default;
    input_handler(input_handler&&) = default;
    input_handler& operator=(input_handler&&) = default;

    auto get_input_file_name() {
        return input_file_name_m;
    }
    void set_file_input_name(std::string const& input_file_name) {
        input_file_name_m = input_file_name;
    }

    auto get_output_file_name() {
        return output_file_name_m;
    }
    void set_file_output_name(std::string const& output_file_name) {
        output_file_name_m = output_file_name;
    }

    auto get_file_content() {
        return file_content;
    }
    void set_file_content(std::string file_content) {
        this->file_content = std::move(file_content);
    }

    void open_file();
    void write_file();

    ~input_handler() = default;

  private:
    std::string input_file_name_m;
    std::string output_file_name_m;
    std::string file_content;
};

#endif