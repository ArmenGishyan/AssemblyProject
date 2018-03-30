#include "postfixcalculator.h"

PostfixCalculator::PostfixCalculator() {}

void PostfixCalculator::setExpression(const std::string &expression)
{
    m_postfixNotation.clear();
    m_expression = expression;

    assert(bracketValidator() == true);

    infixToPostfix();
}

std::string PostfixCalculator::getPostfixNotation()
{
    std::string postfix;

    for (auto token : m_postfixNotation)
    {
        postfix += token;
      //  postfix += " ";
    }
    return postfix;
}

double PostfixCalculator::getResult()
{
    return evaluateFromPostfixNotation();
}

bool PostfixCalculator::bracketValidator() const
{
    std::stack<char> stack;

    for (size_t i = 0; i < m_expression.length(); i++)
    {
        if (m_expression[i] == '(')
            stack.push(m_expression[i]);

        if (m_expression[i] == ')')
        {
            if (!stack.empty())
            {
                stack.pop();
            }
            else
            {
                return false;
            }
        }
    }

    if (!stack.empty())
        return false;

    return true;
}

bool PostfixCalculator::isOperand(const char &ch) const
{
   return ((ch >= '0') && (ch <= '9'));
}

bool PostfixCalculator::isOperator(const char &ch) const
{
    switch(ch)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
        return true;
    }

    return false;
}

int PostfixCalculator::getPrioritet(const char &ch) const
{
    switch(ch)
    {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
        return 4;
    }

    return -1;
}

double PostfixCalculator::calculate(const char &operation, double leftOperand, double rightOperand) const
{
    switch(operation)
    {
    case '+':
        return leftOperand + rightOperand;
    case '-':
        return leftOperand - rightOperand;
    case '*':
        return leftOperand * rightOperand;
    case '/':
        return leftOperand / rightOperand;
    case '^':
        return pow(leftOperand, rightOperand);
    }

    return 0.0000;
}

void PostfixCalculator::infixToPostfix()
{
    std::stack<char> operation_stack;

    for (size_t i = 0; i < m_expression.length(); i++)
    {
        if (isOperand(m_expression[i]))
        {
            /* check if number has multiple digits or number is real then add to str */
            std::string operand;
            size_t j = i;
            operand += m_expression[j];
            j++;

            while (j < m_expression.length() && (isOperand(m_expression[j]) || m_expression[j] == '.'))
            {
                operand += m_expression[j];
                j++;
                i++;
            }
            /* **************************************************** */

            m_postfixNotation.push_back(operand);
        }
        else if (isOperator(m_expression[i]))
        {
           while (
                  (!operation_stack.empty()) &&
                  (operation_stack.top() != '(') &&
                  (getPrioritet(m_expression[i]) < getPrioritet(operation_stack.top()))
                 )
           {
               // convert char to string and then push_back to the link list
               m_postfixNotation.push_back(std::string(1, operation_stack.top()));
               operation_stack.pop();
           }

           operation_stack.push(m_expression[i]);
        }
        else if (m_expression[i] == ')')
        {
           while ( (!operation_stack.empty()) && (operation_stack.top() != '(') )
           {
               m_postfixNotation.push_back(std::string(1, operation_stack.top()));
               operation_stack.pop();
           }

           operation_stack.pop();
        }
        else if (m_expression[i] == '(')
        {
           operation_stack.push(m_expression[i]);
        }
    }

    while (!operation_stack.empty())
    {
        if (operation_stack.top() != '(')
        {
            m_postfixNotation.push_back(std::string(1, operation_stack.top()));
            operation_stack.pop();
        }
    }
}

double PostfixCalculator::evaluateFromPostfixNotation() const
{
    double leftOperand, rightOperand, result;
    std::stack<double> operand_stack;

    for (auto token : m_postfixNotation)
    {
        if (isOperand(token[0]))
        {
            // (std::stod) convert from string to double
            operand_stack.push(std::stod(token));
        }
        else if (isOperator(token[0]) && !operand_stack.empty())
        {
            rightOperand = operand_stack.top();
            operand_stack.pop();
            leftOperand = operand_stack.top();
            operand_stack.pop();

            result = calculate(token[0], leftOperand, rightOperand);
            operand_stack.push(result);
        }
    }

    if (!operand_stack.empty())
    {
        result = operand_stack.top();
    }

    return result;
}
