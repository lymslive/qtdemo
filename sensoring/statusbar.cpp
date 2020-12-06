#include "statusbar.h"
#include <QLabel>
#include <QStatusBar>

void StatusBar::init(QStatusBar *statusBar)
{
    if (statusBar == nullptr)
    {
        return;
    }
    w_statusBar = statusBar;

    m_statusLabel = new QLabel;
    w_statusBar->addWidget(m_statusLabel);
}

StatusBar *StatusBar::instance(QStatusBar *statusBar)
{
    static StatusBar instance;
    if (statusBar != nullptr)
    {
        if (instance.w_statusBar == nullptr)
        {
            instance.init(statusBar);
        }
        else
        {
            // can only init once;
        }
    }
    return &instance;
}

void StatusBar::showMessage(QString msg)
{
    m_statusLabel->setText(msg);
}

void StatusBar::showPoint(QPointF p)
{
    QString msg("current point: (%1, %2)");
    msg = msg.arg(p.x()).arg(p.y());
    showMessage(msg);
}
