#ifndef LEXICALANALAYSIS_H
#define LEXICALANALAYSIS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include <iterator>
#include <algorithm>

class LexicalAnalayser
{
    private:
        std::fstream m_inputFile;
        std::vector<std::string> m_KeyWords;
        std::vector<std::vector<std::string > > m_StrMartix;
        //minusneri depqum sqal a ashxatum 
        bool isNumber(const std::string &) const;
        void simpleSemiColonValid() const;
        bool isKeyWord(const std::string &str) const;
        bool isVariable(const std::string &str) const;
        bool isMathExpression(const std::string &str) const;
        bool isValidSymbol(const char &character);
        void VariableOrFunc();

        bool simpleValidation() const;
        
    public:
        //user write compilable filename
        void GetFile();
        static bool IsFunc(std::string const &str);
        
        //Split passing string into operator and operand.
        std::vector<std::string > Split(std::string str);

        int MakeExpression(const int &Lineindex);
        void MakeExpressioncMatrix();
        void addNewKeyword(const std::string &str);
        std::vector<std::vector<std::string> > PassMatrixToCodeGen();
        
        void print();
};

#endif