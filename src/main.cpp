/*
******** Cipher Tools ********
******** 2025© Ne0W0r1d ********
******** 2024-2025© Yumeyo ********
******** LGPL 3 License ********
******** Version/Program Other Logic ********
*/

#include "Home.h" //主界面
#include <QFile> // 日志 - 文件系统
#include <QApplication> // Qt Widget（应用依赖）
#include <QTextStream> // 日志依赖 - 文本流输出
#include <QDebug> // 日志依赖 - Debug 系统
#include <QDateTime> // 日志依赖 - 时间系统
#include "version.h" // 统一输出版本号

// 版本号
QString AK_VERSION = "CIPHER.rana.alpha_snapshot.251214"; //主程序版本号
QString AKT_VERSION = "RANATOOLKIT.astra.prototype"; //该程序版本号请根据 Ne0W0r1d/Rana_Toolkit 进行编写，目前 Prototype 是因为工具箱并没有实现


// 自定义信息接口
void customMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    static QFile logFile("ArmyKnife.log"); //日志文件打开 / 生成

    // 如果无法打开日志则生成报错
    if (!logFile.isOpen()) {
        if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
            qCritical() << "无法打开日志文件是何意味？：" << logFile.errorString();
            return;
        }
    }

    QTextStream out(&logFile);//输入日志
    QString level;//等级变量，为输出文件带等级头

    // 定义输出日志的变量值
    switch (type) {
    case QtDebugMsg: // 对应 qDebug()
        level = "DEBUG - 调试";
        break;
    case QtInfoMsg: // 对应 qInfo()
        level = "INFO - 信息";
        break;
    case QtWarningMsg:// 对应 qWaring()
        level = "WARN - 警告";
        break;
    case QtCriticalMsg: // 对应 qCritical()
        level = "CRIT - 关键";
        break;
    case QtFatalMsg: // 对应 qFatal();
        level = "FATAL - 寄了";
        break;
    }
    // 日志时间
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ")
        << "[" << level << "] "
        << msg << "\n";
    out.flush();

    // 致命错误则终止程序
    if (type == QtFatalMsg) // 如果出现了 QtFatalMsg 报错
        abort();// 则直接终止

    // 自动清理日志
    if (logFile.size() > 2 * 1024 * 1024) { // 超过 2 MB
        logFile.resize(0); // 清空
    }
}
// Main 自动生成
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customMessageHandler); // 启用自定义信息 Handler
    home w;
    w.show();
    return a.exec();
}
