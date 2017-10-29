#include "DeviceType.h"

const string DeviceType::type = "type";
const string DeviceType::name = "name";

DeviceType::DeviceType()
{
    tableName = "deviceType";
}
        
bool DeviceType::Save(void)
{
    bool state = false;
    string sqlStr;
    string tblItems;
    string values;
    string temp;

    if (this->insert)
    {
        tblItems = "";
        temp = "";
        temp.append(this->type);
        tblItems += IsNullOrEmpty(table.type) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->name);
        tblItems += IsNullOrEmpty(table.name) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";

        temp = "";
        values = "";
        temp.append(table.type);
        values.append(IsNullOrEmpty(table.type) ? "":temp);
        temp = IsNullOrEmpty(values) ? "":","; 
        temp.append("'");
        temp.append(table.name);
        temp.append("'");
        values.append(IsNullOrEmpty(table.name) ? "":temp);


        if (IsNullOrEmpty(tblItems) || IsNullOrEmpty(values))
        {
            printf("insert DeviceType IsNullOrEmpty(tblItems) || IsNullOrEmpty(values)\n");
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
        if (!IsNullOrEmpty(table.name)){
            values.append(this->name);
            values.append("=");
            values.append("'");
            values.append(table.name);
            values.append("'");
        }

        if (IsNullOrEmpty(table.type) || (IsNullOrEmpty(values))){
            printf("update DeviceType IsNullOrEmpty(table.type) || (IsNullOrEmpty(values)\n");
            return false;
        }

        sqlStr = "update ";
        sqlStr.append(tableName);
        sqlStr.append(" set ");
        sqlStr.append(values);
        sqlStr.append(" where ");
        sqlStr.append(this->type);
        sqlStr.append("=");
        sqlStr.append(table.type);
        sqlStr.append(";");
    }

    printf("DeviceType:%s\n", sqlStr.c_str());
    state =  mydb->Exec(sqlStr); 
    return state;
}
    
bool DeviceType::Find(list<Table> * lt)
{
    string temp = "";
    string condition = "";
        
    if (!IsNullOrEmpty(table.type))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->type);
        temp.append("=");
        temp.append(table.type);
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.name))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->name);
        temp.append("='");
        temp.append(table.name);
        temp.append("'");
        condition.append(temp);
    }
    
    string sqlStr = "select * from ";
    if (IsNullOrEmpty(condition))
    {
        sqlStr.append(tableName);
        sqlStr.append(";");
        //sqlStr.append(" limit 100;");
    }
    else{
        sqlStr.append(tableName);
        sqlStr.append(" where ");
        sqlStr.append(condition);
        sqlStr.append(" limit 100;");
    }

    printf("DeviceType:%s\n", sqlStr.c_str());
    Result * res = mydb->Query(sqlStr);
    
    if (res == NULL)
        return false;

    while (res->next())
    {
        Table tbl;
        char * str = NULL;
        str = res->value(this->type.c_str());   
        tbl.type = (str == NULL ? "":str);
        str = res->value(this->name.c_str());
        tbl.name = (str == NULL ? "":str);

        cout << tbl.type << "|"
             << tbl.name << endl;

        
        lt->push_back(tbl);
    }   
    return true;
}

bool DeviceType::Del()
{
    bool state = false;
    string condition = "";
    
    if(!IsNullOrEmpty(table.type)){
        condition.append(this->type);
        condition.append("=");
        condition.append(table.type);
    }   

    if (IsNullOrEmpty(condition)){
        printf("DeviceType:IsNullOrEmpty(condition)\n"); 
        return false;
    }

    string sqlStr = "delete from ";
    sqlStr.append(tableName);
    sqlStr.append(" where ");
    sqlStr.append(condition);
    sqlStr.append(";");

    printf("DeviceType:%s\n", sqlStr.c_str());
    state = mydb->Exec(sqlStr);
    return state;
}


