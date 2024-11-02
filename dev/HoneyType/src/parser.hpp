#pragma once

class Parser{
public:
    inline explicit Parser(std::vector<Token> tokens ):
        m_tokens(std::move(tokens)) {
    }
private:
    const std::vector<Token> m_tokens;
};