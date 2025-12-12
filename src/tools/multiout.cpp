#include "multiout.h"
#include "ui_multiout.h"

MultiOut::MultiOut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiOut)
{
    ui->setupUi(this);
}

MultiOut::~MultiOut()
{
    delete ui;
}
