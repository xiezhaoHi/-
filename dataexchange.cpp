#include "dataexchange.h"
#include<QSettings>
#include<QCoreApplication>
#include<QDataStream>
#include<QTimer>
#include "mainwindow.h"
DataExchange* DataExchange::m_dataExchange = NULL;
DataExchange::DataExchange()
{

}
DataExchange::~DataExchange()
{
    if(m_dataExchange)
    {


        delete m_dataExchange;
    }

}
//链接服务器初始化
 bool DataExchange::Init(void)
 {
     QString strPath = qApp->applicationDirPath()+"\\config\\config.ini";

     QSettings iniRead(strPath,QSettings::IniFormat);
     QString strHost = iniRead.value("SOCKET/host").toString();
     int  port = iniRead.value("SOCKET/port").toInt();

     //!配置无效
     if(strHost.isEmpty()
           || 0 == port)
     {
         qCritical() << "无效的配置文件!获取 主机 端口失败!";
         return false;
     }

   m_tcpSocket = new QTcpSocket();
     m_tcpSocket->connectToHost(strHost,port,QTcpSocket::ReadWrite);
    connect(m_tcpSocket,&QTcpSocket::connected,this,&DataExchange::hasconnected);
    connect(m_tcpSocket,&QTcpSocket::disconnected,this,&DataExchange::disconnected);


    //!初始化 存储数据的 缓冲区
    //!     int   m_writePos;
  //!   int   m_readPos;
  //!   int         m_maxSize;
    //! data* m_dataBuffer;

//    m_maxSize = 1024;
//  //  m_dataBuffer = new QString[m_maxSize];
//   // memset(m_dataBuffer,0,m_maxSize);
//m_dataBuffer[0] = "hello";
//    m_writePos = m_readPos =m_current_count= 0;
//m_current_count++;


//    //!生产者 线程 启动
//    Worker *worker = new Worker;

//    worker->moveToThread(&m_producerThread);

//    connect(&m_producerThread, &QThread::finished, worker, &QObject::deleteLater);

//   connect(this, &DataExchange::startProduce, worker, &Worker::producer);

//    m_producerThread.start();


//    //!消费者线程
//    //只是用于测试
//    worker = new Worker;

//    worker->moveToThread(&m_consumerThread);

//    connect(&m_consumerThread, &QThread::finished, worker, &QObject::deleteLater);

//    connect(&m_timer, &QTimer::timeout, worker, &Worker::consumer);
//     m_timer.start(100);
//    m_consumerThread.start();
     return true;
 }
  DataExchange* DataExchange::InitDataExchange()
  {
        if(!m_dataExchange)
        {
            m_dataExchange = new DataExchange();
            //!初始化  tcp 链接
            if(!m_dataExchange->Init())
            {
                delete m_dataExchange;
                m_dataExchange = NULL;
            }
    }
        qDebug() << m_dataExchange->m_maxSize << "," << m_dataExchange->m_current_count ;
 return m_dataExchange;
}



  //!服务端链接断开
void  DataExchange::disconnected()
{
    qDebug() << QStringLiteral("断开服务端链接!");
  //  if(m_tcpSocket)
   //     delete m_tcpSocket;
       // connect(m_dataExchange->m_tcpSocket,&QTcpSocket::readyRead,this,&DataExchange::readyread);
  //  delete  m_dataExchange->m_tcpSocket ;
}

void  DataExchange::hasconnected()
{
     qDebug() << QStringLiteral("连接服务端成功!");
        connect(m_dataExchange->m_tcpSocket,&QTcpSocket::readyRead,this,&DataExchange::readyread);
}
/*服务端回复数据*/
void  DataExchange::readyread()
{
    QByteArray arr=m_tcpSocket->readAll();
      // QDataStream * dst=new QDataStream(&arr,QIODevice::ReadOnly);/******重点******/
       QDataStream dst(&arr,QIODevice::ReadOnly);

       QString str1;
       //QString str2;
       dst>>str1;
    //   qDebug() << str1 ;
     //  emit startProduce(str1);
       QString* pstr = new QString(str1);
     //  qDebug() << pstr;
    //    qDebug() << *pstr;
       m_mutex.lock();
       m_cyclebuff.write((char*)&pstr,4);
       m_cond.notify_all();
       m_mutex.unlock();
       //delete dst;
}



//!把数据望 缓冲区 存
void Worker::producer(const QString &parameter)
{
   // QString* pstr = new QString(parameter);

}

//!从缓冲区取数据 计算 显示
//暂时不用,只用于测试
void Worker::consumer()
{
  //  qDebug() << "h" << DataExchange::m_dataExchange->m_current_count;
   DataExchange::m_dataExchange->m_mutex.lock();
   if(DataExchange::m_dataExchange->m_cyclebuff.isEmpty())
       DataExchange::m_dataExchange->m_cond.wait(&DataExchange::m_dataExchange->m_mutex);
 QString* pstr = NULL;
  if(4 ==  DataExchange::m_dataExchange->m_cyclebuff.read((char*)&pstr,4))
  {
   qDebug() << pstr;
  qDebug() << *pstr;
  delete pstr;
  }
  DataExchange::m_dataExchange->m_mutex.unlock();
}

Worker::Worker()
{
    //connect(this,&Worker::resultReady,&MainWindow::resultReady);
}
