#ifndef LEXICALANALAYSIS_H
#define LEXICALANALAYSIS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>

class LexicalAnalayser
{
        std::string m_FileName;
        std::vector<std::string> m_KeyWords;
        std::vector<std::vector<std::string > > m_StrMartix;
        //minusneri depqum sqal a ashxatum 
        bool IsNumber(const std::string &);
    public:
        LexicalAnalayser();

        //user write compilable filename
        void GetFile();
        
        //Read passing file each line separately. Make Matrix each row is vector<string>. 
        std::vector < std::vector<std::string> > MakeStrMartix();

        //Split passing string into operator and operand.
        std::vector<std::string > Split(std::string str);

        bool SemicolonValidation();
        
        bool LeftValueValidation();
};

#endif