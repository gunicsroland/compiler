#include "inputHandler.hpp"
#include <fstream>
#include <iostream>

InputHandler::~InputHandler() = default;

void InputHandler::openFile(){
	try{
		std::ifstream stream_in(input_file_name_m);
		while(stream_in.eof() == false){
			std::string line;
			std::getline(stream_in, line);
			file_content.append(line + '\n');
		}

		stream_in.close();
	}
	catch(std::ifstream::failure& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch(std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

}

void InputHandler::writeFile(){
	try{
		std::ofstream stream_out(output_file_name_m);
		stream_out << file_content;
		stream_out.close();
	}
	catch(std::ifstream::failure& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}
	catch(std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void InputHandler::replaceContent(){
	//TODO: file handler functions
    //TODO: error handling 
}
