#ifndef MEMORY_H
#define MEMORY_H

#include <stack>
#include <string>
#include <map>
#include <iostream>

class Memory
{
    public:
        Memory();
        std::string regAssign(std::string value);
        std::string regOperationCode(char oper);
        std::stack<std::string> m_emptyRegStack;
        std::stack<std::string> m_reserveRegStack;


};

#endif