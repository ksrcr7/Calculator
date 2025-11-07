#include "calc/Parser.h"
#include "calc/Lexer.h"


namespace calc {
    Parser::Parser(calc::Lexer &lex) :
            message(),
            error(Error::None),
            lexer(&lex),
            had_error(false)

    {}

    double Parser::parsTerm() {
        double value = parsFactor();
        if(had_error)return 0.0;

        for(;;){
            Token t = peek();
            if(t.type == TokenType::Mul){
                next();
                double rhs = parsFactor();
                if(had_error)return 0.0;
                value *= rhs;

            }
            else if(t.type == TokenType::Div){
                next();
                double rhs = parsFactor();
                if(had_error)return 0.0;
                if(rhs == 0.0){
                    error = Error::DivisionByZero;
                    message = "division by zero";
                    had_error = true;
                    return 0.0;
                }
                value /= rhs;
            }
            else
                break;
        }
        return value;


    }

    double Parser::parsExpression() {
        double value = parsTerm();
        if(had_error)return 0.0;

        for(;;){
            Token t = peek();
            if(t.type == TokenType::Plus){
                next();
                double rhs = parsTerm();
                if(had_error)return 0.0;
                value += rhs;
            }
            else if(t.type == TokenType::Minus){
                next();
                double rhs = parsTerm();
                if(had_error)return 0.0;
                value -= rhs;
            }
            else
                break;
        }
        return value;


    }

    double Parser::parsFactor() {
        Token t = peek();
        if(t.type == TokenType::Minus){
            next();
            double v = parsFactor();
            return -v;
        }

        if(t.type == TokenType::Number){
            next();
            return t.value;
        }

        if(t.type == TokenType::LParen){
            next();
            double v = parsExpression();
            if(had_error)return 0.0;

            Token r = peek();
            if(r.type != TokenType::RParen){
                error = Error::UnbalancedParen;
                message = "missing ')'";
                had_error = true;
                return 0.0;
            }
            next();
            return v;
        }
        error = Error::ParseError;
        message = "expected number or '('";
        had_error = true;
        return 0.0;

    }

    Token Parser::peek() {
        Token t = lexer->peek();
        if(t.type == TokenType::Invalid){
            had_error = true;
            error = Error::UnexpectedChar;
            message = "unexpected character in input";
        }
        return t;
    }

    Token Parser::next() {
        Token t = lexer->next();
        if(t.type == TokenType::Invalid){
            had_error = true;
            error = Error::UnexpectedChar;
            message = "unexpected character in input";
        }
        return t;
    }

    bool Parser::match(TokenType expected) {
        Token t = peek();
        if(t.type == expected){
            next();
            return true;
        }
        return false;
    }
}
