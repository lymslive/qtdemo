/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QGestureEvent;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
public:
    explicit Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~Chart();

    void init();
    void reset();
    void addPoint(const QPointF& p, bool updateTitle = true);

public:
    struct SAxis
    {
        QString title;
        qreal min = 0;
        qreal max = 0;
        int precision = 0;
        int majorTick = 0;
        int minorTick = 0;
    };

    void defaultAxisX(SAxis& axisInfo);
    void defaultAxisY(SAxis& axisInfo);
    void setAxisInfo(QValueAxis *axis, const SAxis& axisInfo);
    void getAxisInfo(QValueAxis *axis, SAxis& axisInfo);

protected:
    bool sceneEvent(QEvent *event);

private:
    bool gestureEvent(QGestureEvent *event);

private:
    QPointer<QLineSeries> m_series;
    QPointer<QValueAxis> m_axisX;
    QPointer<QValueAxis> m_axisY;

    QString m_title{"Realtime Curve Monitor"};

public:
    QLineSeries *series() { return m_series; }
    QValueAxis *axisX() { return m_axisX; }
    QValueAxis *axisY() { return m_axisY; }
};

#endif // CHART_H