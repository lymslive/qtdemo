#include "serialport.h"
#include "settingsdialog.h"
#include "mainwindow.h"
#include "statusbar.h"
#include <QMessageBox>

SerialPort::SerialPort(QObject *parent) : SerialSource(parent)
{
    initSerial();
    m_settings = new SettingsDialog; // cannot set parent this: to fix
}

SerialPort::~SerialPort()
{
    if (m_settings != nullptr)
    {
        delete m_settings;
        m_settings = nullptr;
    }
}

void SerialPort::config()
{
    m_settings->show();
}

void SerialPort::start()
{
    openSerialPort();
}

void SerialPort::stop()
{
    closeSerialPort();
}

void SerialPort::initSerial()
{
    m_serial = new QSerialPort(this);

    connect(m_serial, &QSerialPort::readyRead, this, &SerialPort::readData);
    connect(m_serial,
        static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &SerialPort::handleError);
}

void SerialPort::readData()
{
    QByteArray data = m_serial->readAll();
    // console->putData(data);

    // simply assume a real numeric value
    QString strData(data);
    qreal realData = strData.toDouble();
    QPointF p(qreal(m_info.dataCount++), realData);
    pushPoint(p);
}

void SerialPort::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(MainWindow::global(), tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}

void SerialPort::openSerialPort()
{
    SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        // console->setEnabled(true);
        // console->setLocalEchoEnabled(p.localEchoEnabled);
        StatusBar::instance()->showMessage(
                    tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl)
                    );
    }
    else
    {
        QMessageBox::critical(MainWindow::global(), tr("Error"), m_serial->errorString());

        StatusBar::instance()->showMessage(tr("Open error"));
    }
}

void SerialPort::closeSerialPort()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
    }
    // console->setEnabled(false);
    StatusBar::instance()->showMessage(tr("Disconnected"));
}
