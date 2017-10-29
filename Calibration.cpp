#include "Calibration.h"

const string Calibration::id = "id";
const string Calibration::nodeid = "nodeid";
const string Calibration::deviceid = "deviceid";
const string Calibration::gain= "gain";
const string Calibration::offset= "offset";
const string Calibration::max= "max";
const string Calibration::min= "min";
const string Calibration::create_date = "create_date";
    
Calibration::Calibration()
{
    tableName = "calibration";
}
        
bool Calibration::Save(void)
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

        GET_TABLE_ITEMS(id, tblItems);
        GET_TABLE_ITEMS(nodeid, tblItems);
        GET_TABLE_ITEMS(deviceid, tblItems);
        GET_TABLE_ITEMS(gain, tblItems);
        GET_TABLE_ITEMS(offset, tblItems);
        GET_TABLE_ITEMS(max, tblItems);
        GET_TABLE_ITEMS(min, tblItems);
        GET_TABLE_ITEMS(create_date, tblItems);

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
 
        GET_TABLEITEM_INT_VALUES(id, values);
        GET_TABLEITEM_INT_VALUES(nodeid, values);
        GET_TABLEITEM_INT_VALUES(deviceid, values);
        GET_TABLEITEM_STR_VALUES(gain, values);
        GET_TABLEITEM_STR_VALUES(offset, values);
        GET_TABLEITEM_INT_VALUES(max, values);
        GET_TABLEITEM_INT_VALUES(min, values);
        GET_TABLEITEM_STR_VALUES(create_date, values);

        if (IsNullOrEmpty(tblItems) || IsNullOrEmpty(values))
        {
            printf("insert Calibration IsNullOrEmpty(tblItems) || IsNullOrEmpty(values)\n");
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

        //SET_TABLEITEM_INT_VALUES(id, values);
        SET_TABLEITEM_INT_VALUES(nodeid, values);
        SET_TABLEITEM_INT_VALUES(deviceid, values);
        SET_TABLEITEM_STR_VALUES(gain, values);
        SET_TABLEITEM_STR_VALUES(offset, values);
        SET_TABLEITEM_INT_VALUES(max, values);
        SET_TABLEITEM_INT_VALUES(min, values);
        SET_TABLEITEM_STR_VALUES(create_date, values);

        if (IsNullOrEmpty(table.id))
        {
            printf("update Calibration IsNullOrEmpty(table.id)\n");
            return false;
        }

        sqlStr = "update ";
        sqlStr.append(tableName);
        sqlStr.append(" set ");
        sqlStr.append(values);
        sqlStr.append(" where ");
        sqlStr.append(this->id);
        sqlStr.append("=");
        sqlStr.append(table.id);
        sqlStr.append(";");
    }

    printf("Calibration:%s\n", sqlStr.c_str());
    state =  mydb->Exec(sqlStr); 
    return state;
}
    
bool Calibration::Find(list<Table> * lt)
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

    GET_FIND_CONDITION_INT_VALUES(id, condition);
    GET_FIND_CONDITION_INT_VALUES(nodeid, condition);
    GET_FIND_CONDITION_INT_VALUES(deviceid, condition);
    GET_FIND_CONDITION_STR_VALUES(gain, condition);
    GET_FIND_CONDITION_STR_VALUES(offset, condition);
    GET_FIND_CONDITION_INT_VALUES(max, condition);
    GET_FIND_CONDITION_INT_VALUES(min, condition);
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

    printf("Calibration:%s\n", sqlStr.c_str());
    Result * res = mydb->Query(sqlStr);
    
    if (res == NULL)
        return false;

    while (res->next())
    {
        Table tbl;
        char * str = NULL;
        str = res->value(this->id.c_str());    
        tbl.id = (str == NULL ? "":str);
        str = res->value(this->nodeid.c_str());    
        tbl.nodeid = (str == NULL ? "":str);
        str = res->value(this->deviceid.c_str());    
        tbl.deviceid = (str == NULL ? "":str);
        str = res->value(this->gain.c_str());    
        tbl.gain = (str == NULL ? "":str);
        str = res->value(this->offset.c_str());    
        tbl.offset = (str == NULL ? "":str);
        str = res->value(this->max.c_str());    
        tbl.max = (str == NULL ? "":str);
        str = res->value(this->min.c_str());    
        tbl.min = (str == NULL ? "":str);
        str = res->value(this->create_date.c_str());    
        tbl.create_date= (str == NULL ? "":str);

        cout << tbl.id << "|"
             << tbl.nodeid << "|" 
             << tbl.deviceid << "|" 
             << tbl.gain << "|" 
             << tbl.offset << "|" 
             << tbl.max << "|" 
             << tbl.min << "|" 
             << tbl.create_date << endl;
        
        lt->push_back(tbl);
    }    

    return true;
}

bool Calibration::Del()
{
    bool state = false;
    string condition = "";

    if(IsNullOrEmpty(table.id)){
        printf("Calibration Del: IsNullOrEmpty(table.id)\n");
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

    GET_DEL_CONDITION_INT_VALUES(id, condition);
    

    if (IsNullOrEmpty(condition)){
        return false;
    }

    string sqlStr = "delete from ";
    sqlStr.append(tableName);
    sqlStr.append(" where ");
    sqlStr.append(condition);
    sqlStr.append(";");

    printf("Calibration:%s\n", sqlStr.c_str());
    state = mydb->Exec(sqlStr);
    return state;
}
