#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <fstream>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iterator>
#include <sstream>
#include "postfixcalculator.h"
#include "SemanticAnalysis.h"
#include "Memory.h"
#include "varRegWrap.h"

class CodeGeneration 
{
    private:
        std::map<std::string,VarRegWrap>  MemoryAddress;

        std::string makeMathExpresion(std::string str,const int index);
        std::string makeVaribleName( std::string const &str,const int index);
        std::string makeFunctionName(std::string const &str);
        std::string makeMemoryAddress();
        void addVariable(const std::string &varName,const std::string &varValue);
        std::string getVarValue(const std::string &varName);
        void DataSegment();
        template <class T>
        void clearStack(std::stack<T> &st);
       

    public:
        std::fstream m_outputFile;
        std::fstream m_inputFile;
        PostfixCalculator m_C_object;
        CodeGeneration(std::string s_OutfileName="assemblyOutput.txt",std::string s_InFileName="inputFile.txt");
        ~CodeGeneration(); 

        //kardum a filic stugum a funkcia a te math artahaytutyun berum  a postfixi  
        void ReadFromFile();
};

template <class T>
void clearStack(std::stack<T> &st)
        {
            while(!st.empty)
            {
                st.pop();
            }
        }

#endif