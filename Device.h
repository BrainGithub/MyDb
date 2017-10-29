#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <list>
#include "IRecord.h"

using namespace std;


class Device : public IRecord
{
public:
    typedef struct {
        string id;
        string siteid;
        string device_type;
        string create_date;
        string update_date;
        string expire_date;
        string profile;    
    }Table;

    Device();
    bool Save(void);
    bool Find(list<Table> * lt);
    bool Del(void);

    Table table;
private:
    static const string id;
    static const string siteid;
    static const string device_type;
    static const string create_date;
    static const string update_date;
    static const string expire_date;
    static const string profile;
};

#endif
