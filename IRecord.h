#ifndef IRECORD_H  
#define IRECORD_H 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DbManager.h"

class IRecord 
{
public:
    IRecord();
    ~IRecord();
    bool Save(void);
    bool Find( void * data);
    bool Del(void);

public:
    string tableName;
    bool insert;
    SQLiteDB * mydb;
protected:
    bool IsNullOrEmpty(string);
    string Int2Str(int);
private:
    DbManager * _dbm;
    
};

#endif
