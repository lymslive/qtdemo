#ifndef SERIALSOURCE_H
#define SERIALSOURCE_H

#include <QObject>
#include <QtCharts>
#include <QPointer>

class Chart;

class SerialSource : public QObject
{
    Q_OBJECT
public:
    explicit SerialSource(QObject *parent = nullptr);
    virtual ~SerialSource() {}

    void connectChart(Chart* chart);

    void setSourceTitle(const QString& title)
    {
        m_info.title = title;
    }

    // pull all points as one full series line
    virtual void pullAll() {};
    virtual void config() {};
    virtual void start() {};
    virtual void stop() {};
    virtual void pause() {};

    struct Info
    {
        QString title;
        qreal xMin = 0;
        qreal xMax = 0;
        qreal yMin = 0;
        qreal yMax = 0;
        int dataCount = 0;
    };

    const Info* getInfo() const { return &m_info; }

protected:
    // push one pint each time
    void pushPoint(QPointF p, bool sendSignal = true);

signals:
    void sendPoint(QPointF);

protected:
    QPointer<Chart> w_chart;

    Info m_info;
};

#endif // SERIALSOURCE_H
