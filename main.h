#include <iostream>
#include "varRegWrap.h"
#include <map>
#include <string>
#include <iterator>

using namespace std;

int main()
{
    map<string,VarRegWrap> obj;

    VarRegWrap objvv("A1","12");
    obj.insert(obj.begin(),pair<string,VarRegWrap>("var1",objvv));
    map<string,VarRegWrap>::iterator it = obj.begin();
    cout<<it->second.sm_VarAdress;
    return 0;
}
