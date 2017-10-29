#ifndef MYSQLQUERY_H  
#define MYSQLQUERY_H

#include <mysql/mysql.h>
#include "MysqlBase.h"

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

#endif
