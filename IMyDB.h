
using namespace std;  
  
 

class IMyDB
{
public:
    virtual void * Open(){};
    virtual void Close(void *){};
};
