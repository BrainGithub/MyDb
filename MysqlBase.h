#ifndef MYSQLBASE_H  
#define MYSQLBASE_H
  
#include <string.h>  
#include <iostream>  
  
#include <pthread.h>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mysql/mysql.h>
#include "IMyDB.h"  

using namespace std;  
  
typedef struct cfg
{
    string host;
    string user;
    string passwd;
    string dbName;
    string dbVer;
    int port;
} Cfg;

class MysqlQuery
{
public:
    MysqlQuery();
    MysqlQuery(MysqlQuery& rQuery);
    MysqlQuery& operator=(MysqlQuery& rQuery);
    virtual ~MysqlQuery();
    
    long numRows();
    int numFields();
    int fieldIndex(const char* szField);
    
    //0...n-1 collumn
    const char* fieldName(int nCol);
    //   const char* fieldDeclType(int nCol);
    //   int fieldDataType(int nCol);
    long seekRow(long offerset);
    int getIntField(int nField, int nNullValue=0);
    int getIntField(const char* szField, int nNullValue=0);
    double getFloatField(int nField, double fNullValue=0.0);
    double getFloatField(const char* szField, double fNullValue=0.0);
    //0...n-1列
    const char* getStringField(int nField, const char* szNullValue="");
    const char* getStringField(const char* szField, const char* szNullValue="");
    const unsigned char* getBlobField(int nField, int& nLen);
    const unsigned char* getBlobField(const char* szField, int& nLen);
    bool fieldIsNull(int nField);
    bool fieldIsNull(const char* szField);
    bool eof();
    void nextRow();
    void finalize();
private:
    void freeRes();
private:
    MYSQL_RES*  _mysql_res;
    MYSQL_FIELD* _field;
    MYSQL_ROW  _row;
    long   _row_count;
    int   _field_count;

};


class MysqlBase : public IMyDB
{  
public:  
    MysqlBase();  

    void* open(Cfg * cfg);  
    void close(void *db);  
  
    bool startTransaction(void *db);  
    bool commitTransaction(void *db);  
    bool rollbackTransaction(void *db);  
  
    int exec(void *db,const string &sql);  
  
    MysqlQuery& query(void *db,const string &sql);    
  
private:  
    pthread_mutex_t _lock;  
};  
  

#endif //MYSQLBASE_H 

