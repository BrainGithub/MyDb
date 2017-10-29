#ifndef SqliteBase_H  
#define SqliteBase_H  
  
#include <string.h>  
#include <iostream>  
  
#include <pthread.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sqlite3.h> 
#include "IMyDB.h"  

using namespace std;  
  

typedef struct qureyResult  
{  
    int nRow;  
    int nColumn;  
    int nIndex;  
    char** pResult;  
    qureyResult(int row, int column, char**p)  
    {  
        nRow = row;  
        nColumn = column;  
        pResult = NULL;  
        nIndex = 0;  
        if(nRow > 0)  
        {  
            pResult = p;  
        }  
    }  
    ~qureyResult()  
    {  
        if(pResult)  
        {  
            sqlite3_free_table(pResult);  
        }  
    }  

    bool next()  
    {  
        if(nIndex == 0)  
        {  
            if(nRow > 0)  
            {  
                ++nIndex;  
                return true;  
            }else{  
                return false;  
            }  
        }else{  
            if((nRow*nColumn) >= ((nIndex+1)*nColumn))  
            {  
                ++nIndex;  
                return true;  
            }else{  
                return false;  
            }  
        }  
    }  

    char* value(const char *pColumnName)  
    {  
        int index = nIndex*nColumn;  
        for(int i = 0; i < nColumn; ++i)  
        {  
            if(strcmp(pColumnName,pResult[i]) == 0)  
            {  
                return pResult[index];  
            }  
            ++index;  
        }  
        return NULL;  
    }  
} Result;  
  
class SqliteBase : public IMyDB
{  
public:  
    SqliteBase(const string &pDBName, int pVersion = 1);  

    sqlite3* OpenDB();  
    void CloseDB(sqlite3 *p);  
  
    bool transaction(sqlite3 *p);  
    bool commitTransaction(sqlite3 *p);  
    bool rollbackTransaction(sqlite3 *p);  
  
    bool Exec(sqlite3 *p,const string &sql);  
  
    Result *Query(sqlite3 *p,const string &sql);    
  
private:  
    string dbName;  
    int version;  
  
    pthread_mutex_t m_lock;  
};  
  

#endif // SqliteBase_H  
