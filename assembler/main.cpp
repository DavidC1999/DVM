#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Tokenizer.h"
#include "Assembler.h"

#define FILE_PATH "D:\\Users\\David\\Documents\\programming\\VM\\assembler\\asm\\test.vmasm"

std::string get_file_contents(const char *file_path) {
    std::ifstream file(file_path);
    if (file.is_open()) {
        std::stringstream contents;

        std::string line;
        while (getline(file, line)) {
            contents << line << std::endl;
        }

        return contents.str();
    } else {
        std::cout << "Could not open file: " << file_path << std::endl;
        std::exit(1);
    }
}

void write_to_out_file(const program_t& program) {
    std::ofstream file;
    file.open("../program.bin", std::ios_base::binary);
    if (file.is_open()) {
        for (const uint8_t &byte : program) {
            file.write((char*)&byte, sizeof(byte));
        }
    } else {
        std::cout << "Could not open output file" << std::endl;
        std::exit(1);
    }
}

int main() {
    std::string text = get_file_contents(FILE_PATH);

    Tokenizer tokenizer(text);
    token_list_t tokens = tokenizer.tokenize();

    for (std::unique_ptr<Token> const &token : tokens) {
        std::cout << *token << std::endl;
    }

    Assembler assembler(std::move(tokens));
    program_t program = assembler.assemble();

    for (const uint8_t &byte : program) {
        std::cout << (int) byte << ", ";
    }
    std::cout << std::endl;

    write_to_out_file(program);
}