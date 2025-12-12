/*
******** Cipher Tools ********
******** 2025© Ne0W0r1d ********
******** 2024-2025© Yumeyo ********
******** LGPL 3 License ********
******** Tools/WOL ********
*/

#include "wakenow.h"
#include "ui_wakenow.h"

WakeNow::WakeNow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WakeNow)
{
    ui->setupUi(this);
}

WakeNow::~WakeNow()
{
    delete ui;
}
