#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QObject>
#include <QString>
#include <QPointF>

class QStatusBar;
class QLabel;

class StatusBar : public QObject
{
// single instance
private:
    StatusBar() {}

    void init(QStatusBar* statusBar);

public:
    static StatusBar* instance(QStatusBar* statusBar = nullptr);

    void showMessage(QString msg);
    void showPoint(QPointF p);

private:
    QStatusBar* w_statusBar = nullptr;
    QLabel* m_statusLabel = nullptr;
};

#endif // STATUSBAR_H
