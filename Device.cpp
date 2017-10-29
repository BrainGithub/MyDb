#include "Device.h"

const string Device::id = "id";
const string Device::siteid = "siteid";
const string Device::device_type = "device_type";
const string Device::create_date = "create_date";
const string Device::update_date = "update_date";
const string Device::expire_date = "expire_date";
const string Device::profile = "profile";
    
Device::Device()
{
    tableName = "device";
}
        
bool Device::Save(void)
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
        temp.append(this->id);
        tblItems += IsNullOrEmpty(table.id) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->siteid);
        tblItems += IsNullOrEmpty(table.siteid) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->device_type);
        tblItems += IsNullOrEmpty(table.device_type) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->create_date);
        tblItems += IsNullOrEmpty(table.create_date) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->update_date);
        tblItems += IsNullOrEmpty(table.update_date) ? "":temp; 
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->expire_date);
        tblItems += IsNullOrEmpty(table.expire_date) ? "":temp;
        temp = IsNullOrEmpty(tblItems)? "":",";
        temp.append(this->profile);
        tblItems += IsNullOrEmpty(table.profile) ? "":temp;

        temp = "";
        values = "";
        temp.append(table.id);
        values.append(IsNullOrEmpty(table.id) ? "":temp);
        temp = IsNullOrEmpty(values) ? "":","; 
        //temp.append("'");
        temp.append(table.siteid);
        //temp.append("'");
        values.append(IsNullOrEmpty(table.siteid) ? "":temp);

        temp = IsNullOrEmpty(values) ? "":",";
        //temp.append("'");
        temp.append(table.device_type);
        //temp.append("'");
        values.append(IsNullOrEmpty(table.device_type) ? "":temp);
        temp = IsNullOrEmpty(values) ? "":","; 
        temp.append("'");
        temp.append(table.create_date);
        temp.append("'");
        values.append(IsNullOrEmpty(table.create_date) ? "":temp);
        temp = IsNullOrEmpty(values) ? "":","; 
        temp.append("'");
        temp.append(table.update_date);
        temp.append("'");
        values.append(IsNullOrEmpty(table.update_date) ? "":temp);
        temp = IsNullOrEmpty(values) ? "":",";
        temp.append("'");
        temp.append(table.expire_date);
        temp.append("'");
        values.append(IsNullOrEmpty(table.expire_date) ? "":temp);
        temp = IsNullOrEmpty(values) ? "":","; 
        temp.append("'");
        temp.append(table.profile);
        temp.append("'");
        values.append(IsNullOrEmpty(table.profile) ? "":temp);

        if (IsNullOrEmpty(tblItems) || IsNullOrEmpty(values))
        {
            printf("insert Device IsNullOrEmpty(tblItems) || IsNullOrEmpty(values)\n");
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
        if (!IsNullOrEmpty(table.siteid)){
            values.append(this->siteid);
            values.append("=");
            //values.append("'");
            values.append(table.siteid);
            //values.append("'");
        }

        if (!IsNullOrEmpty(table.device_type)){
            values.append(",");
            values.append(this->device_type);
            values.append("=");
            //values.append("'");
            values.append(table.device_type);
            //values.append("'");
        }

        if (!IsNullOrEmpty(table.create_date)){
            values.append(",");
            values.append(this->create_date);
            values.append("=");
            values.append("'");
            values.append(table.create_date);
            values.append("'");
        }

        if (!IsNullOrEmpty(table.update_date)){
            values.append(",");
            values.append(this->update_date);
            values.append("=");
            values.append("'");
            values.append(table.update_date);
            values.append("'");
        }

        if (!IsNullOrEmpty(table.expire_date)){
            values.append(",");
            values.append(this->expire_date);
            values.append("=");
            values.append("'");
            values.append(table.expire_date);
            values.append("'");
        }

        if (!IsNullOrEmpty(table.profile)){
            values.append(",");
            values.append(this->profile);
            values.append("=");
            values.append("'");
            values.append(table.profile);
            values.append("'");
        }

        if (IsNullOrEmpty(table.id) || (IsNullOrEmpty(values))){
            printf("update Device IsNullOrEmpty(table.id) || (IsNullOrEmpty(values)\n");
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

    printf("Device:%s\n", sqlStr.c_str());
    state =  mydb->Exec(sqlStr); 
    return state;
}
    
bool Device::Find(list<Table> * lt)
{
    string temp = "";
    string condition = "";
        
    if (!IsNullOrEmpty(table.id))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->id);
        temp.append("=");
        temp.append(table.id);
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.siteid))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->siteid);
        temp.append("=");
        temp.append(table.siteid);
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.device_type))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->device_type);
        temp.append("=");
        temp.append(table.device_type);
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.create_date))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->create_date);
        temp.append("='");
        temp.append(table.create_date);
        temp.append("'");
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.update_date))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->update_date);
        temp.append("='");
        temp.append(table.update_date);
        temp.append("'");
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.expire_date))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->expire_date);
        temp.append("='");
        temp.append(table.expire_date);
        temp.append("'");
        condition.append(temp);
    }
    if (!IsNullOrEmpty(table.profile))
    {
        temp = "";
        temp.append(IsNullOrEmpty(condition)? "":" and ");
        temp.append(this->profile);
        temp.append("='");
        temp.append(table.profile);
        temp.append("'");
        condition.append(temp);
    }
    
    string sqlStr = "select * from ";

    if (IsNullOrEmpty(condition)){
        sqlStr.append(tableName);
    }else{
        sqlStr.append(tableName);
        sqlStr.append(" where ");
        sqlStr.append(condition);
    }
    sqlStr.append(" limit 100;");

    printf("Device:%s\n", sqlStr.c_str());
    Result * res = mydb->Query(sqlStr);
    
    if (res == NULL)
        return false;

    while (res->next())
    {
        Table tbl;
        char * str = NULL;
        str = res->value(this->id.c_str());    
        tbl.id = (str == NULL ? "":str);
        str = res->value(this->siteid.c_str());
        tbl.siteid = (str == NULL ? "":str);
        str = res->value(this->device_type.c_str());
        tbl.device_type = (str == NULL ? "":str); 
        str = res->value(this->create_date.c_str());
        tbl.create_date = (str == NULL ? "":str); 
        str = res->value(this->update_date.c_str());
        tbl.update_date = (str == NULL ? "":str); 
        str = res->value(this->expire_date.c_str());
        tbl.expire_date = (str == NULL ? "":str); 
        str = res->value(this->profile.c_str());    
        tbl.profile = (str == NULL ? "":str);

        cout << tbl.id << "|"
             << tbl.siteid << "|" 
             << tbl.device_type << "|" 
             << tbl.create_date << "|" 
             << tbl.update_date << "|" 
             << tbl.expire_date << "|" 
             << tbl.profile << endl;

        
        lt->push_back(tbl);
    }    
    return true;
}

bool Device::Del()
{
    bool state = false;
    string condition = "";
    
    if(!IsNullOrEmpty(table.id)){
        condition.append(this->id);
        condition.append("=");
        condition.append(table.id);
        
    }    

    if (IsNullOrEmpty(condition)){
        return false;
    }

    string sqlStr = "delete from ";
    sqlStr.append(tableName);
    sqlStr.append(" where ");
    sqlStr.append(condition);
    sqlStr.append(";");

    printf("Device:%s\n", sqlStr.c_str());
    state = mydb->Exec(sqlStr);
    return state;
}

