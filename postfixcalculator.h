#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <stack>
#include <list>
#include <string>
#include <cmath>
#include <cassert>

class PostfixCalculator
{
private:
    std::string m_expression;
    std::list<std::string> m_postfixNotation;

    bool bracketValidator() const;
    bool isOperand(const char &ch) const;
    bool isOperator(const char &ch) const;
    int getPrioritet(const char &ch) const;
    double calculate(const char &operation, double leftOperand, double rightOperand = 0) const;

    void infixToPostfix();
    double evaluateFromPostfixNotation() const;

public:
    PostfixCalculator();
    PostfixCalculator(const PostfixCalculator&) = delete;
    PostfixCalculator& operator=(const PostfixCalculator&) = delete;

    void setExpression(const std::string &expression);
    double getResult();
    std::string getPostfixNotation();
};

#endif // POSTFIXCALCULATOR_H
