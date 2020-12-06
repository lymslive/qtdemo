#ifndef CHARTSETTINGDLG_H
#define CHARTSETTINGDLG_H

#include <QDialog>
#include "chart.h"

namespace Ui {
class ChartSettingDlg;
}

class ChartSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ChartSettingDlg(QWidget *parent = nullptr);
    ~ChartSettingDlg();

    void setFriendChart(Chart* chart);

private:
    void fillSettins();
    void updateSettings();

private slots:
    void onApply();
    void onClose();
    void onReset();

private:
    Ui::ChartSettingDlg *ui;
    Chart::SAxis m_axisX;
    Chart::SAxis m_axisY;

    QPointer<Chart> w_chart;
};

#endif // CHARTSETTINGDLG_H
