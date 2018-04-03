#include "CodeGeneration.h"

typedef std::pair<std::string,VarRegWrap> pair_type;


CodeGeneration::CodeGeneration(std::vector<std::vector<std::string> > const &Matrix, std::string s_OutfileName)
{
    m_ExpressionMatrix=Matrix;
    
    m_outputFile.open(s_OutfileName.c_str(),std::ios::out);
    assert(m_outputFile.is_open());
}
CodeGeneration::~CodeGeneration()
{
    m_outputFile.close();
}
void CodeGeneration::DataSegment()
{  
    m_outputFile.seekg(std::ios::beg);
    m_outputFile<<".DATA\n";
    for(int i=0;i<m_ExpressionMatrix.size();i++)
    {
        if(m_ExpressionMatrix[i][m_ExpressionMatrix[i].size()-1]=="var")
        {
            WriteVarInDataSegment(m_ExpressionMatrix[i]);
        }
    }
}
std::string CodeGeneration::makeMathExpresion(std::string str,const int index)
{
    std::string s_tempStr="";
    for(int i=index+1;i<str.size()-1;i++)
    {
        s_tempStr+=str[i];
    }
    return s_tempStr;
}
 std::string CodeGeneration::makeVaribleName(std::string const &s_expresion,const int index)
 {
     std::string s_str="";
     std::cout<<index<<std::endl;
     for(int i=0;i<index;i++)
     {
         s_str+=s_expresion[i];
     }
     std::cout<<s_str<<std::endl;
     return s_str;
 }
void CodeGeneration::addVariable(const std::string &varName,const std::string &varValue)
{
    VarRegWrap obj(m_mem.makeMemoryAddress(),varValue);
    m_mem.MemoryAddress.insert(pair_type(varName,obj));
}
VarRegWrap CodeGeneration::getVarValue(const std::string &varName)
{
    std::map<std::string,VarRegWrap>::iterator itInmap=m_mem.MemoryAddress.find(varName);
    if(itInmap==m_mem.MemoryAddress.end())
    {
        std::cout<<"ERROR: \n You cannot use undeclared variable \n";
        std::terminate();
    }
    else 
    {   
        if(itInmap->second.sm_VarValue=="00")
        {
            std::cout<<"ERROR: \n You cannot use uninitialized variable \n";
             std::terminate();
        }
        else
        {
            return VarRegWrap(itInmap->second);
        }
    }
}
std::string CodeGeneration::makeFunctionName(std::string const &s_str)
{
    std::string s_funcName="";
    int index=0;
    while(s_str[index]!='[' && index<s_str.size())
    {
        s_funcName+=s_str[index];
        index++;
    }
    return s_funcName;
}

