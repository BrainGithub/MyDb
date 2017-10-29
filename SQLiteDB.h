#ifndef DBRECORD_H  
#define DBRECORD_H  
  
#include <list>  
#include "SqliteBase.h"  

//namespace mydbmodule {  
  
class SQLiteDB : public SqliteBase 
{  
public: 
    SQLiteDB(const string &pDBName, int vresion);
        static SQLiteDB* GetInstance(const string &pDBName, int version);  
    void * Open();
    void Close(void *);
    bool Exec(const string sql);
    Result * Query(const string sql);
    
private:  
    //const string _msgRecordTblName;  
    //string _strDbName;
    
    list<void *> _db_conn_busy;
    list<void *> _db_conn_idle;
    pthread_t _db_pool_id;
    
    void createConnPool();
    void destroyConnPool();
    void db_pool_task();
  
    static pthread_mutex_t _mutex_instance;  
    static pthread_mutex_t _mutex;  
  
    ~SQLiteDB();
    class CGarbo  
    {  
    public:  
        ~CGarbo()  
        {  
            if (SQLiteDB::instance)  
            {  
                delete SQLiteDB::instance;  
                SQLiteDB::instance = NULL;  
            }  
        }  
    };  
    static CGarbo Garbo;  
  
    static SQLiteDB* instance;  
};  
  
//}  
  
#endif // DBRECORD_H 
