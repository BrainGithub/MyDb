#include "DbFactury.h"

using namespace std;
//using namespace mydbmodule;  
  

IMyDB * DbFactury::Create(string dbname)  
{  
    if (dbname == "SQLite3")
    {
        return SQLiteDB::GetInstance(dbfile,10);
    }
    else if (dbname == "MySql")
    {
        return MySqlDB::GetInstance(dbfile);
    }

    return NULL;
}  
  
DbFactury::DbFactury()  
{  
  
} 
