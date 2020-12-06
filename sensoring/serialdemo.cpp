#include "serialdemo.h"

SerialDemo::SerialDemo(QObject *parent) : SerialSource(parent)
{
    // xtime = -1;
    // timer = nullptr;
}

SerialDemo::~SerialDemo()
{
}

void SerialDemo::start()
{
    if (timer == nullptr)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SerialDemo::generatePoint);
    }
    timer->start(1000);
    xtime = -1;
}

void SerialDemo::stop()
{
    if (timer != nullptr)
    {
        timer->stop();
    }
}

void SerialDemo::generatePoint()
{
    xtime++;
    if (xtime < 0)
    {
        return;
    }

    QPointF p = calculatePoint(xtime);
    pushPoint(p);
}

void SerialDemo::pullAll()
{
    for (int i = 0; i < 720; i++)
    {
        QPointF p = calculatePoint(i);
        pushPoint(p, false);
    }
}

QPointF SerialDemo::calculatePoint(int t)
{
    QPointF p((qreal) t, qSin(M_PI / 50 * t) * 100);
    p.ry() += qrand() % 20;
    return p;
}
