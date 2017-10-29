#include "Axis.h"

const string Axis::nodeid = "nodeid";
const string Axis::deviceid = "deviceid";
const string Axis::position = "position";
const string Axis::velocity = "velocity";
const string Axis::torque = "torque";
const string Axis::accelerate = "accelerate";
const string Axis::current = "current";
const string Axis::voltage = "voltage";
const string Axis::create_date = "create_date";
const string Axis::profile = "profile";
    
Axis::Axis()
{
    tableName = "axis";
}
        
bool Axis::Save(void)
{
    bool state = false;
    string sqlStr;
    string tblItems;
    string values;
    string temp;

    if (this->insert)
    {
        tblItems = "";

#define GET_TABLE_ITEMS(item, values)\
{\
    if (!IsNullOrEmpty(table.item)){\
        values.append(IsNullOrEmpty(values) ? "":",");\
        values.append(this->item);\
    }\
}

        GET_TABLE_ITEMS(nodeid, tblItems);
        GET_TABLE_ITEMS(deviceid, tblItems);
        GET_TABLE_ITEMS(position, tblItems);
        GET_TABLE_ITEMS(velocity, tblItems);
        GET_TABLE_ITEMS(torque, tblItems);
        GET_TABLE_ITEMS(accelerate, tblItems);
        GET_TABLE_ITEMS(current, tblItems);
        GET_TABLE_ITEMS(voltage, tblItems);
        GET_TABLE_ITEMS(create_date, tblItems);
        GET_TABLE_ITEMS(profile, tblItems);

#define GET_TABLEITEM_INT_VALUES(item, values) do{\
    if (!IsNullOrEmpty(table.item)){\
        values.append(IsNullOrEmpty(values) ? "":",");\
        values.append(table.item);\
    }\
}while(0)


#define GET_TABLEITEM_STR_VALUES(item, values) do{\
    if (!IsNullOrEmpty(table.item)){\
        values.append(IsNullOrEmpty(values) ? "":",");\
        values.append("'");\
        values.append(table.item);\
        values.append("'");\
    }\
}while(0)

        //values
        values = "";
 
        GET_TABLEITEM_INT_VALUES(nodeid, values);
        GET_TABLEITEM_INT_VALUES(deviceid, values);
        GET_TABLEITEM_INT_VALUES(position, values);
        GET_TABLEITEM_STR_VALUES(velocity, values);
        GET_TABLEITEM_STR_VALUES(torque, values);
        GET_TABLEITEM_STR_VALUES(accelerate, values);
        GET_TABLEITEM_STR_VALUES(current, values);
        GET_TABLEITEM_STR_VALUES(voltage, values);
        GET_TABLEITEM_STR_VALUES(create_date, values);
        GET_TABLEITEM_STR_VALUES(profile, values);

        if (IsNullOrEmpty(tblItems) || IsNullOrEmpty(values))
        {
            printf("insert Axis IsNullOrEmpty(tblItems) || IsNullOrEmpty(values)\n");
            return false;
        }


        sqlStr += "insert into ";
        sqlStr += tableName;
        sqlStr += " (";
        sqlStr += tblItems;
        sqlStr += ") values (";
        sqlStr += values;
        sqlStr += ");";
    }
    else
    {
        values = "";

#define SET_TABLEITEM_INT_VALUES(item, values) do{\
    if (!IsNullOrEmpty(table.item)){\
        values.append(IsNullOrEmpty(values) ? "":",");\
        values.append(this->item);\
        values.append("=");\
        values.append(table.item);\
    }\
}while(0)
        
#define SET_TABLEITEM_STR_VALUES(item, values) do{\
    if (!IsNullOrEmpty(table.item)){\
        values.append(IsNullOrEmpty(values) ? "":",");\
        values.append(this->item);\
        values.append("=");\
        values.append("'");\
        values.append(table.item);\
        values.append("'");\
    }\
}while(0)

        //SET_TABLEITEM_INT_VALUES(nodeid, values);
        //SET_TABLEITEM_INT_VALUES(deviceid, values);
        SET_TABLEITEM_INT_VALUES(position, values);
        SET_TABLEITEM_STR_VALUES(velocity, values);
        SET_TABLEITEM_STR_VALUES(torque, values);
        SET_TABLEITEM_STR_VALUES(accelerate, values);
        SET_TABLEITEM_STR_VALUES(current, values);
        SET_TABLEITEM_STR_VALUES(voltage, values);
        SET_TABLEITEM_STR_VALUES(create_date, values);
        SET_TABLEITEM_STR_VALUES(profile, values);

        if (IsNullOrEmpty(table.nodeid) || 
            IsNullOrEmpty(table.deviceid) || 
            IsNullOrEmpty(values))
        {
            printf("update Axis IsNullOrEmpty(table.nodeid) || \
                IsNullOrEmpty(table.deviceid) || \
                IsNullOrEmpty(values)\n");
            return false;
        }

        sqlStr = "update ";
        sqlStr.append(tableName);
        sqlStr.append(" set ");
        sqlStr.append(values);
        sqlStr.append(" where ");
        sqlStr.append(this->nodeid);
        sqlStr.append("=");
        sqlStr.append(table.nodeid);
        sqlStr.append(" and ");
        sqlStr.append(this->deviceid);
        sqlStr.append("=");
        sqlStr.append(table.deviceid);
        sqlStr.append(";");
    }

    printf("Axis:%s\n", sqlStr.c_str());
    state =  mydb->Exec(sqlStr); 
    return state;
}
    
