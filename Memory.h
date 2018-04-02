#ifndef MEMORY_H
#define MEMORY_H

#include <stack>
#include <string>
#include <map>
#include <iostream>
#include "varRegWrap.h"
#include <sstream>

class Memory
{
    public:
        Memory();
        std::string regAssign(std::string const &value);
        std::string regOperationCode(char const &oper);

        std::map<std::string,VarRegWrap>  MemoryAddress;
        std::stack<std::string> m_emptyRegStack;
        std::stack<std::string> m_reserveRegStack;
        std::string makeMemoryAddress();

        void clearStack();

        void printM();
};

#endif