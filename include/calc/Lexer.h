

#ifndef CALCULATOR_ORIGINAL_LEXER_H
#define CALCULATOR_ORIGINAL_LEXER_H
#pragma once
#include <string_view>

namespace calc{

    enum class TokenType{Number,Plus,Minus,Mul,Div,LParen,RParen,End,Invalid};

    struct Token{
        TokenType type;
        double value = 0.0;
    };

    class Lexer{
    public:
        explicit Lexer(std::string_view);
        Token next();
        Token peek();



    private:
        std::string_view input;
        size_t pos = 0;
        bool has_peek;
        Token peek_tok;
    };


}




















#endif //CALCULATOR_ORIGINAL_LEXER_H
