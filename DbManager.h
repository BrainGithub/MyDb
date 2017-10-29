#ifndef DBMANAGER_H  
#define DBMANAGER_H  
  
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "DbFactury.h"
//namespace mydbmodule {  
using namespace std;
  
class DbManager  
{  
public:  
    static DbManager* Instance();  
  
    SQLiteDB *GetDB();  
private:  
    class CGarbo 
    {
    public:
    ~CGarbo()
    {  
        if (DbManager::instance)  
        {  
            delete DbManager::instance;  
        }  
    }  
    };  
    static CGarbo Garbo; 
    static DbManager* instance;
    static pthread_mutex_t mutex;  
    SQLiteDB * mydb;

    DbManager();  
    ~DbManager();  
};  
  
//}  
  
#endif // DBMANAGER_H  
