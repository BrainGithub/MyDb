#include "dbchatrecord.h"  
  
#include <strstream>  
  
using namespace mydbmodule;  
  
mutex DBRecord::m_mutex;  
DBRecord* DBCRecord::instance = NULL;  
DBRecord::CGarbo DBRecord::Garbo;  
  
DBRecord* DBRecord::GetInstance(const string &pDBName, int version = 0)  
{  
    if(NULL == instance)  
    {  
        m_mutex.lock();
        if(NULL == instance)  
        {  
            instance = new DBRecord(pDBName, version);  
        }  
        m_mutex.unlock();
    }  
    return instance;  
}  
  
DBRecord::DBRecord(const string &dbName, int version):  
    SqliteBase(dbName, version),  
    m_msgRecordTblName("TBL_RECORD"),  
    m_strDbName(dbName)  
{  
	//build connection pool
}   
 
DBRecord::createConnPool()
{
	int ret;
	
	ret = pthread_create(&_db_pool_id, NULL, db_pool_task, NULL);
	
	if (ret == NULL)
	{
		printf("build db connectoin pool failed");
	}
	
	return;
}

DBRecord::db_pool_task(void)
{
	int count = 10;
	
	m_mutex.lock();
	
	for (int i=0; i<count; i++)
	{
		db = Open();
		if (db == NULL)
		{
			m_mutex.unlock();
			printf("Error: open db failed\n");
			return;
		}
		_db_conn_idle.push_back(db);
	}
	
	m_mutex.unlock();
	
	// need to implemented
	while (true)
	{
		
	}
}

sqlite3 * DBRecord::Open()
{
	sqlite3 * db = NULL;
	
	m_mutex.lock();
	
	if (_db_conn_idle.empty()){
		m_mutex.unlock();
		printf("Warning: no idle db connection return;\n");
		return NULL;
	}
	db = _db_conn_idle.front();
	_db_conn_idle.pop_front();
	_db_conn_busy.push_back(db);
	
	m_mutex.unlock();
	
	return db;
}

DBRecord::Close(sqlite3 * db)
{
	m_mutex.lock();
	
	_db_conn_busy.remove(db)
	_db_conn_idle.push_back(db);
	
	m_mutex.unlock();
	
	return;
}
 
