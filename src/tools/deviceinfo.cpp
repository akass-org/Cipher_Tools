/*
******** Cipher Tools ********
******** 2025© Ne0W0r1d ********
******** 2024-2025© Yumeyo ********
******** LGPL 3 License ********
******** Tools/Device ********
*/


/*  WARING!
 *  Windows plz use wmic
 *  And Linux plz use ls series or cat /proc
 *  Mac need more information
 */

#include "deviceinfo.h"
#include "ui_deviceinfo.h"
// #include "Home.h"

DeviceInfo::DeviceInfo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeviceInfo)
{
    ui->setupUi(this);

}

DeviceInfo::~DeviceInfo()
{
    delete ui;
}
