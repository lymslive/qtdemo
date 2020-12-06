#ifndef SERIALDEMO_H
#define SERIALDEMO_H

#include "serialsource.h"
#include <QTimer>
#include <QPointF> 

class SerialDemo : public SerialSource
{
    Q_OBJECT
public:
    explicit SerialDemo(QObject *parent = nullptr);
    ~SerialDemo();

    virtual void pullAll();

    void start();
    void stop();

private:
    void generatePoint();
    QPointF calculatePoint(int t);

private:
    QPointer<QTimer> timer;
    int xtime = -1; // point x
};

#endif // SERIALDEMO_H
