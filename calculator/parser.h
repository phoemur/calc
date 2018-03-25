/* 
This is a recursive descent parser to evaluate arithmetic expressions.
Based on: http://www.dreamincode.net/forums/topic/234775-creating-a-recursive-descent-parser-oop-style/

The Grammar:

expr -> term ‘+’ term
expr -> term ‘-‘ term
expr -> term
term -> unary ‘*’ unary
term -> unary ‘/’ unary
term -> unary '%' unary
term -> unary
unary -> ‘-‘ power
unary -> ‘+’ power
unary -> power
power -> factor '^' factor
power -> factor
factor -> '(' expr ')'
factor -> number 
*/

#ifndef PARSER_RDP_MAIN_HEADER
#define PARSER_RDP_MAIN_HEADER

#include <istream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <vector>

namespace Parser {
    
class ParseError : public std::runtime_error {
public:
    ParseError(const std::string& msg);    
    ParseError();
};


class Interface {
public:
    virtual ~Interface() noexcept = default;
    virtual double getValue() = 0;
    
    static char getChar(std::istream& in);
    static void ignoreSpace(std::istream& in);
};


class Number : public Interface {
    double value;
public:
    Number(std::istream& in);
    virtual double getValue() override;
};


class Factor : public Interface {
    std::unique_ptr<Interface> expr;
public:
    Factor(std::istream& in);
    virtual double getValue() override;
};

class Power : public Interface {
    std::stack<std::unique_ptr<Factor>> values; //power is right-associative, so use stack
public:
    Power(std::istream& in);
    virtual double getValue() override;
};


class Unary : public Interface {
    int sign;
    std::unique_ptr<Power> value;
public:
    Unary(std::istream& in);
    virtual double getValue() override;
};


class Term : public Interface {
    std::vector<std::unique_ptr<Unary>> values;
    std::vector<char> ops;
public:
    Term(std::istream& in);
    virtual double getValue() override;
};


class Expression : public Interface {
    std::vector<std::unique_ptr<Term>> values;
    std::vector<char> ops;
public:
    Expression(std::istream& in);
    virtual double getValue() override;
};

} // end of namespace Parser

#endif // PARSER_RDP_MAIN_HEADER
