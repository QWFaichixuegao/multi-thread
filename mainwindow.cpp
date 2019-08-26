#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"main:"<<QThread::currentThreadId();


    worker = new mythread();
    QTimer * asd =new QTimer();                              //创建线程容器

    /***************************测试三选一**************************************/
    connect(asd,SIGNAL(timeout()),worker,SLOT(time()));      //定时器测试
    asd->start(1000);

    //connect(&thread,SIGNAL(started()),worker,SLOT(time()));//thread started信号测试

    //connect(this,&MainWindow::click_test,worker,&mythread::time);//点击测试
    /*************************************************************************/

    worker->moveToThread(&thread);                           //将创建的耗时操作移动到线程容器中
    thread.start();                                          //开启多线程
    connect(&thread,&QThread::finished, worker,&QObject::deleteLater);
    connect(&thread,&QThread::finished,&thread,&QThread::deleteLater);
}

MainWindow::~MainWindow()
{
    thread.quit();//退出事件循环
    thread.wait();//释放线程槽函数资源
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
  // worker->time();//直接调用  因为是在主线程当中调用，还是占用主线程 可打开试试
   emit click_test();

}
