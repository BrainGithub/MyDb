
#include "DbManager.h"
#include <list>
#include "Site.h"
#include "Device.h"
#include "DeviceType.h"
#include "Axis.h"
#include "Calibration.h"

    
//test the base open and close
void DbManager_test()
{
    IMyDB * db;
    DbManager *dbm = DbManager::Instance();
    if (NULL == (db = dbm->GetDB())){
        printf("ooo failed\n");
        exit(-1);
    }

    list<void*> l; 

    for (int i=0; i<12; i++){
        void *p = db->Open();
        l.push_back(p);
        printf("open db:%d\n", p);
    }

    for (int j=0; j<5; j++){
        db->Close(l.back());
        l.pop_back();
    }
    
    for (int i=0; i<12; i++){
        void *p = db->Open();
        printf("open db:%d\n", p);
    }
}

void Site_test()
{
    Site * site = new Site();
//    site->table.profile="123";
    //site->table.id="124";
    //site->table.serialno="123";
    //site->table.expire_date="2017-10-10 15:00:00";
    //site->insert=false;
    //site->Del();
    list<Site::Table> list;
    site->Find(&list);
    Site::Table tbl = list.front();
        cout << tbl.id << "|"
             << tbl.serialno << "|" 
             << tbl.productno << "|" 
             << tbl.create_date << "|" 
             << tbl.update_date << "|" 
             <<    tbl.expire_date << "|" 
             << tbl.profile << endl;
    delete site;
}

void DeviceType_test()
{
    DeviceType * devt = new DeviceType();
    //add
    devt->table.type = "44444";
    devt->table.name = "";
    //devt->insert = false;   
    devt->Save();

    //update
    devt->table.type = "44444";
    devt->table.name = "eat";
    devt->insert = false;   
    devt->Save();

    //delete
    devt->table.type = "77";
    devt->Del();

    //find
    //devt->table.type = "44444";
    //devt->table.name= "eat";

    list<DeviceType::Table> ldt;
    list<DeviceType::Table>::iterator itbl;
    devt->Find(&ldt);
    for (itbl = ldt.begin(); itbl != ldt.end(); itbl++)
    {
        cout << "DeviceType:" << itbl->type << "|" << itbl->name << endl;
    }
}    

void Device_test()
{
    Device * dev = new Device();
    dev->table.id = "1";
    dev->table.siteid = "3";
    dev->table.device_type = "100";
    dev->insert = false;
    //dev->Save();
    dev->Del();
    return;

    list<Device::Table> lt;
    list<Device::Table>::iterator itor;
    dev->Find(&lt);
    for (itor = lt.begin(); itor != lt.end(); itor++)
    {
        cout << "Device:" << itor->id << "|"    
                         << itor->siteid << "|"
                         << itor->device_type << "|"
                         << itor->create_date << "|"
                         << itor->update_date << "|"
                         << itor->expire_date << "|"
                         << itor->profile << "|"
                         << endl;
    }
}

void Axis_test()
{
    Axis * axis = new Axis(); 
    axis->table.nodeid = "123";
    axis->table.deviceid = "123";
    axis->table.position = "123.123456";
    //axis->insert = false;


    list<Axis::Table> lt;
    list<Axis::Table>::iterator itor;
    axis->Find(&lt);
    //for (itor = lt.begin(); itor != lt.end(); itor++)
    //{
    //    cout << "Axis:" << itor->id << "|"    
    //                     << itor->siteid << "|"
    //                     << itor->device_type << "|"
    //                     << itor->create_date << "|"
    //                     << itor->update_date << "|"
    //                     << itor->expire_date << "|"
    //                     << itor->profile << "|"
    //                     << endl;
    //
    //}

    //axis->Del();
}



void Calibration_test()
{
    Calibration * cal = new Calibration(); 
    cal->table.id = "5";
    cal->table.nodeid = "123";
    cal->table.deviceid = "124";
    //cal->table.position = "123.123456";
    cal->insert = false;
    cal->Save();

    list<Calibration::Table> lt;
    list<Calibration::Table>::iterator itor;
    cal->Find(&lt);
    //for (itor = lt.begin(); itor != lt.end(); itor++)
    //{
    //    cout << "Calibration:" << itor->id << "|"    
    //                     << itor->siteid << "|"
    //                     << itor->device_type << "|"
    //                     << itor->create_date << "|"
    //                     << itor->update_date << "|"
    //                     << itor->expire_date << "|"
    //                     << itor->profile << "|"
    //                     << endl;
    //
    //}

}


int main()
{
    //Device_test();
    //Axis_test();
    Calibration_test();
    return 0;
}
