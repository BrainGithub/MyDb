#ifndef DBFACTURY_H  
#define DBFACTURY_H  
 
#include <IMyDB> 
#include <string>

namespace mydbmodule {  
  
class DBFactury
{  
public:  
    static DBFactury * GetInstance();
    IMyDB * Create(string);
  
	
private:  
    pthread_mutex_t _mutex;  
    static DBFactury * _instance;  
};

}
  
#endif // DBFACTURY_H 
