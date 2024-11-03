#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <optional>

#include "tokenization.hpp"
#include "parser.hpp"


// std::string tokens_to_asm(const std::vector<Token> &tokens) {
//     std::stringstream output;
//     output << "global _start:\n_start:\n";
//
//     // For each of the tokens check if it is a return
//     // token with int_lit and semi following.
//
//     for (int i = 0; i < tokens.size(); i++) {
//         const Token& token = tokens.at(i);
//         if (token.type == TokenType::_exit) {
//             if (i + 1 < tokens.size() &&
//                 tokens.at(i + 1).type == TokenType::int_lit) {
//                 if (i + 2 < tokens.size() &&
//                     tokens.at(i + 2).type == TokenType::semi) {
//                     output << "    mov rax, 60\n";
//                     output << "    mov rdi, " << tokens.at(i + 1).value.value()
//                            << "\n";
//                     output << "    syscall";
//                 }
//             }
//         }
//     }
//     return output.str();
// }

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

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();
    std::cout << tokens.size()<< std::endl;
    std::cout << "Running asm" << std::endl;

    std::cout << tokenizer.generate_asm(tokens) << std::endl;

    {
        std::fstream file("../out.asm", std::ios::out);
        file << tokenizer.generate_asm(tokens);
    }

    system("nasm -felf64 ../out.asm");
    system("ld -o out ../out.o");

    return EXIT_SUCCESS;
}
