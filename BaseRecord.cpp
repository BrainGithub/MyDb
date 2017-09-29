

class BaseRecord : public IRecord
{
public:
    string tableName;
    bool update = false;
    IMyDB * _mydb;
private:
    DBManager * _dbm;
    
}

BaseRecord::BaseRecord
{
    _dbm = DBManager::GetInstance();
    if (_dbm == NULL)
    {
        printf("DBManager::GetInstance failed\n");
    }
    else
        _mydb = _dbm->GetDB();
}