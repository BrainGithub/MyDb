#ifndef DBMANAGER_H  
#define DBMANAGER_H  
  
namespace mydbmodule {  
  
class DBManager  
{  
public:  
    static DBManager* GetInstance();  
  
    void *GetDB();  
private:  
    class CGarbo // 它的唯一工作就是在析构函数中删除ReceiveMsgManagerThread的实例  
    {  
    public:  
        ~CGarbo()  
        {  
            if (DBManager::_instance)  
            {  
                delete DBManager::instance;  
            }  
        }  
    };  
    static CGarbo Garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数  
    static DBManager* instance;  

    static mutex g_mutex;  

    DBFactury * _dbfactury;
  
    DBManager();  
};  
  
}  
  
#endif // DBMANAGER_H  
