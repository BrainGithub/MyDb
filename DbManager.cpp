#include "DbManager.h"  
  
//using namespace mydbmodule;  
  
pthread_mutex_t DbManager::mutex = PTHREAD_MUTEX_INITIALIZER;
DbManager::CGarbo DbManager::Garbo;  
DbManager* DbManager::instance = NULL;  
  
DbManager *DbManager::Instance()  
{  
    if(NULL == instance)  
    {  
         pthread_mutex_lock(&mutex);  
         if(NULL == instance)  
         {  
             instance = new DbManager();  
         }  
         pthread_mutex_unlock(&mutex);  
     }  
    return instance;  
}  
  
SQLiteDB * DbManager::GetDB()  
{  
    return mydb;  
}  
  
DbManager::DbManager()  
{  
    printf("in DbManager::DbManager()\n");
    
    printf("DbFactury::Create SQLite3 start\n");
    mydb = DbFactury::Create("SQLite3");
    printf("DbFactury::Create SQLite3 end\n");
}  

DbManager::~DbManager()
{
    printf("in DbManager::~DbManager()\n");
    //delete mydb;
}
