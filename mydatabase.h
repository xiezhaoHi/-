#ifndef MYDATABASE_H
#define MYDATABASE_H

#include"connectionpool.h"
/*
 * ���ݿ������
 * ʵ�����ݿ��������
 * ��:addData(QString const& strSql)
 * ɾ:deleteData(QString const& strSql)
 * ��:changeData(QString const& strSql)
 * ��:selectData(QString const& strSql)
 *
 */
class MyDatabase
{
private:
    //QString m_strPath;  //�����ļ���·��
public:
     MyDatabase();

     bool  addData(QString const& strSql)   ;
    bool deleteData(QString const& strSql);
    bool changeData(QString const& strSql);
    bool selectData(QString const& strSql);

};

#endif // MYDATABASE_H
