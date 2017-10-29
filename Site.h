#ifndef SITE_H
#define SITE_H

#include <string>
#include <list>
#include "IRecord.h"

using namespace std;


class Site : public IRecord
{
public:
    typedef struct {
        string id;
        string serialno;
        string productno;
        string create_date;
        string update_date;
        string expire_date;
        string profile;    
    }Table;

    Site();
    bool Save(void);
    bool Find(list<Table> * lt);
    bool Del(void);

    Table table;
private:
    static const string id;
    static const string serialno;
    static const string productno;
    static const string create_date;
    static const string update_date;
    static const string expire_date;
    static const string profile;
};

#endif
