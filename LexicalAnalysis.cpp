#include "LexicalAnalysis.h"

LexicalAnalayser::LexicalAnalayser()
{
    m_FileName="";
    m_KeyWords.push_back("R1");
    m_KeyWords.push_back("R4");
}
void LexicalAnalayser::GetFile()
{
    std::cout<<"Write File Name:\n";
    getline(std::cin,m_FileName);
}
std::vector < std::vector<std::string> > LexicalAnalayser::MakeStrMartix()
{
    std::vector< std::vector<std::string> > vec_Matrix;
    std::fstream inputFile;
    inputFile.open(m_FileName.c_str(),std::ios::in);
    assert(inputFile.is_open() && "File is Not open");

    std::string temp_str="";
    
    while(!inputFile.eof())
    {
        getline(inputFile,temp_str);
        vec_Matrix.push_back(Split(temp_str));
        
    }

    m_StrMartix=vec_Matrix;
    return vec_Matrix;
}
std::vector<std::string > LexicalAnalayser::Split(std::string str)
{
    std::string tempStr="";
    str+="+";

    std::vector<std::string> VecForRetrun;
    for(int i=0;i<str.length();i++)
    {
        if(int(str[i])>=int('0') && int(str[i])<=int('9') )
        {
            tempStr+=str[i];
        }
        else 
        {
            if(str[i]==' ')
            {
                continue;
            }
            if(tempStr.length()!=0 && tempStr[0]!=' ')
            {
                VecForRetrun.push_back(tempStr);
                tempStr="";
            }
                VecForRetrun.push_back(std::string(1,str[i]));
        }
    }
    return VecForRetrun;
}
bool LexicalAnalayser::IsNumber(std::string const &s_obj)
{
    for(int i=0;i<s_obj.size();i++)
    {
        if(int(s_obj[i])<=int('9') || int(s_obj[i])>=int('9') )
        return false;
    }
    return true;
}

bool LexicalAnalayser::SemicolonValidation()
{
    for(int i=0;i<m_StrMartix.size();i++)
    {
        if(m_StrMartix[i][m_StrMartix[i].size()-1]!=";")
            return false;
    }
    return true;
}

bool LexicalAnalayser::LeftValueValidation()
{
    
}