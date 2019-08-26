#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QObject>
#include <QDebug>
class mythread : public QObject
{
    Q_OBJECT
public:
    explicit mythread(QObject *parent = nullptr);

signals:

public slots:

    void time();


};

#endif // MYTHREAD_H
