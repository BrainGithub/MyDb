#include <DBFactury.h>

using namespace std;
using namespace mydbmodule;  
  
mutex DBFactury::_mutex;  
DBFactury * DBFactury::_instance = NULL;  

DBFactury * DBFactury::GetInstance()  
{  
    if(NULL == _instance)  
    {  
         _mutex.lock();  
         if(NULL == _instance)  
         {  
             _instance = new DBFactury();  
         }  
         _mutex.unlock();  
     }  
    return _instance;  
}  
  
IMyDB * DBFactury::Create(string dbname)  
{  
    if (dbname = "SQLite3")
    {
        return SQLiteDB::GetInstance(dbfile,10);
    }
    else if (dbname == "MySql")
    {
        return MySqlDB::GetInstance(dbfile);
    }

    return NULL;
}  
  
DBFactury::DBFactury()  
{  
  
} 