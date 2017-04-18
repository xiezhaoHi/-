#ifndef DATAEXCHANGE_H
#define DATAEXCHANGE_H

//!
//! \brief DataExchange::DataExchange
//!
//!电梯检测系统
//! authou:xiezhao
//! date:20170331
//! data:数据交互
//! qq:454668838
//!
//!

#include<QThread>
#include<QTcpSocket>
#include<QObject>
#include<QThread>
#include<QTimer>
#include<QMutex>
#include<QWaitCondition>
#include"CCycleBuffer.h"
//!单例模式
//!

struct data{
    QString data1;
    QString data2;
};

class Worker : public QObject
{

    Q_OBJECT

public:
    Worker();

public slots:

    //!把数据望 缓冲区 存
    void producer(const QString &parameter) ;

    //!从缓冲区取数据 计算 显示
    void consumer();
signals:

    void resultReady(const QString &result);
};
class DataExchange : public QObject
{

 Q_OBJECT

public:

    static DataExchange* m_dataExchange;
    static DataExchange* InitDataExchange();
    ~DataExchange();


private:
        DataExchange();
public:
    /*数据缓冲区
     *存堆指针，方便数据read方解析
     *
     *
     */
    CCycleBuffer  m_cyclebuff;

    /*
     * 互斥锁
     */
    QMutex      m_mutex;
    QWaitCondition m_cond;
    QTcpSocket*  m_tcpSocket;
    bool Init(void);
    //! 一个 存放数据的 仓库
    //! 使用 环形 缓冲区
    //! m_maxSize  缓冲区的最大值
    //! m_writePos  写指针位置
    //! m_readPos   读指针位置

    int   m_writePos;
    int   m_readPos;
    int         m_maxSize;
    //!当前的 数据数量
    int     m_current_count;
    QString m_dataBuffer[1024];


    QThread m_producerThread;
    QThread m_consumerThread;
    QTimer m_timer;

Q_SIGNALS:
    void startProduce(const QString &parameter);
    void startConsume(void);

private slots:
    //!链接建立
    void hasconnected();
    //!读取解析返回数据
    void readyread();
    void  disconnected();
};
#endif // DATAEXCHANGE_H
