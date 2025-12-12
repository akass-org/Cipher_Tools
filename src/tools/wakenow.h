#ifndef WAKENOW_H
#define WAKENOW_H

#include <QDialog>

namespace Ui {
class WakeNow;
}

class WakeNow : public QDialog
{
    Q_OBJECT

public:
    explicit WakeNow(QWidget *parent = nullptr);
    ~WakeNow();

private:
    Ui::WakeNow *ui;
};

#endif // WAKENOW_H
