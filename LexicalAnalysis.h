#ifndef LEXICALANALAYSIS_H
#define LEXICALANALAYSIS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>

class LexicalAnalayser
{
    private:
        std::fstream m_inputFile;
        std::vector<std::string> m_KeyWords;
        std::vector<std::vector<std::string > > m_StrMartix;
        
        void simpleSemiColonValid() const;
        void isKeyWord(const std::string &str) const;
        void isVariable(const std::string &str) const;
        void VariableOrFunc();
        int MakeExpression(const int &Lineindex);
        bool simpleValidation() const;
        bool isNumber(const std::string &) const;

    public:
        LexicalAnalayser();

        //user write compilable filename
        void GetFile();
        static bool IsFunc(std::string const &str);
        void addNewKeyword(const std::string &str);
        std::vector<std::vector<std::string> > PassMatrixToCodeGen();
        void MakeExpressioncMatrix();
        
        
        void print();
};
#endif