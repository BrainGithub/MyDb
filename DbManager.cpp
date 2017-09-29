#include "dbmanager.h"  
#include "dbchatrecord.h"  
#include <vector>  
  
using namespace mydbmodule;  
  
mutex DBManager::g_mutex;  
DBManager::CGarbo DBManager::Garbo;  
DBManager* DBManager::instance = nullptr;  
  
DBManager *DBManager::GetInstance()  
{  
    if(NULL == instance)  
    {  
         g_mutex.lock();  
         if(NULL == instance)  
         {  
             instance = new DBManager();  
         }  
         g_mutex.unlock();  
     }  
    return instance;  
}  
  
void * DBManager::GetDB()  
{  
    return _mydb;  
}  
  
DBManager::DBManager()  
{  
    _mydb = DBFactury::GetInstance()->Create("SQLite3");
}  
