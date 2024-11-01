#include <fstream>
#include <iostream>
#include <sstream>

enum class TokenType { _return, int_lit, semi };

struct Token {
    TokenType type;
    std::optional<std::string> value{};
};

std::vector<Token> tokenize(const std::string &str) {
    std::vector<Token> tokens{};
    std::string buf = "";

    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);

        if (std::isalpha(c)) {
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            if (buf == "return") {
                tokens.push_back({.type = TokenType::_return});
                buf.clear();
            } else {
                std::cerr << "Whats on your toast" << std::endl;
                exit(EXIT_FAILURE);
            }

        } else if (isdigit(c)) {
            buf.push_back(c);
            i++;
            while (std::isdigit(str.at(i))) {
                /* code */
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();

        } else if (c == ';') {
            tokens.push_back({.type = TokenType::semi});

        } else if (isspace(c)) {
            continue;

        } else {
            std::cerr << "Whats on your toast" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}

std::string tokens_to_asm(const std::vector<Token> &tokens) {
    std::stringstream output;
    output << "global _start\nstart\n";

    for (int i = 0; i < tokens.size(); i++) {
        const Token &token = tokens.at(i);
        
        if (token.type == TokenType::_return) {
            if (i + 1 < tokens.size() &&
                tokens.at(i + 1).type == TokenType::int_lit) {
                if (i + 2 < tokens.size() &&
                    tokens.at(i + 2).type == TokenType::semi) {
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << tokens.at(i + 1).value.value()
                           << "\n";
                }
                output << "    syscall";
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "incorrect usage " << std::endl;
        std::cout << "usage: <script.honey> " << std::endl;
        return EXIT_FAILURE;
    }
    std::stringstream contents_stream;

    {
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
    }

    return EXIT_SUCCESS;
}
