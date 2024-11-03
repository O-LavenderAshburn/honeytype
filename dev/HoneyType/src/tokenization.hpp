#pragma once
#include <string>
#include <vector>

enum class TokenType { _exit, int_lit, semi};

struct Token {
    TokenType type;
    std::optional<std::string> value{};
};

class Tokenizer {
public:



    inline explicit  Tokenizer(std::string src):
        m_src(std::move(src)) {
    }


    inline std::vector<Token> tokenize(){
        // Create tokens based on contents
        std::vector<Token> tokens{};
        std::string buf;

        //while we have something to consume
        while(peek().has_value()) {

            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())){
                    buf.push_back(consume());
                }

                if (buf == "exit") {
                    tokens.push_back({.type = TokenType::_exit});
                    buf.clear();
                    continue;
                } else {
                    std::cerr << "Whats on your toast" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            // peek for digits
            else if (std::isdigit(peek().value())) {
                buf.push_back(consume());

                while(peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }

                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }

            // Consume semi colons
            else if (peek().value() == ';') {
                tokens.push_back({.type = TokenType::semi});
                consume();
                continue;

            }
            // Consume whitespace
            else if(std::isspace(peek().value())) {
                consume();
                continue;
            }else{
                std::cerr << "Whats on your toast" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        m_index= 0;
        return tokens;
    }

private:
    /**
     * Peek at next char in the source code.
     * @param ahead
     * @return
     */
    [[nodiscard]] std::optional<char> peek(int ahead = 1) const
    {
        if (m_index + ahead > m_src.length()) {
            return {};
        }
        
        return m_src.at(m_index);

    }

    /**
     * consume m_src character.
     * @return
     */
    char consume() {
        return m_src.at(m_index ++);
    }

    const std::string m_src;
    int m_index= 0;

};
