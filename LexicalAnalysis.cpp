#include "LexicalAnalysis.h"

void LexicalAnalayser::GetFile()
{
    std::string FileName="inputFile.txt";
    int tryFlag=true;
    do
    {
        if(tryFlag)
        {
            std::cout<<"Write compilable File Name:\n";
            getline(std::cin,FileName);
            tryFlag=false;
        }
        else
        {
            std::cout<<"ERROR! \n The filename is incorrect: Try again!\n";
            getline(std::cin,FileName);
        }
        m_inputFile.open(FileName.c_str(),std::ios::in);
    }
    while(!m_inputFile.is_open());
}

bool LexicalAnalayser::isNumber(std::string const &s_obj) const
{
    for(int i=0;i<s_obj.size();i++)
    {
        if(int(s_obj[i])<=int('9') || int(s_obj[i])>=int('9') )
        return false;
    }
    return true;
}

int LexicalAnalayser::MakeExpression(const int &Lineindex)
{
    char character;
    m_inputFile>>character;
    std::string VaribleORExpr="";

    while(character!='=' && character!=';' && !m_inputFile.eof())
    {
        VaribleORExpr+=character;
        m_inputFile>>character;
    }

    m_StrMartix[Lineindex].push_back(VaribleORExpr);

    if(character==';' || m_inputFile.eof()) return 0;

    MakeExpression(Lineindex);
    return 0;
}

void LexicalAnalayser::MakeExpressioncMatrix()
{
   int Lineindex=-1;
   while(!m_inputFile.eof())
   {
       Lineindex++;
       m_StrMartix.push_back(std::vector<std::string>());
       
       MakeExpression(Lineindex);
   }
}

void LexicalAnalayser::isKeyWord(const std::string &str) const 
{
    for(int i=0;i<m_KeyWords.size();++i)
    {
        std::cerr<<"ERROR:\n Using Keyword as Function or variable name!\t"<<str<<"\n";
        std::terminate();
    }
}
void LexicalAnalayser::isVariable(const std::string &str) const 
{
    for(int i=0;i<str.size();i++)
    {
        if( !((int(str[i])>='A' && int(str[i])<='Z')  || (int(str[i])>='a' && int(str[i])<='z') || str[i]==']' || str[i]=='['))
        {
            std::cerr<<"ERROR \n : Variable or Function name must  have only alphabetic \n";
            std::terminate();
        }
    }
}

void LexicalAnalayser::addNewKeyword(const std::string &str)
{
    m_KeyWords.push_back(str);
}
void LexicalAnalayser::simpleSemiColonValid() const
{
  if(m_StrMartix[m_StrMartix.size()-1][0].size())
    {
        std::cerr<<"Missing semicolon \n";
        std::terminate();
    }
}
bool LexicalAnalayser::simpleValidation() const
{
    simpleSemiColonValid();
   
    for(int i=0;i<m_StrMartix.size()-1;i++)
    {
        for(int j=1;j<m_StrMartix[i].size();j++)
        {
            isVariable(m_StrMartix[i][j-1]);
        }
    }
    
    return true;
}

void LexicalAnalayser::VariableOrFunc()
{
    for(int i=0;i<m_StrMartix.size()-1;i++)
    {
        if(IsFunc(m_StrMartix[i][0]))
        {
            m_StrMartix[i].push_back("func");
        }
        else
        {
            m_StrMartix[i].push_back("var");
        }
    }
}

bool LexicalAnalayser::IsFunc(std::string const &str)
{
    int i=str.size()-1;
    if(str[i]==']')
    {
        --i;
        while(str[i]!='[')
        {
            --i;
            if(i==0) return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}
std::vector<std::vector<std::string> > LexicalAnalayser::PassMatrixToCodeGen()
{
    if(simpleValidation())
    {
        VariableOrFunc();
        return m_StrMartix;
    }
    else
    {
        std::cerr<<"ERROR\n : You have a mistakes plesae to correct it \n";
        std::terminate();
    }
}

LexicalAnalayser::LexicalAnalayser()
{
    m_inputFile.close();
}