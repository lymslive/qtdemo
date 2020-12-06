#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "serialsource.h"
#include <QtSerialPort/QSerialPort>

class SettingsDialog;
class QSerialPort;

class SerialPort : public SerialSource
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = nullptr);
    ~SerialPort();

    virtual void config();
    virtual void start();
    virtual void stop();

    void openSerialPort();
    void closeSerialPort();
private:
    void initSerial();

private slots:
    void readData();
    void handleError(QSerialPort::SerialPortError error);

private:
    QPointer<SettingsDialog> m_settings;
    QPointer<QSerialPort> m_serial;
};

#endif // SERIALPORT_H