void CodeGeneration::WriteVarInDataSegment(std::vector<std::string>  const &vec)
{
    if(vec.size()==2)
    {
            m_outputFile<<"DWORD\t"<<vec[0]<<"\n";
    }
    else
    {
        std::vector<std::string>::const_iterator it= vec.begin();
        while(it!=(vec.end()-2))
        {
            m_outputFile<<"DWORD\t"<<*it<<"\n";
            it++;
        }
    }
}
void CodeGeneration::CodeSegment()
{
    long FilePointerPosition=m_outputFile.tellg();

    m_outputFile<<". CODE "<<"\n";

    for(int i=0;i<m_ExpressionMatrix.size()-1;i++)
    {
        for(int j=0;j<m_ExpressionMatrix[i].size()-1;j++)
        {
            if(m_ExpressionMatrix[i][m_ExpressionMatrix[i].size()-1]=="func") // check Function or not
            {
                m_outputFile.seekg(std::ios::beg,m_outputFile.end);

                m_outputFile<<MakeFuncLabel(m_ExpressionMatrix[i][0])<<" : \n";

                addVariable(m_ExpressionMatrix[i][0],MakeFunctionCode(m_ExpressionMatrix[i][1]));

                m_outputFile.seekg(FilePointerPosition);
                break;
            }
            else
            {
                if(m_ExpressionMatrix[i].size()==2)
                {
                    m_outputFile<<"ASSIGN"<<"\t"<<m_mem.makeMemoryAddress()<<"\t"<<m_ExpressionMatrix[i][0]<<"\n";
                    addVariable(m_ExpressionMatrix[i][0],"00");
                }
                else
                {
                    VariableInit(m_ExpressionMatrix[i]);
                }
            }
        }
    }
}
std::string CodeGeneration::MakeFuncLabel(std::string const &str)
{
    std::string ret_str="";
    for(int i=0;i<str.size()-2;i++)
    {
        ret_str+=str[i];
    }
    return ret_str;
}
void CodeGeneration::VariableInit(std::vector<std::string> &vec)
{
    std::string result="";
    std::string memAddress=""; 
    while(vec.size()!=2)
    {
        memAddress=m_mem.makeMemoryAddress();
        static std::map<std::string,VarRegWrap>::iterator itToArdesses;
        itToArdesses= m_mem.MemoryAddress.find(*(vec.end()-3));

        if(itToArdesses==m_mem.MemoryAddress.end())
        {
            m_outputFile<<"ASSIGN \t"<<memAddress<<"\t"<<*(vec.end()-3)<<"\n";
            result=SolveMathExpression(*(vec.end()-2));
            m_outputFile<<"STORE\t"<<memAddress<<"\t"<<m_mem.m_emptyRegStack.top()<<"\n";
            m_mem.m_reserveRegStack.push(m_mem.m_emptyRegStack.top());
            m_mem.m_emptyRegStack.pop();
            addVariable(*(vec.end()-3),result);
            *(vec.end()-3)=result;
            vec.erase(vec.end()-2);
            VariableInit(vec);
        }
        else
        {
            result=SolveMathExpression(*(vec.end()-2));
            m_outputFile<<"STORE\t"<<itToArdesses->second.sm_VarAdress<<"\t"<<m_mem.m_emptyRegStack.top()<<"\n";
            m_mem.m_reserveRegStack.push(m_mem.m_emptyRegStack.top());
            m_mem.m_emptyRegStack.pop();
            itToArdesses->second.sm_VarValue=result;
            *(vec.end()-3)=result;
            vec.erase(vec.end()-2);
            VariableInit(vec);
        }
    }
}
std::string CodeGeneration::SolveMathExpression(std::string const & str)
{
    PostfixCalculator makePost;
    makePost.setExpression(str);

    std::vector<std::string > s_vec = makeMAthExpressionToVector(makePost.getPostfixNotation());

    for(int i=0;i<s_vec.size();i++)
    {
        if(int(s_vec[i][0])<=int('9') && int(s_vec[i][0])>=int('0'))
        {
            m_outputFile<<m_mem.regAssign(std::string(s_vec[i]))<<"\n";
        }
        else
        {
            if((int(s_vec[i][0])<=int('Z') && int(s_vec[i][0])>=int('A')) || (int(s_vec[i][0])<=int('z') && int(s_vec[i][0])>=int('a')))
            {
                if(LexicalAnalayser::IsFunc(s_vec[i]))
                {
                    m_outputFile<<"CALL\t"<<MakeFuncLabel(s_vec[i])<<"\n";
                    m_outputFile<<"LOAD\t"<<m_mem.m_reserveRegStack.top()<<"\t"<<getVarValue(s_vec[i]).sm_VarAdress<<"\n";
                    m_mem.m_emptyRegStack.push(m_mem.m_reserveRegStack.top());
                    m_mem.m_reserveRegStack.pop();
                }
                else
                {
                    m_outputFile<<"LOAD\t"<<m_mem.m_reserveRegStack.top()<<"\t"<<getVarValue(s_vec[i]).sm_VarAdress<<"\n";
                    m_mem.m_emptyRegStack.push(m_mem.m_reserveRegStack.top());
                    m_mem.m_reserveRegStack.pop();
                }
            }
            else
            {
                m_outputFile<<m_mem.regOperationCode(s_vec[i][0])<<"\n";
            }
        }
    }
    makePost.setExpression(changeVariableTovalue(str));

    std::stringstream out;
    out << int(makePost.getResult());
    
    return out.str();
}
std::string CodeGeneration::MakeFunctionCode(std::string const &str)
{
    std::string ret_str = SolveMathExpression(str);
    
    m_outputFile<<"RET"<<"\n";
    m_mem.clearStack();
    return ret_str;
}


std::vector<std::string > CodeGeneration::makeMAthExpressionToVector(std::string const &str)
{
    std::vector<std::string> vec;
    std::string s_temp;
    for(int i=0;i<str.size();i++)
    {
        s_temp="";
        while(str[i]!=' ' && i<str.size())
        {
            s_temp+=str[i];
            i++;
        }
        vec.push_back(s_temp);
    }
    return vec;
}

std::string  CodeGeneration::changeVariableTovalue(std::string const &str)
{
    std::string  ret_str="";
    std::string temp="";
    for(int i=0;i<str.size();i++)
    {
        if((int(str[i])>=int('A') && int(str[i])<=int('Z')) || (int(str[i])>=int('a') && int(str[i])<=int('z')))
        {
            temp="";
            while(str[i]!='+' && str[i]!='-' && str[i]!='/' && str[i]!='*' && i<str.size())
            {
                temp+=str[i];
                i++;
            }
            ret_str+=getVarValue(temp).sm_VarValue;
        }
        else
        {
            ret_str+=str[i];
        }
    }
    return ret_str;
}

void CodeGeneration::DividedInZeroValidation(const std::string &str) 
{
    std::vector<std::string> vec;
    std::string s_temp;
    for(int i=0;i<str.size();i++)
    {
        s_temp="";
        while(str[i]!=' ' && i<str.size())
        {
            s_temp+=str[i];
            i++;
        }
        vec.push_back(s_temp);
    }
    copy(vec.begin(),vec.end(),std::ostream_iterator<std::string>(std::cout,","));
    std::cout<<std::endl;
    for(int i=vec.size()-1;i>=2;i--)
    {
        s_temp="";
        
        if(vec[i].size()==1)
        {
            if(vec[i][0]=='/')
            {
                try
                {
                    if(vec.at(i-2).size()==1 && vec.at(i-2)[0]=='0')
                    {
                        std::cerr<<"ERROR \n Division by zero \n";
                        std::terminate();
                    }
                   
                }
                catch (const std::out_of_range& oor)
                {
                    std::cerr << "Invalid Math Expression:" << oor.what() << '\n';
                    std::terminate();
                }
            }
        }
        else
        {
            if(vec[i][0]=='0')
            {
                std::cerr<<"ERROR:\n Invalid Number: Number cannot started with 0 {"<<vec[i]<<"}\n";
                std::terminate();
            }
        }
    }
}

