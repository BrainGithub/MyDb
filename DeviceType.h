#ifndef DEVICETYPE_H
#define DEVICETYPE_H

#include <string>
#include <list>
#include "IRecord.h"

using namespace std;

class DeviceType : public IRecord
{
public:

    typedef struct {
        string type;
        string name; 
    }Table;

    DeviceType();
    bool Save(void);
    bool Find(list<Table> * lt);
    bool Del(void);

    Table table;
private:
    static const string type;
    static const string name;
};

#endif

