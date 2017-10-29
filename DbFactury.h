#ifndef DBFACTURY_H  
#define DBFACTURY_H  
 
#include <string>
#include "IMyDB.h" 
#include "SQLiteDB.h" 

//namespace mydbmodule {  
  
class DbFactury
{  
public:  
    DbFactury();
    ~DbFactury();
    static SQLiteDB * Create(string);
};

//}
  
#endif // DBFACTURY_H 
