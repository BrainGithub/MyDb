#include "SQLiteDB.h"  
  
  
//using namespace mydbmodule;  
  
pthread_mutex_t SQLiteDB::_mutex = PTHREAD_MUTEX_INITIALIZER;  
SQLiteDB* SQLiteDB::instance = NULL;  
SQLiteDB::CGarbo SQLiteDB::Garbo;  
  
SQLiteDB* SQLiteDB::GetInstance(const string &pDBName, int version = 0)  
{  
    if(NULL == instance)  
    {  
        pthread_mutex_lock(&_mutex);
        if(NULL == instance)  
        {  
            instance = new SQLiteDB(pDBName, version);  
        }  
        pthread_mutex_unlock(&_mutex);
    }  
    return instance;  
}  
  
SQLiteDB::SQLiteDB(const string &dbName, int version):  
    SqliteBase(dbName, version)  
{  
	//build connection pool
}   
 
void SQLiteDB::createConnPool()
{
	int ret;
	
	//ret = pthread_create(&_db_pool_id, NULL, db_pool_task, NULL);
	
	if (ret == 0)
	{
		printf("build db connectoin pool failed");
	}
	
	return;
}

void SQLiteDB::db_pool_task(void)
{
	int count = 10;
	sqlite3 * db;

	pthread_mutex_lock(&_mutex);
	
	for (int i=0; i<count; i++)
	{
		db = (sqlite3 *)Open();
		if (db == NULL)
		{
			pthread_mutex_unlock(&_mutex);
			printf("Error: open db failed\n");
			return;
		}
		_db_conn_idle.push_back(db);
	}
	
	pthread_mutex_unlock(&_mutex);
	
	// need to implemented
	while (true)
	{
		
	}
}

void * SQLiteDB::Open()
{
	void * db = NULL;
	
	pthread_mutex_lock(&_mutex);
	
	if (_db_conn_idle.empty()){
		pthread_mutex_unlock(&_mutex);
		printf("Warning: no idle db connection return;\n");
		return NULL;
	}
	db = _db_conn_idle.front();
	_db_conn_idle.pop_front();
	_db_conn_busy.push_back(db);
	
	pthread_mutex_unlock(&_mutex);
	
	return db;
}

void SQLiteDB::Close(void * db)
{
	pthread_mutex_lock(&_mutex);
	
	_db_conn_busy.remove(db);
	_db_conn_idle.push_back(db);
	
	pthread_mutex_unlock(&_mutex);
	
	return;
}
 
