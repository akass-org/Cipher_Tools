/*
******** Yumeyo's ARMY KNIFE（NetInfoChecker Qt Edition） ********
******** 2025© Ne0W0r1d
******** 2024-2025© Yumeyo
******** LGPL 2.1 License
******** This file about "about" dependence ********
*/

#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QDialog>
#include <QSysInfo>
#include <QMessageBox>
#include <QAction>
namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

private:
    Ui::about *ui;
};

#endif // ABOUT_H
