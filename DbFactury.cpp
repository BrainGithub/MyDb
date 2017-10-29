#include "DbFactury.h"

using namespace std;
//using namespace mydbmodule;  
  

SQLiteDB * DbFactury::Create(string dbtype)  
//void * DbFactury::Create(string dbname)  
{  
    if (dbtype == "SQLite3")
    {
        printf("SQLiteDB::GetInstance(motion.db,10)\n");
        return SQLiteDB::GetInstance("motion.db",1);
    }
    else if (dbtype == "MySql")
    {
        //return MySqlDB::GetInstance(dbname); 
    }

    return NULL;
}  
  
DbFactury::DbFactury()  
{  
  
} 

