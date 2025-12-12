#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QDialog>

namespace Ui {
class DeviceInfo;
}

class DeviceInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceInfo(QWidget *parent = nullptr);
    ~DeviceInfo();

private:
    Ui::DeviceInfo *ui;
};

#endif // DEVICEINFO_H
