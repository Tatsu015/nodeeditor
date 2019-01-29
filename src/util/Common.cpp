#include "Common.h"


QString btos(bool value)
{
    if(value){
        return "true";
    }
    return "false";
}

bool stob(const QString& value)
{
    if("false" == value){
        return false;
    }
    return true;
}
