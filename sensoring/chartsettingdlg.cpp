#include "chartsettingdlg.h"
#include "ui_chartsettingdlg.h"

ChartSettingDlg::ChartSettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartSettingDlg)
{
    ui->setupUi(this);

    connect(ui->ApplyPB, &QPushButton::clicked, this, &ChartSettingDlg::onApply);
    connect(ui->ResetPB, &QPushButton::clicked, this, &ChartSettingDlg::onReset);
    connect(ui->ClosePB, &QPushButton::clicked, this, &ChartSettingDlg::onClose);
}

ChartSettingDlg::~ChartSettingDlg()
{
    qDebug() << "~ChartSettingDlg";
    delete ui;
}

void ChartSettingDlg::setFriendChart(Chart *chart)
{
    if (chart == nullptr)
    {
        return;
    }

    w_chart = chart;
    w_chart->getAxisInfo(w_chart->axisX(), m_axisX);
    w_chart->getAxisInfo(w_chart->axisY(), m_axisY);
    fillSettins();
}

void ChartSettingDlg::fillSettins()
{
    QString strDouble = "%1";
    ui->xTitleEdit->setText(m_axisX.title);
    ui->xMinEdit->setText(strDouble.arg(m_axisX.min));
    ui->xMaxEdit->setText(strDouble.arg(m_axisX.max));
    ui->xPrecisionSpin->setValue(m_axisX.precision);
    ui->xMajorTickSpin->setValue(m_axisX.majorTick);
    ui->xMinorTickSpin->setValue(m_axisX.minorTick);

    ui->yTitleEdit->setText(m_axisY.title);
    ui->yMinEdit->setText(strDouble.arg(m_axisY.min));
    ui->yMaxEdit->setText(strDouble.arg(m_axisY.max));
    ui->yPrecisionSpin->setValue(m_axisY.precision);
    ui->yMajorTickSpin->setValue(m_axisY.majorTick);
    ui->yMinorTickSpin->setValue(m_axisY.minorTick);
}

void ChartSettingDlg::updateSettings()
{
    m_axisX.title = ui->xTitleEdit->text();
    m_axisX.min =  ui->xMinEdit->text().toDouble();
    m_axisX.max = ui->xMaxEdit->text().toDouble();
    m_axisX.precision = ui->xPrecisionSpin->value();
    m_axisX.majorTick = ui->xMajorTickSpin->value();
    m_axisX.minorTick = ui->xMinorTickSpin->value();

    m_axisY.title = ui->yTitleEdit->text();
    m_axisY.min =  ui->yMinEdit->text().toDouble();
    m_axisY.max = ui->yMaxEdit->text().toDouble();
    m_axisY.precision = ui->yPrecisionSpin->value();
    m_axisY.majorTick = ui->yMajorTickSpin->value();
    m_axisY.minorTick = ui->yMinorTickSpin->value();
}

void ChartSettingDlg::onApply()
{
    updateSettings();
    w_chart->setAxisInfo(w_chart->axisX(), m_axisX);
    w_chart->setAxisInfo(w_chart->axisY(), m_axisY);

    if (ui->AndCloseCB->isChecked())
    {
        onClose();
    }
}

void ChartSettingDlg::onClose()
{
    this->hide();
}

void ChartSettingDlg::onReset()
{
    w_chart->getAxisInfo(w_chart->axisX(), m_axisX);
    w_chart->getAxisInfo(w_chart->axisY(), m_axisY);
    fillSettins();
}
