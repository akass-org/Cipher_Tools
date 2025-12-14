/*
******** Yumeyo's ARMY KNIFE（NetInfoChecker Qt Edition） ********
******** 2025© Ne0W0r1d
******** 2024-2025© Yumeyo
******** LGPL 2.1 License
******** This file about maininterface dependence ********
*/


#ifndef HOME_H
#define HOME_H
//所需头文件
#include <QMainWindow> //主窗口
#include <QNetworkAccessManager> //网络会话管理器
#include <QNetworkReply> // 网络回复
#include <QMenuBar> // 菜单栏
#include <QMenu>// 菜单
#include <QAction>// 指令
#include <QDesktopServices> // 与桌面交互服务
#include <QUrl> // QUrl类
#include <QMessageBox> // 标准对话框支持
#include <QHostInfo> // 主机名
#include <QHostAddress> // 主机地址
#include <QDateTime> // 时钟支持
#include <QNetworkInterface> // 网卡信息支持
#include <QList> // 动态数组支持
#include <QRegularExpression> // 正则表达式支持

QT_BEGIN_NAMESPACE
namespace Ui {
class home;
}
QT_END_NAMESPACE

class home : public QMainWindow
{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();
    void getwanv4(); // 获取广域v4信息
    void getwanv6(); // 获取广域v6信息
    void getisp(); // 获取ISP
    void getlan(); // 获取LAN相关
    void getpriority();// 查询IP优先级

private slots:
/* Help */
    /* 帮助 */
    void help_Blog_trigger();// 博客信号槽
    void help_Wiki_trigger();// Wiki 信号槽
    void help_About_trigger();// 关于信号槽

    /* 仓库 */
    void help_repoGithub_trigger();// Github 仓库信号槽
    void help_repoCNB_trigger();// CNB 仓库信号槽
    //void help_repoCodeberg_trigger();// Codeberg 仓库信号槽
    //void help_repoGitee_trigger();// Gitee 仓库信号槽

    /* 更新日志 */
    void help_logCNB_trigger();// CNB 更新日志信号槽
    //void help_logGithub_trigger();// Github 更新日志信号槽
    //void help_logCodeberg_trigger();// Codeberg 更新日志信号槽
    //void help_logGitee_trigger();// Gitee 更新日志信号槽

    /* 议题 */
    void help_issueCNB_trigger();// IssueCNB 信号槽
    void help_issueGithub_trigger();// IssueGithub 信号槽
    //void help_issueGitee_trigger();// IssueGitee 信号槽
    //void help_issueCodeberg_trigger();// IssueCodeberg 信号槽

/* 主页 */
    void HomeInfo_Refresh(); // 刷新按钮信号槽
    // void HomeInfo_Settings(); // 设置按钮信号槽
    // void HomeInfo_RecordToFile(); // 记录当前IP地址按钮
    // void HomeInfo_CheckRecorded(); //查询已记录按钮
    /* Tools */
    void Tools_MOWeb_Trigger(); // 在线版多出口信号槽
    //void Tools_MOQt_Trigger();
private:
    Ui::home *ui;
    QNetworkAccessManager *sessionNet;
    QString ipv4; // V4 回调
    QString ipv6; // V6 回调
};
#endif // HOME_H
