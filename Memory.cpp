#include "Memory.h"

Memory::Memory()
{
    m_reserveRegStack.push("R24");
    m_reserveRegStack.push("R20");
    m_reserveRegStack.push("R16");
    m_reserveRegStack.push("R12");
    m_reserveRegStack.push("R8");
    m_reserveRegStack.push("R4");
    m_reserveRegStack.push("R0");
}

 std::string getVarValue(const std::string &varName)
 {
     return "fv";
 }
 std::string Memory::regAssign(std::string value)
 {
     std::string str="ASSIGN\t";
     str+=m_reserveRegStack.top();
     str+="\t";
     str+=value;
     m_emptyRegStack.push(m_reserveRegStack.top());
     m_reserveRegStack.pop();

     return str;
 }
 std::string Memory::regOperationCode(char oper)
 {
     std::string str;
     switch(oper)
     {
         case '+':
            {
                str+="ADD  ";
                break;
            }
         case '-':
            {
                str+="SUB  ";
                break;
            }
         case '*':
            {
                str+="MUL  ";
                break;
            }
         case '/':
            {
                str+="DIV  ";
                break;
            }
            default:
            {
                std::cout<<"aaa";
            }
     }
     std::string r4=m_emptyRegStack.top();
     m_emptyRegStack.pop();
     std::string r0=m_emptyRegStack.top();
    
     str+=r0;
     str+="\t";
     str+=r4;
     str+="\t";
     str+=r0;
     m_reserveRegStack.push(r4);
     return str;
     
}