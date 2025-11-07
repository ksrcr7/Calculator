#include "Calculator.h"
#include "calc/Lexer.h"
#include "calc/Parser.h"
namespace calc{
    calc::Result calc::Calculator::evaluate(std::string_view expression) noexcept {
        Result out;

        auto only_ws = [](std::string_view s){
            for(char c: s){
                if(!(c == '\t' || c == ' ' || c == '\r' || c == '\n'))return false;
            }
            return true;
        };

        if(expression.empty() || only_ws(expression)){
            out.error = Error::ParseError;
            out.message = "empty expression";
            out.value = 0.0;
            return out;
        }

        Lexer lexer{expression};
        Parser parser{lexer};

        double value = parser.parsExpression();

        if(parser.ok()){
            out.error = parser.errorCode();
            out.message = parser.errorMessage();
            out.value = 0.0;
            return out;
        }

        if(!parser.atEnd()){
            out.error = Error::ParseError;
            out.message = "trailing input after valid expression.";
            out.value = 0.0;
            return out;
        }

        out.value = value;
        out.error = Error::None;
        out.message.clear();
        return out;

    }}


