#include "mainwindow.h"


#include <QFile>
#include <QApplication>
#include<QTextCodec>
#include<QMutex>
#include<QDateTime>
#include<QTextStream>
#include<QSettings>
#include"custom.h"
class CommonHelper
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};



void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);


    QString strFile = qApp->applicationDirPath() +QString("/logfiles/%1.txt").arg( QDateTime::currentDateTime().toString("yyyyMMdd"));
    QFile file(strFile);

    //如果打开失败,文件不存在
    if(file.exists())
    {
          file.open(QIODevice::WriteOnly | QIODevice::Append);
    }
    else
    {
        file.open(QIODevice::ReadWrite | QIODevice::Text);
    }

    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册MessageHandler
     //  qInstallMessageHandler(outputMessage);
    CommonHelper::setStyle(":/qss/test.qss");
    MainWindow w;
   // custom w;



       //打印日志到文件中
       //qDebug("This is a debug message");
      // qWarning("This is a warning message");
     //  qCritical("This is a critical message");


    w.setWindowIcon(QIcon(":/images/G:/测试图片/Entypo_26c8(0).ico"));

   w.setWindowTitle(QStringLiteral("检测系统" ));
    w.show();

    return a.exec();
}
