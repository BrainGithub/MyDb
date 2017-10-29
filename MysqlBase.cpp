#include "MysqlBase.h"   
  
  
MysqlBase::MysqlBase()  
{  
}  
  
void * MysqlBase::open(Cfg * cfg)  
{  
    MYSQL * mysql = 0;
    string host = cfg->host;
    string user = cfg->user;
    string passwd = cfg->passwd;
    string dbName = cfg->dbName;
    string dbVer = cfg->dbVer;
    int port = cfg->port;

    mysql_init(mysql);
    
    //assert
    if(dbName.empty())// || dbVer < 0)  
    {
        cout << "Param error: host=" << host
            << ",user=" << user
            << ",passwd=" << passwd
            << ",dbName=" << dbName
            << ",dbVer=" << dbVer
            << ",port=" << port << endl;
        //errMsg.append(PublicFunction::IntToString(version));  
        printf("[mysql] MysqlBase open failed\n");  
        return NULL;  
    }   
  
    if(NULL == mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, NULL, 0))
    {
        fprintf(stderr, "[mysql] error:%d, %s\n",
            mysql_errno(mysql),
            mysql_error(mysql));


        return NULL;  
    }   
  
    return mysql;  
}

void MysqlBase::close(void *p)  
{  
    mysql_close((MYSQL*)p);  
    p = NULL;  
}   
  
bool MysqlBase::startTransaction(void *p)  
{  
    string tran = "START TRANSACTION";
    MYSQL * mysql = (MYSQL *)p;

    if(mysql_real_query(mysql, tran.c_str(), tran.length()))
    {
        //return error
        fprintf(stderr, "[mysql] error:%d, %s\n",
            mysql_errno(mysql),
            mysql_error(mysql));

        return false;
    }

    return true;
}  
  
bool MysqlBase::commitTransaction(void *p)  
{  
    string tran = "COMMIT";
    MYSQL * mysql = (MYSQL *)p;

    if(mysql_real_query(mysql, tran.c_str(), tran.length()))
    {
        //return error
        fprintf(stderr, "[mysql] error:%d, %s\n",
            mysql_errno(mysql),
            mysql_error(mysql));

        return false;
    }

    return true;
}  
  
bool MysqlBase::rollbackTransaction(void *p)  
{
    string tran = "ROLLBACK";
    MYSQL * mysql = (MYSQL *)p;

    if(mysql_real_query(mysql, tran.c_str(), tran.length()))
    {
        //return error
        fprintf(stderr, "[mysql] error:%d, %s\n",
            mysql_errno(mysql),
            mysql_error(mysql));

        return false;
    }

    return true;
}  
  
int MysqlBase::exec(void *p, const string &sql)  
{  
    MYSQL * mysql = (MYSQL *)p;

    if (!mysql_real_query ( mysql , sql.c_str() , sql.length()))  
    {
        return (int)mysql_affected_rows(mysql);      
    }
    else
    {   
        fprintf(stderr, "[mysql] error:%d, %s\n",
            mysql_errno(mysql),
            mysql_error(mysql));

        return -1;
    }  
}  
  
MysqlQuery * MysqlBase::query(void *p, const string &sql)  
{  
    MysqlQuery query;  
    MYSQL * mysql = (MYSQL *)p;

    //start exec query  
    if (mysql_real_query( mysql , sql.c_str(), sql.length()))  
    {  
        //failed
        fprintf(stderr, "[mysql] error:%d, %s\n",
            mysql_errno(mysql),
            mysql_error(mysql));
        return query;
    }  

    query._mysql_res = mysql_store_result( mysql );
    
    return query;  
}

