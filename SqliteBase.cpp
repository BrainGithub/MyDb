#include "SqliteBase.h"   
  
//using namespace mydbmodule;  
  
SqliteBase::SqliteBase(const string &pDBName, int pVersion)  
{  
    this->dbName = pDBName;
    this->version = pVersion;
}  
  
sqlite3* SqliteBase::OpenDB()  
{  
    string dbstr = dbName;  
    sqlite3 *pSqlite = NULL;
    
    //assert
    if(dbName.empty() || version < 0)  
    {
        string errMsg;  
        errMsg.append("Param error dbName=");  
        errMsg.append(dbName);   
        errMsg.append(",version=");  
        //errMsg.append(PublicFunction::IntToString(version));  
        printf("[sqlite] SqliteBase open :%s",errMsg.c_str());  
        return NULL;  
    }   
  
    int nRes = sqlite3_open(dbstr.c_str(), &pSqlite);  
    if (nRes != SQLITE_OK)  
    {    
        printf("Open database fail:%s",sqlite3_errmsg(pSqlite));  
        return NULL;  
    }   
  
    return pSqlite;  
}

void SqliteBase::CloseDB(sqlite3 *p)  
{  
    sqlite3_close(p);  
    p = NULL;  
}   
  
bool SqliteBase::transaction(sqlite3 *p)  
{  
    int result = true;  
    char *errMsg = NULL;  
    int ret = sqlite3_exec (p, "begin transaction" , 0 , 0 , &errMsg ); // 开始一个事务  
    if(ret != SQLITE_OK)  
    {  
        printf("start transaction failed:%s",errMsg);  
        result = false;  
    }  
    sqlite3_free(errMsg);  
    return result;  
}  
  
bool SqliteBase::commitTransaction(sqlite3 *p)  
{  
    int result = true;  
    char *errMsg = NULL;  
    int ret = sqlite3_exec ( p , "commit transaction" , 0 , 0 , & errMsg );  
    if(ret != SQLITE_OK)  
    {  
        printf("commit transaction failed:%s",errMsg);  
        result = false;  
    }  
    sqlite3_free(errMsg);  
    return result;  
}  
  
bool SqliteBase::rollbackTransaction(sqlite3 *p)  
{  
    int result = true;  
    char *errMsg = NULL;  
    int ret = sqlite3_exec ( p , "rollback transaction" , 0 , 0 , & errMsg );  
    if(ret != SQLITE_OK)  
    {  
        printf("rollback transaction failed:%s",errMsg);  
        result = false;  
    }  
    sqlite3_free(errMsg);  
    return result;  
}    
  
bool SqliteBase::Exec(sqlite3 *p, const string &sql)  
{  
    bool result = true;  
    char *errMsg = NULL;  
    int  ret = sqlite3_exec ( p , sql.c_str() , 0 , 0 , & errMsg );  
    if(ret != SQLITE_OK)  
    {   
        printf("[sqlite] SqliteBase Update error:dbName=%s,msg=%s sql:%s",dbName.c_str(),errMsg,sql.c_str());  
        result = false;  
    }  
    sqlite3_free(errMsg);  
    return result;  
}  
/*
bool SqliteBase::Exec(const string &sql)  
{  
    bool result = true;  
    char *errMsg = NULL;  
    sqlite3 * p = Open();
    int  ret = sqlite3_exec ( p , sql.c_str() , 0 , 0 , & errMsg );  
    if(ret != SQLITE_OK)  
    {   
        printf("[sqlite] SqliteBase Update error:dbName=%s,msg=%s sql:%s",dbName.c_str(),errMsg,sql.c_str());  
        result = false;  
    }  
    sqlite3_free(errMsg);  
    return result;  
}  
*/ 
  
Result *SqliteBase::Query(sqlite3 *p, const string &sql)  
{  
    Result *pRe = NULL;  
    char *errmsg = NULL;  
    char **dbResult;  
    int nRow = 0;  
    int nColumn = 0;  
 
    //start exec query  
    int result = sqlite3_get_table(p, sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg );  
    if(result == SQLITE_OK)  
    {  
        printf("nRow:%d, nColumn:%d\n", nRow, nColumn);
        pRe = new Result(nRow,nColumn,dbResult);  
    }else{  
        printf("[sqlite] SqliteBase Query error:dbName=%s,msg=%s sql:%s\n",dbName.c_str(),errmsg,sql.c_str());  
    }  
    //free memory  
    sqlite3_free(errmsg);  
    return pRe;  
}

