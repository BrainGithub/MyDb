#include "MysqlQuery.h"

MysqlQuery::MysqlQuery()
{
    _mysql_res = NULL;
    _field = NULL;
    _row = NULL;
    _row_count = 0;
    _field_count = 0;
}
MysqlQuery::MysqlQuery(MysqlQuery& rQuery)
{
    *this = rQuery;
}
MysqlQuery& MysqlQuery::operator=(MysqlQuery& rQuery)
{
    if ( this == &rQuery )
        return *this;
    _mysql_res = rQuery._mysql_res;
    _row = NULL;
    _row_count = 0;
    _field_count = 0;
    _field = NULL;
    if ( _mysql_res != NULL )
    {
        //定位游标位置到第一个位置
        mysql_data_seek(_mysql_res, 0);
        _row = mysql_fetch_row( _mysql_res );
        _row_count = mysql_num_rows( _mysql_res ); 
        //得到字段数量
        _field_count = mysql_num_fields( _mysql_res );
    }
    rQuery._mysql_res = NULL;
    rQuery._field = NULL;
    rQuery._row = NULL;
    rQuery._row_count = 0;
    rQuery._field_count = 0;
    return *this;
}
MysqlQuery::~MysqlQuery()
{
    freeRes();
}
void MysqlQuery::freeRes()
{
    if ( _mysql_res != NULL )
    {
        mysql_free_result(_mysql_res);
        _mysql_res = NULL;
    }
}

long MysqlQuery::numRows()
{
    return _row_count;
}

int MysqlQuery::numFields()
{
    return _field_count;
}

long MysqlQuery::seekRow(long offerset)
{
    if ( offerset < 0 )
        offerset = 0;
    if ( offerset >= _row_count )
        offerset = _row_count -1;
    mysql_data_seek(_mysql_res, offerset);

    _row = mysql_fetch_row(_mysql_res);
    return offerset;
}

int MysqlQuery::fieldIndex(const char* szField)
{
    if ( NULL == _mysql_res )
        return -1;
    if ( NULL == szField )
        return -1;
    mysql_field_seek(_mysql_res, 0);//定位到第0列
    int i = 0;
    while ( i < _field_count )
    {
        _field = mysql_fetch_field( _mysql_res );
        if ( _field != NULL && strcmp(_field->name, szField) == 0 )//找到
            return i;
        i++;
    }
    return -1;
}
const char* MysqlQuery::fieldName(int nCol)
{
    if ( _mysql_res == NULL )
        return NULL;
    mysql_field_seek(_mysql_res, nCol);
    _field = mysql_fetch_field(_mysql_res);
    if ( _field != NULL )
        return _field->name;
    else
        return  NULL;
}
int MysqlQuery::getIntField(int nField, int defValue/* = 0*/)
{ 
    if ( NULL == _mysql_res )
        return defValue;

    if ( nField + 1 > (int)_field_count )
        return defValue;

    if ( NULL == _row )
        return defValue;

    return atoi(_row[nField]);
}
int MysqlQuery::getIntField(const char* szField, int defValue/* = 0*/)
{
    if ( NULL == _mysql_res || NULL == szField )
        return defValue;

    if ( NULL == _row )
        return defValue;
    const char* field = getStringField(szField);
    if ( NULL == field )
        return defValue;
    return atoi(field);
}
const char* MysqlQuery::getStringField(int nField, const char* szDefValue)
{
    if ( NULL == _mysql_res )
        return szDefValue;
    if ( nField + 1 > (int)_field_count )
        return szDefValue;
    if ( NULL == _row )
        return szDefValue;
    return _row[nField];
}

const char* MysqlQuery::getStringField(const char* szField, const char* szDefValue)
{
    if ( NULL == _mysql_res )
        return szDefValue;
    int nField = fieldIndex(szField);
    if ( nField == -1 )
        return szDefValue;

    return getStringField(nField);
}

double MysqlQuery::getFloatField(int nField, double fDefValue/*=0.0*/)
{
    const char* field = getStringField(nField);
    if ( NULL == field )
        return fDefValue;
    return atol(field);
}
 
double MysqlQuery::getFloatField(const char* szField, double fDefValue/*=0.0*/)
{
    const char* field = getStringField(szField);
    if ( NULL == field )
        return fDefValue;
    return atol(field);
}

void MysqlQuery::nextRow()
{
    if ( NULL == _mysql_res )
        return;
    _row = mysql_fetch_row(_mysql_res);
}

bool MysqlQuery::eof()
{
    if ( _row == NULL )
        return true;
    return false;
}

