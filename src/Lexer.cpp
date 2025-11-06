#include "Lexer.h"
#include <string>





calc::Token calc::Lexer::next() {
    if(has_peek){
        has_peek = false;
        return peek_tok;
    }

    auto isSpace = [](char c){
        return c == '\t' || c == '\n' || c == '\r' || c == ' ';
    };

    while (pos < input.size() && isSpace(input[pos])){
        ++pos;
    }

    if(pos >= input.size()){
        return Token{TokenType::End,0.0};
    }

    char c = input[pos];
    switch (c) {
            case '+': ++pos; return Token{TokenType::Plus,0.0};
            case '-': ++pos; return Token{TokenType::Minus,0.0};
            case '/': ++pos; return Token{TokenType::Div,0.0};
            case '*': ++pos; return Token{TokenType::Mul,0.0};
            case '(': ++pos; return Token{TokenType::LParen,0.0};
            case ')': ++pos; return Token{TokenType::RParen,0.0};
            default:break;

    }


    size_t start = pos;
    bool seen_digit = false;
    while(pos < input.size() && std::isdigit(static_cast<unsigned char>(input[pos]))){
        seen_digit = true;
        ++pos;
    }

    if(pos < input.size() && input[pos] == '.'){
        seen_digit = true;
        ++pos;
    }

    if(seen_digit){
        const auto len = pos - start;
        double value = std::stod(std::string (input.substr(start,len)));
        return Token{TokenType::Number,value};
    }
    ++pos;
    return Token{TokenType::Invalid,0.0};

}

calc::Token calc::Lexer::peek() {
    if(has_peek){
        return peek_tok;
    }

    else{
        peek_tok = this->next();
        has_peek = true;
        return peek_tok;
    }
}
