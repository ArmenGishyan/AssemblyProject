#include "SemanticAnalysis.h"

bool SemanticAnalyzer::isFunction(std::string s_str,int &indexOfOperator)
{

   for(int i=0;i<s_str.size()-2;i++)
   {
       if(s_str[i]=='(' && s_str[i+1]==')' && s_str[i+2]=='=')
       {
            indexOfOperator=i+2;
            return true;
       }
       if(s_str[i]=='=')
       {
           indexOfOperator=i;
       }
   }
   return false;


}