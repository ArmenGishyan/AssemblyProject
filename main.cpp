#include <iostream>
//#include "varRegWrap.h"
#include <map>
#include <string>
#include <iterator>
#include <fstream>
#include "postfixcalculator.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
//#include <algorithm>


void addMinusOperator(std::string &str)
{
    std::string::iterator it=str.begin();
    str+='\0';
    if(*it=='-') 
    {
        str.insert(it,'0');
        it++;
        it++;
    }

    while(*it!='\0')
    {
        if(*it=='-' && !(int(*(it-1))<=int('9') && int(*(it-1))>=int('0')) && !((int(*(it-1))<=int('z') && int(*(it-1))>=int('a'))) )
        {
            str.insert((it),'0');
            
        }
        std::cout<<*it<<std::endl;
        it++;
        
    }
    str.erase(--str.end());
    
}

std::vector<std::string> DividedInZeroValidation(std::string str)
{
    std::vector<std::string> vec;
    std::string s_temp;
    std::vector<std::string> makableVec;
    std::cout<<"gg"<<str<<"\n";
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
                    if(vec.at(i-1).size()==1 && vec.at(i-1)[0]=='0')
                    {
                        std::cerr<<"ERROR \n Division by zero \n";
                        std::terminate();
                    }
                    else
                    {
                        makableVec.push_back(vec[i]);
                    }
                }
                catch (const std::out_of_range& oor)
                {
                    std::cerr << "Invalid Math Expression:" << oor.what() << '\n';
                    std::terminate();
                }
            }
            else
            {
                if(vec[i]=="-" && vec[i-2]=="0")
                {
                    s_temp+="-";
                    s_temp+=vec[i-1];
                    makableVec.push_back(s_temp);
                    i-=2;
                }
                else
                {
                    makableVec.push_back(vec[i]);
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
            else
            {
                makableVec.push_back(vec[i]);
                std::cout<<"he";
            }
        }
    }
    std::reverse(makableVec.begin(),makableVec.end());
    return makableVec;
    
}


int main()
{
    PostfixCalculator obj;
    std::string str="aA()*var2";
    //addMinusOperator(str);
    //std::cout<<"add-:"<<str<<"\n";
   // addMinusOperator(str);
    obj.setExpression(str);
    std::cout<<obj.getPostfixNotation();

    //std::vector<std::string> cc = DividedInZeroValidation(obj.getPostfixNotation());
    //copy(cc.begin(),cc.end(),std::ostream_iterator<std::string>(std::cout,","));
    //std::cout<<obj.getResult();



    
    return 0;
}
