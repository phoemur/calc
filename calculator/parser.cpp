#include "parser.h"

#include <cmath>
#include <sstream>
#include <string>


Parser::ParseError::ParseError(const std::string& msg) : std::runtime_error(msg) {}
Parser::ParseError::ParseError() : ParseError("A parsing error has ocurred") {}

void Parser::Interface::ignoreSpace(std::istream& in) 
{
    while(std::isspace(in.peek())) {
        in.get();
    }
}

char Parser::Interface::getChar(std::istream& in)
{
    ignoreSpace(in); //remove all preceding space
    char ret = in.get();
    ignoreSpace(in); //remove all following space
    return ret;
}

Parser::Number::Number(std::istream& in) 
{
    ignoreSpace(in); //remove all preceding space
    in >> value;
    if(!in) {
        throw ParseError("Error");
    }
    ignoreSpace(in); //remove all following space
}

double Parser::Number::getValue() {return value;}

Parser::Factor::Factor(std::istream& in)
    : expr{nullptr}
{
    ignoreSpace(in); //remove all preceding space
    if(in.peek() == '(') { //check to see if a paren was used
        in.get();
        expr.reset(new Expression(in));
        ignoreSpace(in); //remove all following space
        if(in.peek() != ')') { //make sure the paren was matched
            throw ParseError("Unbalanced Parenthesis");
        } else {
            in.get();
        }
    } else { //if there is no paren then we just have a number
        expr.reset(new Number(in));
    }
}

double Parser::Factor::getValue() {return expr->getValue();}


Parser::Power::Power(std::istream& in)
{
    values.emplace(new Factor(in));
    ignoreSpace(in);
    while (in.peek() == '^') {
        getChar(in); // just ignore the operator
        values.emplace(new Factor(in));
        ignoreSpace(in);
    }
}

double Parser::Power::getValue()
{
    while (values.size() > 1) {
        double num2 = values.top()->getValue();
        values.pop();
        double num1 = values.top()->getValue();
        values.pop();
        double result = std::pow(num1, num2);
        std::istringstream ss {std::to_string(result)};
        values.emplace(new Factor(ss));
    }
    
    return values.top()->getValue();
}

Parser::Unary::Unary(std::istream& in) 
    : sign{1}, value{nullptr}
{
    ignoreSpace(in); //get rid of any preceding space
    while(in.peek() == '-' || in.peek() == '+') { //while we have an operator to parse
        if(getChar(in) == '-') { //if the operator actully has an effect
            sign *= -1;
        }
    }
    value.reset(new Power(in)); //parse the factor following the unary operators
}

double Parser::Unary::getValue() {return sign * value->getValue();}


Parser::Term::Term(std::istream& in) 
{
    values.emplace_back(new Unary(in)); //construct the first value
    ignoreSpace(in); //ignore preceding space
    while(in.peek() == '*' || in.peek() == '/' || in.peek() == '%') {
        ops.push_back(getChar(in)); //push back the operator
        values.emplace_back(new Unary(in)); //push back the left operand
    }
}

double Parser::Term::getValue() 
{
    double ret = values[0]->getValue(); //get the first value
    for(unsigned int i=1;i<values.size();++i) { //loop though the rest of the values
        if(ops[i-1] == '*') { //check to see which operator it is and preform the acoridng action
            ret *= values[i]->getValue();
        } else if (ops[i-1] == '/'){
            ret /= values[i]->getValue();
        } else if (ops[i-1] == '%') {
            ret = static_cast<long>(ret) % static_cast<long>(values[i]->getValue());
        }
    }
    return ret;
}

Parser::Expression::Expression(std::istream& in) {
    ignoreSpace(in);
    values.emplace_back(new Term(in));
    while(in.peek() == '+' || in.peek() == '-') {
        ops.push_back(getChar(in));
        values.emplace_back(new Term(in));
    }
}

double Parser::Expression::getValue()
{
    double ret = values[0]->getValue();
    for(unsigned int i=1;i<values.size();++i) {
        if(ops[i-1] == '+') {
            ret += values[i]->getValue();
        } else if (ops[i-1] == '-') {
            ret -= values[i]->getValue();
        }
    }
    return ret;
}