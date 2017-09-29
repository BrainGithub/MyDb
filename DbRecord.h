#ifndef DBRECORD_H  
#define DBRECORD_H  
  
#include <list>  
#include "SqliteBase.h"  
#include "dbmanager.h"  

namespace mydbmodule {  
  
class DBRecord : public SqliteBase  
{  
public:  
    static DBRecord* GetInstance(const string &pDBName, int version = 0);  
  
private:  
    DBRecord(const string &dbName, const string &pPath, int version);  
	
private:  
    mutex lock;  
    const string _msgRecordTblName;  
    string _strDbName;  
	
	list<void *> _db_conn_busy;
	list<void *> _db_conn_idle;
	pthread_t _db_pool_id;
	
	void db_pool_task();
  
    static mutex m_mutex;  
  
    class CGarbo  
    {  
    public:  
        ~CGarbo()  
        {  
            if (DBRecord::instance)  
            {  
                delete DBRecord::instance;  
                DBRecord::instance = NULL;  
            }  
        }  
    };  
    static CGarbo Garbo;  
  
    static DBRecord* instance;  
};  
  
#define DBManag DBManager::GetInstance()  
}  
  
#endif // DBRECORD_H 