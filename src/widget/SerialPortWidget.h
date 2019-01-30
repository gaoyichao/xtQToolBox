#ifndef SERIAL_PORT_WIDGET_H
#define SERIAL_PORT_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QSerialPort>

#include <QGroupBox>
#include <QLabel>
#include <QComboBox>


class SerialPortWidget : public QWidget
{
    Q_OBJECT

public:
    SerialPortWidget(QWidget *parent = 0);

public:
    QString name() {
        return portComboBox.currentText();
    }

    int baud() {
        return baudComboBox.currentText().toInt();
    }

    QSerialPort::DataBits data_bits() {
        return static_cast<QSerialPort::DataBits>(
        dataBitComboBox.itemData(dataBitComboBox.currentIndex()).toInt());
    }

    QSerialPort::Parity parity() {
        return static_cast<QSerialPort::Parity>(
        checkComboBox.itemData(checkComboBox.currentIndex()).toInt());
    }

    QSerialPort::StopBits stop_bits() {
        return static_cast<QSerialPort::StopBits>(
        stopBitComboBox.itemData(stopBitComboBox.currentIndex()).toInt());
    }

    QSerialPort::FlowControl flow_ctrl() {
        return static_cast<QSerialPort::FlowControl>(
        flowCtrlComboBox.itemData(flowCtrlComboBox.currentIndex()).toInt());
    }

private:
    void FillPortInfo();
    void FillPortParam();

private slots:
    void CheckBaudRate(int idx);
    void ShowPortInfo(int idx);

private:
    QGridLayout portSelectGroupLayout;
    QGridLayout portParamGroupLayout;
    QGridLayout mainLayout;

    QGroupBox portSelectGroup;
    QGroupBox portParamGroup;

    QComboBox portComboBox;
    QLabel portDescLabel;
    QLabel portManuLabel;
    QLabel portSNumLabel;
    QLabel portLocationLabel;
    QLabel portVidLabel;
    QLabel portPidLabel;

    QLabel label[5];

    QComboBox baudComboBox;
    QComboBox dataBitComboBox;
    QComboBox checkComboBox;
    QComboBox stopBitComboBox;
    QComboBox flowCtrlComboBox;
};

#endif
