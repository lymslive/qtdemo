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

#include "chartview.h"
#include "chart.h"
#include "chartsettingdlg.h"
#include "serialdemo.h"
#include "serialport.h"
#include <QtGui/QMouseEvent>

ChartView::ChartView(Chart *chart, QWidget *parent) :
    QChartView(chart, parent),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);

    // m_chart = dynamic_cast<Chart*>(chart);
    m_chart = chart;
    if (m_chart != nullptr)
    {
        m_chart->init();
        m_demo = new SerialDemo(this);
        m_demo->connectChart(m_chart);
        // show a demo full static cuve as welcome at start time
        m_demo->pullAll();
    }

    m_port = new SerialPort(this);
}

ChartView::~ChartView()
{
}

bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin)
    {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching)
        return;
    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching)
        m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart()->setAnimationOptions(QChart::SeriesAnimations);

    QChartView::mouseReleaseEvent(event);
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;

    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void ChartView::initChartSettingDlg()
{
    if (m_chartSetting != nullptr)
    {
        return; // only init once!
    }
    m_chartSetting = new ChartSettingDlg(this);
    m_chartSetting->setFriendChart(m_chart);
}

void ChartView::startDemo()
{
    m_port->connectChart(nullptr);
    m_demo->connectChart(m_chart);
    m_chart->reset();
    m_demo->start();
}

void ChartView::stopDemo()
{
    if (m_demo != nullptr)
    {
        m_demo->stop();
    }
}

void ChartView::openChartSettingDlg()
{
    if (m_chart == nullptr)
    {
        return;
    }

    if (m_chartSetting == nullptr)
    {
        initChartSettingDlg();
    }

    m_chartSetting->show();
}

void ChartView::openSerialSettingDlg()
{
    m_port->config();
}

void ChartView::openSerialPort()
{
    m_demo->connectChart(nullptr);
    m_port->connectChart(m_chart);
    m_chart->reset();
    m_port->openSerialPort();
}

void ChartView::closeSerialPort()
{
    m_port->closeSerialPort();
}
