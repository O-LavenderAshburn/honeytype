#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "tokenization.hpp"

class Compiler {
public:
    inline explicit  Compiler(){};


    inline std::string compile(std::vector<Token> &tokens) {

        std::stringstream output;
        output << "global _start:\n_start:\n";
        for (int i = 0; i < tokens.size(); i++) {
            const Token& token = tokens.at(i);
            if (token.type == TokenType::_exit) {
                if (i + 1 < tokens.size() &&
                    tokens.at(i + 1).type == TokenType::int_lit) {
                    if (i + 2 < tokens.size() &&
                        tokens.at(i + 2).type == TokenType::semi) {
                        output << "    mov rax, 60\n";
                        output << "    mov rdi, " << tokens.at(i + 1).value.value()
                               << "\n";
                        output << "    syscall";
                        }
                    }
            }
        }
        return output.str();
    }


};
