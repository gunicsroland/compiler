#include "../include/input_handler.hpp"
#include <fstream>
#include <iostream>

void input_handler::open_file() {
    try {
        std::ifstream stream_in(input_file_name_m);
        if (!stream_in.is_open()) {
            std::cerr << "Failed to open input file: " << input_file_name_m
                      << '\n';
            return;
        }

        std::string line;
        while (std::getline(stream_in, line)) {
            if (line.empty()) {
                continue;
            }
            file_content.append(line + '\n');
        }

        stream_in.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error: " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void input_handler::write_file() {
    try {
        std::ofstream stream_out(output_file_name_m);
        stream_out << file_content;
        stream_out.close();
    } catch (std::ifstream::failure& e) {
        std::cerr << "Error: " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
