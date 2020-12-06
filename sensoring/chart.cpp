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

#include "chart.h"
#include "statusbar.h"
#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtCore/QtMath>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(QChart::ChartTypeCartesian, parent, wFlags)
{
    m_series = nullptr;
    m_axisX = nullptr;
    m_axisY = nullptr;

    // Seems that QGraphicsView (QChartView) does not grab gestures.
    // They can only be grabbed here in the QGraphicsWidget (QChart).
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

Chart::~Chart()
{
}

void Chart::defaultAxisX(SAxis& axisInfo)
{
    axisInfo.title = "time";
    axisInfo.min = 0;
    axisInfo.max = 720;
    axisInfo.precision = 1; // "%.1f";
    axisInfo.majorTick = 20;
    axisInfo.minorTick = 5;
}

void Chart::defaultAxisY(SAxis& axisInfo)
{
    axisInfo.title = "value";
    axisInfo.min = -120;
    axisInfo.max = 120;
    axisInfo.precision = 1; // "%.1f";
    axisInfo.majorTick = 10;
    axisInfo.minorTick = 5;
}

void Chart::setAxisInfo(QValueAxis *axis, const SAxis& axisInfo)
{
    axis->setTitleText(axisInfo.title);
    axis->setRange(axisInfo.min, axisInfo.max);
    QString format = QString("%.%1f").arg(axisInfo.precision);
    axis->setLabelFormat(format);
    axis->setTickCount(axisInfo.majorTick + 1);
    axis->setMinorTickCount(axisInfo.minorTick - 1);
}

void Chart::getAxisInfo(QValueAxis *axis, Chart::SAxis &axisInfo)
{
    if (axis == nullptr)
    {
        return;
    }
    axisInfo.title = axis->titleText();
    axisInfo.min = axis->min();
    axisInfo.max = axis->max();
    axisInfo.majorTick = axis->tickCount() - 1;
    axisInfo.minorTick = axis->minorTickCount() + 1;
    // format "%.2f": extract precision 2;
    {
        QString format = axis->labelFormat();
        QRegularExpressionMatch match;
        if (-1 != format.lastIndexOf(QRegularExpression("(\\d+)f"), -1, &match))
        {
            axisInfo.precision = match.captured(1).toInt();
        }
    }
}

void Chart::init()
{
    m_series = new QLineSeries();
    addSeries(m_series);

    setTitle(m_title);
    setAnimationOptions(QChart::SeriesAnimations);
    legend()->hide();

    // createDefaultAxes();

    m_axisX = new QValueAxis;
    m_axisY = new QValueAxis;

    SAxis axisInfo;
    defaultAxisX(axisInfo);
    setAxisInfo(m_axisX, axisInfo);
    defaultAxisY(axisInfo);
    setAxisInfo(m_axisY, axisInfo);

    setAxisX(m_axisX, m_series);
    setAxisY(m_axisY, m_series);
}

void Chart::reset()
{
    m_series->clear();
    setTitle(m_title);
}

void Chart::addPoint(const QPointF &p, bool updateTitle)
{
    if (m_series != nullptr)
    {
        m_series->append(p);
    }

    if (updateTitle)
    {
        QString curPoint(" (%1, %2)");
        curPoint = curPoint.arg(p.x()).arg(p.y());
        setTitle(m_title + curPoint);

        StatusBar::instance()->showPoint(p);
    }
}

bool Chart::sceneEvent(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent *>(event));
    return QChart::event(event);
}

bool Chart::gestureEvent(QGestureEvent *event)
{
    if (QGesture *gesture = event->gesture(Qt::PanGesture)) {
        QPanGesture *pan = static_cast<QPanGesture *>(gesture);
        QChart::scroll(-(pan->delta().x()), pan->delta().y());
    }

    if (QGesture *gesture = event->gesture(Qt::PinchGesture)) {
        QPinchGesture *pinch = static_cast<QPinchGesture *>(gesture);
        if (pinch->changeFlags() & QPinchGesture::ScaleFactorChanged)
            QChart::zoom(pinch->scaleFactor());
    }

    return true;
}
