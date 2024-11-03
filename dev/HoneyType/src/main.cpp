#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>

#include "tokenization.hpp"
#include "compiler.hpp"
#include "parser.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "incorrect usage " << std::endl;
        std::cout << "usage: <script.honey> " << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    Compiler compiler;
    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    std::cout << tokens.size()<< std::endl;
    std::cout << "Running asm" << std::endl;

    std::cout << compiler.compile(tokens)<< std::endl;

    {
        std::fstream file("../out.asm", std::ios::out);
        file << compiler.compile(tokens);
    }

    system("nasm -felf64 ../out.asm");
    system("ld -o out ../out.o");

    return EXIT_SUCCESS;
}