bool Axis::Find(list<Table> * lt)
{
    string condition = "";

    #define GET_FIND_CONDITION_INT_VALUES(item, values) do{\
        if (!IsNullOrEmpty(table.item)){\
            values.append(IsNullOrEmpty(values) ? "":" and ");\
            values.append(this->item);\
            values.append("=");\
            values.append(table.item);\
        }\
    }while(0)

    #define GET_FIND_CONDITION_STR_VALUES(item, values) do{\
        if (!IsNullOrEmpty(table.item)){\
            values.append(IsNullOrEmpty(values) ? "":" and ");\
            values.append(this->item);\
            values.append("=");\
            values.append("'");\
            values.append(table.item);\
            values.append("'");\
        }\
    }while(0)

    GET_FIND_CONDITION_INT_VALUES(nodeid, condition);
    GET_FIND_CONDITION_INT_VALUES(deviceid, condition);
    GET_FIND_CONDITION_INT_VALUES(position, condition);
    GET_FIND_CONDITION_STR_VALUES(velocity, condition);
    GET_FIND_CONDITION_STR_VALUES(torque, condition);
    GET_FIND_CONDITION_STR_VALUES(accelerate, condition);
    GET_FIND_CONDITION_STR_VALUES(current, condition);
    GET_FIND_CONDITION_STR_VALUES(voltage, condition);
    GET_FIND_CONDITION_STR_VALUES(create_date, condition);
    
    string sqlStr = "select * from ";

    if (IsNullOrEmpty(condition)){
        sqlStr.append(tableName);
    }else{
        sqlStr.append(tableName);
        sqlStr.append(" where ");
        sqlStr.append(condition);
    }
    sqlStr.append(" limit 100;");

    printf("Axis:%s\n", sqlStr.c_str());
    Result * res = mydb->Query(sqlStr);
    
    if (res == NULL)
        return false;

    while (res->next())
    {
        Table tbl;
        char * str = NULL;
        str = res->value(this->nodeid.c_str());    
        tbl.nodeid = (str == NULL ? "":str);
        str = res->value(this->deviceid.c_str());    
        tbl.deviceid = (str == NULL ? "":str);
        str = res->value(this->position.c_str());    
        tbl.position = (str == NULL ? "":str);
        str = res->value(this->velocity.c_str());    
        tbl.velocity = (str == NULL ? "":str);
        str = res->value(this->torque.c_str());    
        tbl.torque = (str == NULL ? "":str);
        str = res->value(this->accelerate.c_str());    
        tbl.accelerate = (str == NULL ? "":str);
        str = res->value(this->current.c_str());    
        tbl.current = (str == NULL ? "":str);
        str = res->value(this->voltage.c_str());    
        tbl.voltage = (str == NULL ? "":str);
        str = res->value(this->create_date.c_str());    
        tbl.create_date= (str == NULL ? "":str);
        str = res->value(this->profile.c_str());    
        tbl.profile= (str == NULL ? "":str);

        cout << tbl.nodeid << "|"
             << tbl.deviceid << "|" 
             << tbl.position << "|" 
             << tbl.velocity << "|" 
             << tbl.torque << "|" 
             << tbl.accelerate << "|" 
             << tbl.current << "|" 
             << tbl.voltage << "|" 
             << tbl.create_date << "|" 
             << tbl.profile << endl;
        
        lt->push_back(tbl);
    }    

    return true;
}

bool Axis::Del()
{
    bool state = false;
    string condition = "";

    if(IsNullOrEmpty(table.nodeid) || IsNullOrEmpty(table.deviceid) ){
        printf("Axis Del: IsNullOrEmpty(table.nodeid) || IsNullOrEmpty(table.deviceid)\n");
        return false;
    }

    #define GET_DEL_CONDITION_INT_VALUES(item, values) do{\
        if (!IsNullOrEmpty(table.item)){\
            values.append(IsNullOrEmpty(values) ? "":" and ");\
            values.append(this->item);\
            values.append("=");\
            values.append(table.item);\
        }\
    }while(0)

    GET_DEL_CONDITION_INT_VALUES(nodeid, condition);
    GET_DEL_CONDITION_INT_VALUES(deviceid, condition);
    

    if (IsNullOrEmpty(condition)){
        return false;
    }

    string sqlStr = "delete from ";
    sqlStr.append(tableName);
    sqlStr.append(" where ");
    sqlStr.append(condition);
    sqlStr.append(";");

    printf("Axis:%s\n", sqlStr.c_str());
    state = mydb->Exec(sqlStr);
    return state;
}
