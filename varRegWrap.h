#include <string>

class VarRegWrap
{
  public:  std::string sm_VarAdress;
            std::string sm_VarValue;
    VarRegWrap(std::string VarAdress,std::string VarValue)
    {
        sm_VarAdress=VarAdress;
        sm_VarValue=VarValue;
    }
    VarRegWrap()
    {
        sm_VarAdress="";
        sm_VarValue="";
    }
    VarRegWrap(const VarRegWrap &obj)
    {
        sm_VarAdress=obj.sm_VarAdress;
        sm_VarValue=obj.sm_VarValue;
    }

};
