#include "LexicalAnalysis.h"

void LexicalAnalayser::GetFile()
{
    std::string FileName="inputFile.txt";
    int tryFlag=true;
   /* do
    {
        if(tryFlag)
        {
            std::cout<<"Write File Name:\n";
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
    while(!m_inputFile.is_open());*/
    m_inputFile.open(FileName.c_str(),std::ios::in);
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
 void LexicalAnalayser::print()
{
    for(int i=0;i<m_StrMartix.size();i++)
    {
        std::copy(m_StrMartix[i].begin(),m_StrMartix[i].end(),std::ostream_iterator<std::string>(std::cout,","));
        std::cout<<"\n";
    }
    
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

bool LexicalAnalayser::isKeyWord(const std::string &str) const 
{
    for(int i=0;i<m_KeyWords.size();++i)
    {
        std::cerr<<"ERROR:\n Using Keyword as Function or variable name!\n";
    }
    return true;
}
bool LexicalAnalayser::isVariable(const std::string &str) const 
{
    std::string errorMessage="ERROR: \n Invalid variable name <"+str+">";
    for(int i=0;i<str.size();i++)
    {
        assert( ((int(str[i])>=int('A') && int(str[i])<=int('Z')) 
        
                || (int(str[i])>=int('a') && int(str[i])<=int('z'))) && errorMessage.c_str()
               );
    }
    return true;
}
bool LexicalAnalayser::isMathExpression(const std::string &str) const
{
    return true;
}
void LexicalAnalayser::addNewKeyword(const std::string &str)
{
    m_KeyWords.push_back(str);
}
void LexicalAnalayser::simpleSemiColonValid() const
{
    assert(!(--m_StrMartix.end())->empty() && "Missing semicolon in end of file ");
}
bool LexicalAnalayser::simpleValidation() const
{
    simpleSemiColonValid();

   for(int i=0;i<m_StrMartix.size()-1;i++)
   {
       if(m_StrMartix[i].size()>1)
       {
           isMathExpression(m_StrMartix[i][m_StrMartix[i].size()-1]);
       }
   }
   
    for(int i=0;i<m_StrMartix.size()-1;i++)
    {
        for(int j=1;j<m_StrMartix[i].size();j++)
        {
            isVariable(m_StrMartix[i][j-1]);
        }
    }

    
    return true;
}

bool LexicalAnalayser::isValidSymbol(const char &ch)
{
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
    if(str[i]==')')
    {
        --i;
        while(str[i]!='(')
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
    if(true)//simpleValidation())
    {
        VariableOrFunc();
        for(int i=0;i<m_StrMartix.size();i++)
        {
            std::cout<<std::endl;
            for(int j=0;j<m_StrMartix[i].size();j++)
            {
                std::cout<<m_StrMartix[i][j];
            }
        }
        return m_StrMartix;
    }
    else
    {
        std::cerr<<"ERROR\n : You have a mistakes plesae to correct it \n";
        std::terminate();
    }
}