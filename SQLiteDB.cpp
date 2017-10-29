#include "SQLiteDB.h"  
  
  
//using namespace mydbmodule;  
  
pthread_mutex_t SQLiteDB::_mutex = PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t SQLiteDB::_mutex_instance = PTHREAD_MUTEX_INITIALIZER;  
SQLiteDB* SQLiteDB::instance = NULL;  
SQLiteDB::CGarbo SQLiteDB::Garbo;  
  
SQLiteDB* SQLiteDB::GetInstance(const string &pDBName, int version = 0)  
{  
    if(NULL == instance)  
    {  
        pthread_mutex_lock(&_mutex_instance);
        if(NULL == instance)  
        {  
            instance = new SQLiteDB(pDBName, version);  
        }  
        pthread_mutex_unlock(&_mutex_instance);
    }  
    return instance;  
}  
  
SQLiteDB::SQLiteDB(const string &dbName, int version):  
    SqliteBase(dbName, version)  
{  
    printf("in SQLiteDB::SQLiteDB()\n");
    //build connection pool
    createConnPool();
    printf("%s,%d\n", __FILE__, __LINE__);
}   

SQLiteDB::~SQLiteDB()
{
    int n=0;
    //destroy all connections
    destroyConnPool();
    printf("in SQLiteDB::~SQLiteDB()\n");
}

void SQLiteDB::createConnPool()
{
    //int ret;
    int count = 10;
    sqlite3 * db;
    
    pthread_mutex_lock(&_mutex);
    for (int i=0; i<count; i++)
    {
        db = (sqlite3 *)OpenDB();
        if (db == NULL)
        {
            pthread_mutex_unlock(&_mutex);
            printf("Error: open db failed\n");
            return;
        }
        _db_conn_idle.push_back(db);
    }
    pthread_mutex_unlock(&_mutex);
    
    printf("create %d SQLite connections\n", count);

    //ret = pthread_create(&_db_pool_id, NULL, db_pool_task, NULL);
    //if (ret == 0)
    //{
    //    printf("build db connectoin pool task failed");
    //}
    
    return;
}

void SQLiteDB::destroyConnPool()
{
    int nbusy = 0;
    int nidle = 0;
    void * db = NULL;

    while (!_db_conn_busy.empty()){
        pthread_mutex_lock(&_mutex);

        if (_db_conn_busy.empty()){
            pthread_mutex_unlock(&_mutex);
            continue;
        }   
        db = _db_conn_busy.front();
        _db_conn_busy.pop_front();

        pthread_mutex_unlock(&_mutex);

        CloseDB((sqlite3 *)db);
        nbusy++;
    }   


    while (!_db_conn_idle.empty()){
        pthread_mutex_lock(&_mutex);

        if (_db_conn_idle.empty()){
            pthread_mutex_unlock(&_mutex);
            continue;
        }
        db = _db_conn_idle.front();
        _db_conn_idle.pop_front();

        pthread_mutex_unlock(&_mutex);

        CloseDB((sqlite3 *)db);
        nidle++;
    }

    printf("closed all opened %d db connections:busy:%d, idle:%d\n", 
            nbusy+nidle, nbusy, nidle);

}

void SQLiteDB::db_pool_task(void)
{
    while (true)
    {
        sleep(2);        
        printf("db pool task\n");
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

bool SQLiteDB::Exec(const string sql)
{
    bool ret;
    void *db = Open();
    ret = SqliteBase::Exec((sqlite3 *)db, sql);
    Close(db);

    return ret;
}


Result * SQLiteDB::Query(const string sql)  
{
    void *db = Open();
    Result * p = NULL;
    p = SqliteBase::Query((sqlite3 *)db, sql);
    Close(db);
    return p;
}


