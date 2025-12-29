#include "multiout.h"
#include "ui_multiout.h"

MultiOut::MultiOut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiOut)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());

    qputenv("QTWEBENGINE_CHROMIUM_FLAGS",
            "--enable-gpu "
            "--enable-zero-copy "
            "--ignore-gpu-blocklist "
            "--enable-features=CSSBackdropFilter");
    QFile mout(":/Resource/checker-web.html");
    if (!mout.open(QIODevice::ReadOnly)) {
        qWarning() << "未能打开文件！";
        return;
    }
    QString html = QString::fromUtf8(mout.readAll());
    ui->webEngineView->setHtml(html);
}

MultiOut::~MultiOut()
{
    delete ui;
}
