#ifndef IMYDB_H
#define IMYDB_H

using namespace std;  

class IMyDB
{
public:
    virtual void * Open(){};
    virtual void Close(void *){};
};
#endif
