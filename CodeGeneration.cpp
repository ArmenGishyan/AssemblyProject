#include "CodeGeneration.h"


typedef std::pair<std::string,VarRegWrap> pair_type;


CodeGeneration::CodeGeneration(std::string s_OutfileName,std::string s_InFileName)
{
    m_inputFile.open(s_InFileName.c_str(),std::ios::in); 
    assert(m_inputFile.is_open()); 
    
    m_outputFile.open(s_OutfileName.c_str(),std::ios::out);
    assert(m_outputFile.is_open());
}
CodeGeneration::~CodeGeneration()
{
    m_outputFile.close();
    m_inputFile.close();
}
void CodeGeneration::ReadFromFile()
{   
    // = operatori tex@ fixelu hamar
    int operatorIndex=0;
    std::string s_expresion="  ";
   
    Memory mem_obj;
    
    while(!m_inputFile.eof())
    {
        
        getline(m_inputFile,s_expresion);
        
        operatorIndex=0;
        

        if(!SemanticAnalyzer::isFunction(s_expresion,operatorIndex))
        {
            std::string str_expresion = makeMathExpresion(s_expresion,operatorIndex);
            m_C_object.setExpression(str_expresion);
            std::string str_postfix =m_C_object.getPostfixNotation();
            
            for(int i=0;i<str_postfix.size();i++)
            {
                if(int(str_postfix[i])<=int('9') && int(str_postfix[i])>=int('0'))
                {
                    m_outputFile<<mem_obj.regAssign(std::string(1,str_postfix[i]))<<"\n";
                }
                else
                {
                    m_outputFile<<mem_obj.regOperationCode(str_postfix[i])<<"\n";
                }
                
            }
           
           m_outputFile<<"STORE\t"<<mem_obj.m_emptyRegStack.top()<<'\t'<<makeMemoryAddress()<<"\n";
           mem_obj.m_reserveRegStack.push(mem_obj.m_emptyRegStack.top());
           mem_obj.m_emptyRegStack.pop();
           addVariable(makeVaribleName(s_expresion,operatorIndex),std::string(1,m_C_object.getResult()));
        }
        else
        {
            std::string str_expresion = makeMathExpresion(s_expresion,operatorIndex);
            m_C_object.setExpression(str_expresion);
            std::string str_postfix =m_C_object.getPostfixNotation();
            
            m_outputFile<<makeFunctionName(s_expresion)<<":\n";
          
            
            for(int i=0;i<str_postfix.size();i++)
            {
                if(int(str_postfix[i])<=int('9') && int(str_postfix[i])>=int('0'))
                {
                    m_outputFile<<mem_obj.regAssign(std::string(1,str_postfix[i]))<<"\n";
                }
                else
                {
                   m_outputFile<<mem_obj.regOperationCode(str_postfix[i])<<"\n";
                }
            }
            m_outputFile<<"RET\n";
        }
        
    }
    
      DataSegment();

   
}
void CodeGeneration::DataSegment()
{  
     m_outputFile.seekg(std::ios::beg);
    m_outputFile<<".Data\n";
    std::map<std::string,VarRegWrap>::iterator it=MemoryAddress.begin();
    while(it!=MemoryAddress.end())
    {
        m_outputFile<<"DWORD\t"<<it->first<<"\n";
        it++;
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
    VarRegWrap obj(makeMemoryAddress(),varValue);
    MemoryAddress.insert(MemoryAddress.begin(),pair_type(varName,obj));
}
std::string CodeGeneration::getVarValue(const std::string &varName)
{
    return MemoryAddress[varName].sm_VarValue;
}
std::string CodeGeneration::makeFunctionName(std::string const &s_str)
{
    std::string s_funcName="";
    int index=0;
    while(s_str[index]!='(' && index<s_str.size())
    {
        s_funcName+=s_str[index];
        index++;
    }
    return s_funcName;
}
std::string CodeGeneration::makeMemoryAddress()
{
    static int count=0;
    
    std::stringstream out;
    out << int(count/2);
    count++;
    return ("A"+out.str());
}
 
