#include <QtWidgets>
#include <SerialPortWidget.h>

#include <QSerialPortInfo>

SerialPortWidget::SerialPortWidget(QWidget *parent)
    : QWidget(parent)
{
    portSelectGroupLayout.addWidget(&portComboBox, 0, 0);
    portSelectGroupLayout.addWidget(&portDescLabel, 1, 0);
    portSelectGroupLayout.addWidget(&portManuLabel, 2, 0);
    portSelectGroupLayout.addWidget(&portSNumLabel, 3, 0);
    portSelectGroupLayout.addWidget(&portLocationLabel, 4, 0);
    portSelectGroupLayout.addWidget(&portVidLabel, 5, 0);
    portSelectGroupLayout.addWidget(&portPidLabel, 6, 0);
    portSelectGroup.setTitle(tr("选择串口"));
    portSelectGroup.setLayout(&portSelectGroupLayout);

    label[0].setText(tr("波特率:"));
    label[1].setText(tr("数据位:"));
    label[2].setText(tr("校验位:"));
    label[3].setText(tr("停止位:"));
    label[4].setText(tr("流控制:"));
    portParamGroupLayout.addWidget(&label[0], 0, 0);
    portParamGroupLayout.addWidget(&label[1], 1, 0);
    portParamGroupLayout.addWidget(&label[2], 2, 0);
    portParamGroupLayout.addWidget(&label[3], 3, 0);
    portParamGroupLayout.addWidget(&label[4], 4, 0);
    portParamGroupLayout.addWidget(&baudComboBox, 0, 1);
    portParamGroupLayout.addWidget(&dataBitComboBox, 1, 1);
    portParamGroupLayout.addWidget(&checkComboBox, 2, 1);
    portParamGroupLayout.addWidget(&stopBitComboBox, 3, 1);
    portParamGroupLayout.addWidget(&flowCtrlComboBox, 4, 1);
    portParamGroup.setTitle(tr("串口参数"));
    portParamGroup.setLayout(&portParamGroupLayout);

    connect(&portComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowPortInfo(int)));
    connect(&baudComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(CheckBaudRate(int)));

    FillPortInfo();
    FillPortParam();

    mainLayout.addWidget(&portSelectGroup, 0, 0);
    mainLayout.addWidget(&portParamGroup, 0, 1);

    setLayout(&mainLayout);
    setWindowTitle(tr("串口配置"));
}

void SerialPortWidget::FillPortParam()
{
    // 添加波特率
    baudComboBox.addItem(QStringLiteral("460800"), 460800);
    baudComboBox.addItem(QStringLiteral("2008000"), 2008000);
    baudComboBox.addItem(QStringLiteral("250000"), 250000);
    baudComboBox.addItem(QStringLiteral("128000"), 128000);
    baudComboBox.addItem(QStringLiteral("115200"), 115200);
    baudComboBox.addItem(QStringLiteral("76800"), 76800);
    baudComboBox.addItem(QStringLiteral("57600"), 57600);
    baudComboBox.addItem(QStringLiteral("38400"), 38400);
    baudComboBox.addItem(tr("custom"));
    baudComboBox.setCurrentIndex(4);
    // 数据位
    dataBitComboBox.addItem(QStringLiteral("5"), QSerialPort::Data5);
    dataBitComboBox.addItem(QStringLiteral("6"), QSerialPort::Data6);
    dataBitComboBox.addItem(QStringLiteral("7"), QSerialPort::Data7);
    dataBitComboBox.addItem(QStringLiteral("8"), QSerialPort::Data8);
    dataBitComboBox.setCurrentIndex(3);
    // 校验位
    checkComboBox.addItem(tr("None"), QSerialPort::NoParity);
    checkComboBox.addItem(tr("Even"), QSerialPort::EvenParity);
    checkComboBox.addItem(tr("Odd"), QSerialPort::OddParity);
    checkComboBox.addItem(tr("Mark"), QSerialPort::MarkParity);
    checkComboBox.addItem(tr("Space"), QSerialPort::SpaceParity);
    // 停止位
    stopBitComboBox.addItem(QStringLiteral("1"), QSerialPort::OneStop);
    stopBitComboBox.addItem(QStringLiteral("1.5"), QSerialPort::OneAndHalfStop);
    stopBitComboBox.addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    // 流控制
    flowCtrlComboBox.addItem(tr("None"), QSerialPort::NoFlowControl);
    flowCtrlComboBox.addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    flowCtrlComboBox.addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void SerialPortWidget::FillPortInfo()
{
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : tr("N/A"))
             << (!manufacturer.isEmpty() ? manufacturer : tr("N/A"))
             << (!serialNumber.isEmpty() ? serialNumber : tr("N/A"))
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : tr("N/A"))
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : tr("N/A"));

        portComboBox.addItem(list.first(), list);
    }
    portComboBox.addItem(tr("Custom"));
}

void SerialPortWidget::CheckBaudRate(int idx)
{
    bool isBaud = baudComboBox.itemData(idx).isValid();
    baudComboBox.setEditable(!isBaud);

    if (!isBaud) {
        baudComboBox.clearEditText();
    }
}

void SerialPortWidget::ShowPortInfo(int idx)
{
    if (idx == -1)
        return;

    QStringList list = portComboBox.itemData(idx).toStringList();
    portDescLabel.setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr("N/A")));
    portManuLabel.setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr("N/A")));
    portSNumLabel.setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr("N/A")));
    portLocationLabel.setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr("N/A")));
    portVidLabel.setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr("N/A")));
    portPidLabel.setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr("N/A")));
}
