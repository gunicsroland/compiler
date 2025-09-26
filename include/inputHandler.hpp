#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <string>
#include <fstream>
#include <iostream>

class InputHandler {
    public:
        InputHandler(){}
        InputHandler(const std::string& input_file_name)
         : input_file_name_m(input_file_name){}
        InputHandler(const std::string& input_file_name, const std::string& output_file_name)
         : input_file_name_m(input_file_name), output_file_name_m(output_file_name){}

        std::string& get_input_file_name(){return input_file_name_m;}
        void set_file_input_name(const std::string& input_file_name){input_file_name_m = input_file_name;}

        std::string& get_output_file_name(){return output_file_name_m;}
        void set_file_output_name(const std::string& output_file_name){output_file_name_m = output_file_name;}

        std::string& get_file_content(){return file_content;}
        void set_file_content(const std::string& file_content){this->file_content = file_content;}

        void openFile();
        void writeFile();
        void replaceContent();

        ~InputHandler();
    private:
        std::string input_file_name_m;
        std::string output_file_name_m;
        std::string file_content;
};

#endif