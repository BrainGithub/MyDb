#ifndef AXIS_H
#define AXIS_H

#include <string>
#include <list>
#include "IRecord.h"

using namespace std;


class Axis : public IRecord
{
public:
    typedef struct {
        string nodeid;
        string deviceid;
        string position;
        string velocity;
        string torque;
        string accelerate;
        string current;    
        string voltage;    
        string create_date;
        string profile;    
    }Table;

    Axis();
    bool Save(void);
    bool Find(list<Table> * lt);
    bool Del(void);

    Table table;
private:
    static const string nodeid;
    static const string deviceid;
    static const string position;
    static const string velocity;
    static const string torque;
    static const string accelerate;
    static const string current;
    static const string voltage;
    static const string create_date;
    static const string profile;
};

#endif
