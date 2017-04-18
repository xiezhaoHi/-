#ifndef MYDATABASE_H
#define MYDATABASE_H

#include"connectionpool.h"
/*
 * 数据库操作库
 * 实现数据库基本操作
 * 增:addData(QString const& strSql)
 * 删:deleteData(QString const& strSql)
 * 改:changeData(QString const& strSql)
 * 查:selectData(QString const& strSql)
 *
 */
class MyDatabase
{
private:
    //QString m_strPath;  //配置文件的路径
public:
     MyDatabase();

     bool  addData(QString const& strSql)   ;
    bool deleteData(QString const& strSql);
    bool changeData(QString const& strSql);
    bool selectData(QString const& strSql);

};

#endif // MYDATABASE_H
