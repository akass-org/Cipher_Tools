#ifndef MULTIOUT_H
#define MULTIOUT_H

#include <QDialog>
#include <QtWebEngineWidgets>
namespace Ui {
class MultiOut;
}

class MultiOut : public QDialog
{
    Q_OBJECT

public:
    explicit MultiOut(QWidget *parent = nullptr);
    ~MultiOut();

private:
    Ui::MultiOut *ui;
};

#endif // MULTIOUT_H
