#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Tokenizer.h"
#include "Assembler.h"

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

void write_to_out_file(const char* filepath, const program_t &program) {
    std::ofstream file;
    file.open(filepath, std::ios_base::binary);
    if (file.is_open()) {
        for (const uint8_t &byte : program) {
            file.write((char *) &byte, sizeof(byte));
        }
    } else {
        std::cout << "Could not open output file" << std::endl;
        std::exit(1);
    }
}

void print_usage(std::ostream &stream, const std::string &program) {
    stream << "USAGE: " << program << " <options> [filename]" << std::endl;
    stream << "OPTIONS:" << std::endl;
    stream << "    -h|--help                      Shows this message" << std::endl;
    stream << "    -o|--output [filename]         Specifies the path and filename of the output file" << std::endl;
}

struct Options {
    const char* in_filepath;
    const char* out_filepath;
};

Options parse_command_line_arguments(int argc, const char **argv) {
    std::string program_name = argv[0];

    Options output {
        .in_filepath = "",
        .out_filepath = "out.bin"
    };

    uint8_t cla_i = 1;
    while (cla_i < argc) {
        if (argv[cla_i] == std::string("-h") || argv[cla_i] == std::string("--help")) {
            print_usage(std::cout, program_name);
            std::exit(0);
        }
        if (argv[cla_i] == std::string("-o") || argv[cla_i] == std::string("--output")) {
            ++cla_i;
            if (cla_i >= argc) {
                std::cerr << "ERROR: --output argument expects filename" << std::endl;
                print_usage(std::cerr, program_name);
                std::exit(1);
            }
            output.out_filepath = argv[cla_i];
            ++cla_i;
            continue;
        }

        if(argv[cla_i][0] == '-') {
            std::cerr << "ERROR: unknown option: " << argv[cla_i] << std::endl;
            print_usage(std::cerr, program_name);
            std::exit(1);
        }

        output.in_filepath = argv[cla_i];
        ++cla_i;
    }

    if(*output.in_filepath == '\0') {
        std::cerr << "ERROR: please provide a file to assemble" << std::endl;
        print_usage(std::cerr, program_name);
        std::exit(1);
    }

    return output;
}

int main(int argc, const char **argv) {

    Options cla = parse_command_line_arguments(argc, argv);

    std::string text = get_file_contents(cla.in_filepath);

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

    write_to_out_file(cla.out_filepath, program);
}