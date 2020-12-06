#include "serialsource.h"
#include "chart.h"

SerialSource::SerialSource(QObject *parent) : QObject(parent)
{
}

void SerialSource::connectChart(Chart *chart)
{
    w_chart = chart;
}

void SerialSource::pushPoint(QPointF p, bool sendSignal)
{
    if (w_chart == nullptr)
    {
        return;
    }

    w_chart->addPoint(p, sendSignal);
    if (sendSignal)
    {
        emit sendPoint(p);
    }

    m_info.dataCount++;
    if (p.x() < m_info.xMin)
    {
        m_info.xMin = p.x();
    }
    if (p.x() > m_info.xMax)
    {
        m_info.xMax = p.x();
    }
    if (p.y() < m_info.yMin)
    {
        m_info.yMin = p.y();
    }
    if (p.y() > m_info.yMax)
    {
        m_info.yMax = p.y();
    }
}
