

#ifndef CALCULATOR_ORIGINAL_PARSER_H
#define CALCULATOR_ORIGINAL_PARSER_H

#pragma once
#include "calc/Lexer.h"
#include "calc/Calculator.h"
#include <string>

namespace calc{


    class Parser{
    public:
        explicit Parser(calc::Lexer &);
        double parsExpression();

    private:
        double parsTerm();
        double parsFactor();
        bool match(TokenType);
        Token peek();
        Token next();
        std::string message;
        Error error = Error::None;
        Lexer* lexer = nullptr;
        bool had_error;

    };
}


























#endif //CALCULATOR_ORIGINAL_PARSER_H
