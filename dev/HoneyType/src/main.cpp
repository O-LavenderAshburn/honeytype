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
            } else {
                std::cerr << "Whats on your toast" << std::endl;
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
