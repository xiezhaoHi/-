#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QList>
#include<QGraphicsPixmapItem>
#include<QThread>
#include<QTimer>
#include"custom.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<QGraphicsPixmapItem*> m_item_list;
    void init(void);// 做一些界面的初始化工作

    QThread m_consumerThread; //处理数据的线程
    QTimer   m_timer;
public slots:

    void get_task_result( QList<struct_result> listResult,struct_cycle cycle);
    void show_ui_data(const QString & str);

    void on_pushButton_zdy_clicked();
    void on_pushButton_sz_clicked(bool checked);
};

//处理数据缓冲区中的数据,并更新到界面上
class ShowWorker : public QObject
{

    Q_OBJECT

public:
    //ShowWorker();
    MainWindow* m_pMainwindow; //主ui窗口的指针

public slots:

    //!把数据望 缓冲区 存
   // void producer(const QString &parameter) ;

    //!从缓冲区取数据 计算 显示
    //解析数据 并显示数据
    void consumer();
signals:

    void showResult(const QString &result);
};
#endif // MAINWINDOW_H
