
#ifndef CALCULATOR_ORIGINAL_CALCULATOR_H


#pragma once
#include <string>
#include <stdexcept>
#include <string_view>


namespace calc{
    enum class Error{None,DivisionByZero,UnexpectedChar,UnbalancedParen,ParseError};

    struct Result{
        double value = 0.0;
        Error error = Error::None;
        std::string message;
    };

    class Calculator{
        Calculator() = default;
        ~Calculator() = default;

        Result evaluate(std::string_view expression)noexcept;

    };
}




















#endif //CALCULATOR_ORIGINAL_CALCULATOR_H
