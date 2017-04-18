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
    void init(void);// ��һЩ����ĳ�ʼ������

    QThread m_consumerThread; //�������ݵ��߳�
    QTimer   m_timer;
public slots:

    void get_task_result( QList<struct_result> listResult,struct_cycle cycle);
    void show_ui_data(const QString & str);

    void on_pushButton_zdy_clicked();
    void on_pushButton_sz_clicked(bool checked);
};

//�������ݻ������е�����,�����µ�������
class ShowWorker : public QObject
{

    Q_OBJECT

public:
    //ShowWorker();
    MainWindow* m_pMainwindow; //��ui���ڵ�ָ��

public slots:

    //!�������� ������ ��
   // void producer(const QString &parameter) ;

    //!�ӻ�����ȡ���� ���� ��ʾ
    //�������� ����ʾ����
    void consumer();
signals:

    void showResult(const QString &result);
};
#endif // MAINWINDOW_H
