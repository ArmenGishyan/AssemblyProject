#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <fstream>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <iterator>
#include <sstream>
#include <vector>
#include "postfixcalculator.h"
#include "SemanticAnalysis.h"
#include "Memory.h"
#include <sstream>
#include "varRegWrap.h"
#include "LexicalAnalysis.h"

class CodeGeneration 
{
    private:
        std::vector<std::vector<std::string> >  m_ExpressionMatrix;
        Memory m_mem;
        std::string makeMathExpresion(std::string str,const int index);
        std::string makeVaribleName( std::string const &str,const int index);
        std::string makeFunctionName(std::string const &str);
        std::string makeMemoryAddress();
        void WriteVarInDataSegment(std::vector<std::string>  const &vec); 

        void addVariable(const std::string &varName,const std::string &varValue);
        VarRegWrap getVarValue(const std::string &varName);
        std::string getNumberFromPostExpr(std::string,int &index);
        
        
       
        bool CodeIsFunc(std::string const &str);
        bool CodeIsVariable(std::string const &str);
        std::string MakeFunctionCode(std::string const &str);

        std::string MakeFuncLabel(std::string const &str);
        void VariableInit(std::vector<std::string> &str);
        std::string SolveMathExpression(std::string const & str);

        std::vector<std::string > makeMAthExpressionToVector(std::string const &str);
    public:
        void CodeSegment();
        void DataSegment();

        std::string  changeVariableTovalue(std::string const &str);
        
        std::fstream m_outputFile;
        PostfixCalculator m_C_object;
        CodeGeneration(std::vector<std::vector<std::string> > const &Matrix, std::string s_OutfileName="assemblyOutput.txt");
        ~CodeGeneration(); 

        //kardum a filic stugum a funkcia a te math artahaytutyun berum  a postfixi  
        void ReadFromFile();
};



#endif