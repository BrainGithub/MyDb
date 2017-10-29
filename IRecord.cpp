#include "IRecord.h"


IRecord::IRecord()
{
    insert = true;

    _dbm = DbManager::Instance();
    if (_dbm == NULL)
    {
        printf("IRecord DBManager::GetInstance failed\n");
    }
    else
        mydb = _dbm->GetDB();
}

IRecord::~IRecord()
{
}

bool IRecord::IsNullOrEmpty(string str)
{
    //if (str == NULL)
    //    return true;
    if (str == "")
        return true;
    return false;
}

string IRecord::Int2Str(int data)
{
    char str[256];
    string temp;
    snprintf(str, sizeof(str), "%d", data);
    temp.append(str);
    return temp;
}
