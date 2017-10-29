#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <string>
#include <list>
#include "IRecord.h"

using namespace std;


class Calibration : public IRecord
{
public:
    typedef struct {
        string id;
        string nodeid;
        string deviceid;
        string gain;
        string offset;
        string max;
        string min;
        string create_date;
    }Table;

    Calibration();
    bool Save(void);
    bool Find(list<Table> * lt);
    bool Del(void);

    Table table;
private:
    static const string id;
    static const string nodeid;
    static const string deviceid;
    static const string gain;
    static const string offset;
    static const string max;
    static const string min;
    static const string create_date;
};

#endif
