

class Site : public BaseRecord
{
public:
	int id;
	string serialno;
	string productno;
	string create_date;
	string update_date;
	string expire_date;
	string profile;


};
	
Site::Site()
{

}
		
/*
bool Site::Save(void)
{
	string sqlStr;
	if (this->insert)
	{
		sqlStr = "insert into " + tableName + " values()";
	}
	else
	{
		sqlStr = "update " + tableName + " values()";
	}
	res = sql_exec(sqlStr,0,0, &errMsg); 
}
	
bool Site::Find( void out * data)
{
	string sqlStr = "select * from " + tableName + ";";
	sql_exec(sqlStr, callback , 0 , &errMsg);
	
	this->id = "";
	this->serialno = "";
	this->productno = "";
	this->create_date = "";
	this->update_date = "";
	this->expire_date = "";
	this->profile = "";
}
	
bool Site::Del()
{
	string sqlStr = "delete from " + tableName + " where ..;";
	sql_exec(sqlStr, callback , 0 , &errMsg);
}
*/