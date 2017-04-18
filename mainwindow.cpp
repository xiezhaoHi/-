#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLineSeries>
#include<QPointF>
#include<QChart>
#include<QLabel>
#include<QTextEdit>
#include<QPushButton>
#include<QtMath>
#include"dataexchange.h"  //数据交换类
#include"custom.h"  //自定义类
QT_CHARTS_USE_NAMESPACE
//QString t[] = {QString::fromLocal8Bit("电压")};
QString  str[] = {"电压电流","电流","电压"
                  ,"频率",NULL};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init(); //主窗口界面初始化工作
   //!
   //!
   //!
   //! 进行 数据交互类初始化
   if(!DataExchange::InitDataExchange())
   {

   }

       ShowWorker* worker = new ShowWorker();
       connect(worker,&ShowWorker::showResult,this,&MainWindow::show_ui_data);
       worker->m_pMainwindow = this;
       worker->moveToThread(&m_consumerThread);

       connect(&m_consumerThread, &QThread::finished, worker, &QObject::deleteLater);

       connect(&m_timer, &QTimer::timeout, worker, &ShowWorker::consumer);
        m_timer.start(10);
       m_consumerThread.start();

}

MainWindow::~MainWindow()
{
    m_consumerThread.quit();
    m_consumerThread.wait();

    delete ui;
}




/*
 *
 * 自定义连续作业 流程步骤
 */
void MainWindow::on_pushButton_zdy_clicked()
{
    custom m;
    connect(&m,&custom::sendresult,this,&MainWindow::get_task_result);
    m.exec();
}


//QString strStep; //步骤
//QString strTask; //任务
//QString strChooseNum; //选择一个层数
void MainWindow::get_task_result( QList<struct_result> listResult,struct_cycle cycle)
{
    struct_result result;
    foreach (result, listResult) {
     qDebug() <<  result.strStep << result.strTask;
    }

    qDebug() << cycle.strCycleType << cycle.strCycleNum;
}

/*设置电压*/
void MainWindow::on_pushButton_sz_clicked(bool checked)
{

}
void MainWindow::init(void)
{
ui->label_dhl->setStyleSheet("color:red");
ui->label_dhl->setText(QStringLiteral("异常"));





    /*
    安全触点
*/
    QGraphicsScene* scene = new QGraphicsScene();

    int viewWidth = 160;//ui->graphicsView_aqcd->width()/2;
    int viewHeight = 110;//ui->graphicsView_aqcd->height()/2;
    QRectF rect = ui->graphicsView_aqcd->sceneRect();
    int indexNum = 20,fonSize =10;
    QGraphicsItem* pTemp = NULL;
    int x = -viewWidth,y = -viewHeight;
    int textWidth = 0;
    for(int index = 0; index < indexNum; ++index)
    {
        QGraphicsPixmapItem* itemPixmap = new QGraphicsPixmapItem(QPixmap(QStringLiteral(":/images/G:/测试图片/green.png")));

        m_item_list.append(itemPixmap);
        if(pTemp)
        {
           x = pTemp->x()+textWidth+20;
           y = pTemp->y();
        }
        if(x>=viewWidth)
        {
           x = -viewWidth;
           y = pTemp->y()+2*fonSize;
        }
        itemPixmap->setPos(x,y);
       scene->addItem(itemPixmap);

       QGraphicsTextItem* textItem = new QGraphicsTextItem(QString(QStringLiteral("触点%1")).arg(index+1));
        QFont font;
        font.setPixelSize(fonSize);

        textItem->setDefaultTextColor(QColor(34,140,58));
       textItem->setPos(x+fonSize+itemPixmap->boundingRect().width(),y);

       scene->addItem(textItem);

       //textWidth = textItem->boundingRect().width();
        textWidth = 5*fonSize;
       pTemp = textItem;
    }
ui->graphicsView_aqcd->setScene(scene);
ui->graphicsView_aqcd->setStyleSheet("background: transparent;border:0px");


/*电压电流频率*/

        /*图表显示*/
        QLineSeries *series = new QLineSeries();

            series->append(0, 6);
            series->append(2, 4);
            series->append(3, 8);
            series->append(7, 4);
            series->append(10, 5);
            *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);


            for(float  index = 0; index < 10; index += 0.5)
            {
           series->append(index,qSin(index));
            }
            QChart *chart = new QChart();
            chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("Simple line chart example");

            ui->graphicsView_charts->setChart(chart);

         /*说明*/
            //电压说明
            ui->label_dy_sm->setText("分辨力0.1v、精度0.2%rdg+0.2%FS");

            //电流说明
            ui->label_dl_sm->setText("分辨力0.1A/1A，精度0.3%rdg+0.3%FS");

            //频率说明
            ui->label_pl_sm->setText("分辨力0.1Hz、精度0.05%");
}

 void MainWindow::show_ui_data(const QString & str)
 {
       ui->lineEdit_dy->setText(str);
 }

//解析数据 并显示数据
void ShowWorker::consumer()
{
    DataExchange::m_dataExchange->m_mutex.lock();
    if(DataExchange::m_dataExchange->m_cyclebuff.isEmpty())
        DataExchange::m_dataExchange->m_cond.wait(&DataExchange::m_dataExchange->m_mutex);
  QString* pstr = NULL;
   if(4 ==  DataExchange::m_dataExchange->m_cyclebuff.read((char*)&pstr,4))
   {
    qDebug() << pstr;
   qDebug() << *pstr;
   emit showResult(*pstr);
   delete pstr;
   }
   DataExchange::m_dataExchange->m_mutex.unlock();
}
