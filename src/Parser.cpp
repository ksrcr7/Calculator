#include "calc/Parser.h"
#include "calc/Lexer.h"


namespace calc {
    Parser::Parser(calc::Lexer &lex) :
            message(),
            error(Error::None),
            lexer(&lex),
            had_error(false)

    {}
}
