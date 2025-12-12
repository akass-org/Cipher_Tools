/*
******** Cipher Tools ********
******** 2025© Ne0W0r1d ********
******** 2024-2025© Yumeyo ********
******** LGPL 3 License ********
******** About ********
*/


#include "About.h"
#include "ui_About.h"
#include "version.h"

about::about(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::about)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    qDebug()<< "关于窗口已启动 Fuck About" ;

    QString systemname = QSysInfo::kernelType();// 获取内核信息
    QString distro = QSysInfo::prettyProductName();// 获取发行版名称
    QString systemver = QSysInfo::productVersion();// 获取系统版本

    ui->softver_info->setText(AK_VERSION);//版本信息
    ui->toolversion->setText(AKT_VERSION);//版本信息
    ui->env->setText(systemname.toUpper() + " (" + distro + ")");// 显示系统环境

    connect(ui->aboutqt, &QPushButton::clicked, this, [=]() {
        QMessageBox::aboutQt(this, "关于 Qt");
    }); //打开关于 Qt

}

about::~about()
{
    delete ui;
}
