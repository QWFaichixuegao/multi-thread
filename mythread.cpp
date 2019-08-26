#include "mythread.h"

mythread::mythread(QObject *parent) : QObject(parent)
{

}


void mythread::time()
{
    qDebug()<<"mythread:" <<QThread::currentThreadId();
}
