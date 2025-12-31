/*
******** Cipher Tools ********
******** 2025© Ne0W0r1d ********
******** 2024-2025© Yumeyo ********
******** LGPL 3 License ********
******** Home ********
*/


#include "Home.h"
#include "About.h"
#include "ui_Home.h"
#include "version.h"
#include "tools/multiout.h"

home::home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::home)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height()); //固定大小（Fixed site）

    QString systemname = QSysInfo::kernelType();// 获取内核信息（Get Kernel Information）
    QString distro = QSysInfo::prettyProductName();// 获取发行版名称（Get Distro Name）
    QString systemver = QSysInfo::productVersion();// 获取系统版本（Get System Version）

    ui -> Version ->setText(AK_VERSION); // 主页应用版本（Home App Version）
    ui -> test_waring -> setText("Alpha 版本 || 请勿用于生产环境 || 请及时汇报BUG || 请勿滥用接口"); // 主页测试版警告（Home Testing Version Warning）

    home::HomeInfo_Refresh(); // 启动首次触发刷新（Trigger Auto Refresh）

    qInfo()<<"系统环境："<<systemname<<"；系统："<<distro<<"；系统版本："<<systemver; // 输出系统版本日志（Echo System Version Log）
    qInfo()<<"软件版本："<<AK_VERSION<<"；工具箱版本："<<AKT_VERSION; // 输出软件版本日志（Echo App Version Log），版本在 Main.cpp（Version in main.cpp）

    // 菜单栏：帮助
    connect(ui -> about, &QAction::triggered, this, &home::help_About_trigger); // 菜单栏 - 帮助：关于
    connect(ui -> wiki, &QAction::triggered, this, &home::help_Wiki_trigger); // 菜单栏 - 帮助：WIKI
    connect(ui -> blog, &QAction::triggered, this, &home::help_Blog_trigger);// 菜单栏-帮助：BLOG

    connect(ui -> repoCNB, &QAction::triggered, this, &home::help_repoCNB_trigger);// 菜单栏 - 帮助 - 查看源码：CNB
    connect(ui -> repoGithub, &QAction::triggered, this, &home::help_repoGithub_trigger);// 菜单栏 - 帮助 - 查看源码：Github
    connect(ui -> repoCodeberg, &QAction::triggered, this, &home::help_repoCodeberg_trigger);// 菜单栏 - 帮助 - 查看源码：Codeberg

    connect(ui -> uplog, &QAction::triggered, this, &home::help_log_trigger);// 菜单栏 - 帮助 - 更新日志

    connect(ui -> issueCNB, &QAction::triggered, this, &home::help_issueCNB_trigger);// 菜单栏 - 帮助 - 问题反馈：CNB
    connect(ui -> issueGithub, &QAction::triggered, this, &home::help_issueGithub_trigger);// 菜单栏 - 帮助 - 问题反馈：Github
    connect(ui -> issueCodeberg, &QAction::triggered, this, &home::help_issueCodeberg_trigger);// 菜单栏 - 帮助 - 问题反馈：Codeberg

    /* 菜单-工具 */
    connect(ui -> MOWeb, &QAction::triggered, this, &home::Tools_MOWeb_Trigger); // 工具：多出口

    /*主页：主机名*/
    QString localHostname = QHostInfo::localHostName(); // 主机名实现
    QString beforPCname = "主机名：";// setText | hostname 前的信息

    qInfo()<< beforPCname << localHostname;

    ui->hostname->setAlignment(Qt::AlignLeft);// 文本靠左
    ui->hostname->setText(beforPCname + localHostname);// 输出主机名：Hostname

    /*主页：按钮*/
    connect(ui -> refresh, &QPushButton::clicked, this, &home::HomeInfo_Refresh); // 刷新主页信息

}

home::~home()
{
    qInfo()<<tr("Exited");
    delete ui;
}

/* 刷新按键、首次获取 */
void home::HomeInfo_Refresh(){

    qInfo()<<"信息获取/刷新信号已收到，初始化UI并获取信息中";

    ui -> v4add -> setText("Loading......"); // v4地址ui: 初始化
    ui -> v6add -> setText("Loading......"); // v6地址ui: 初始化
    ui -> ispinfo -> setText("Loading......"); // isp UI: 初始化
    ui -> localv4add -> setText("Loading......"); // 局域网V4: UI初始化
    ui -> localv6add -> setText("Loading......"); // 局域网V6: UI初始化
    ui -> priority -> setText("Loading......"); // 优先级: UI初始化

    this->getwanv6(); // 执行公网 V6 获取
    getlan(); // 执行本地获取
    getwanv4(); // 执行公网 V4 获取
    getpriority(); // 优先级获取

}

void home::getwanv4() // 公网 IPv4（Public IPv4）
{
    static QNetworkAccessManager *v4manager = new QNetworkAccessManager(this); // 设置新的QNAM
    QNetworkRequest request(QUrl("https://4.ipw.cn")); // 设置Request API为ipw.cn（TODO LIST - 支持多API，并研究出口API）
    QNetworkReply *v4reply = v4manager->get(request); // 设置Manager操作为request
    connect(v4reply, &QNetworkReply::finished, this, [this, v4reply]() { // 连接V4 Reply

        if (v4reply->error() == QNetworkReply::NoError) { // 判定是否有错误
            this->ipv4 = QString(v4reply->readAll()).trimmed(); // 设置IPV4变量为v4返回信息
            ui -> v4add -> setText(ipv4); // 显示在UI中
            if (!ipv4.isEmpty())
                getisp();
        } else {
            QString ipv4_error = v4reply->errorString();
            qCritical() << "请求失败:" << v4reply->errorString(); // 输出错误信息
            ui -> v4add -> setText("请求失败🐱，请检查日志🐱"); // 输出错误UI
        }

        v4reply->abort(); // 终止 v4reply 函数，优化内存泄露
        v4reply->deleteLater(); // 从我的内存滚出去
    });
}
/*以下代码同理*/

// 获得 V6 公网 IP
void home::getwanv6()
{

    static QNetworkAccessManager *v6manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://6.ipw.cn"));
    QNetworkReply *v6reply = v6manager->get(request);
    connect(v6reply, &QNetworkReply::finished, this, [this, v6reply]() {

        if (v6reply->error() == QNetworkReply::NoError) {
            QString ipv6 = QString(v6reply->readAll()).trimmed();
            ui -> v6add -> setText(ipv6);
        } else {
            qCritical() << "请求失败:" << v6reply->errorString();
            ui -> v6add -> setText("查询失败🐱看看右边有没有输出喵，如果没有请检查日志喵");
        }

        v6reply->abort();
        v6reply->deleteLater();

    });
}

// 获得 ISP
void home::getisp() {
    if (ipv4.isEmpty())
        return;
    static  QNetworkAccessManager *ispget = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://cip.cc/"+ ipv4));
    QNetworkReply *ispreply = ispget->get(request);
    connect(ispreply, &QNetworkReply::finished, this, [this, ispreply]() {
        if (ispreply->error() == QNetworkReply::NoError) {

            QString replyText = QString::fromUtf8(ispreply->readAll());
            QString isp;

            static const QRegularExpression regex(R"(数据二\s*:\s*(.*))");// 正则表达式提取
            QRegularExpressionMatch match = regex.match(replyText);

            if (match.hasMatch()) {
                isp = match.captured(1).trimmed();
                ui->ispinfo->setText(isp);
            } else {
                isp = "查询不到喵🐱，请检查日志🐱";
                ui->ispinfo->setText(isp);
                qWarning() << "查询不到喵：" <<ispreply->errorString();
            }
        }else{

            qCritical() << "请求失败喵：" <<ispreply->errorString();
            ui -> ispinfo -> setText("请求失败喵，请检查日志🐱");
        }
        ispreply->abort();
        ispreply->deleteLater();
    });

}

// 执行优先级获取

void home::getpriority(){ // 连接优先级
    static QNetworkAccessManager *priorityget = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("https://test.ipw.cn"));
    QNetworkReply *priorityreply = priorityget->get(request);

    connect(priorityreply, &QNetworkReply::finished, this, [this, priorityreply](){
        if(priorityreply->error() == QNetworkReply::NoError){

            QString res = QString::fromUtf8(priorityreply->readAll()).trimmed(); // 数据转换（原始字节 -> UTF8 字符串）
            QString pri;
            QString prefix_pri = "IP 优先模式："; // pri 输出到 UI 的变量前缀
            QHostAddress addr(res); // 设置 Qt IP 地址变量 abbr，尝试解析 res（resolve 简写成 res 了） 变量
            if (addr.protocol() == QAbstractSocket::IPv6Protocol) { // 确认 abbr 是 ipv6，则输出 V6 优先
                pri = "IPv6 优先";
            } else if (addr.protocol() == QAbstractSocket::IPv4Protocol) { // 回退识别是否是 V4
                pri = "IPv4 优先";
            }else{
                qCritical() << "请求失败:" << priorityreply->errorString();
            }

            ui -> priority -> setText(prefix_pri+pri);
        }
        priorityreply->abort();
        priorityreply->deleteLater();
    });

}

// 本地获取
void home::getlan(){
    QString lanv4_add, lanv6_add, macadd;
    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces(); // 获取所有网卡
    //qDebug()<<interfaces;
    for (const QNetworkInterface &iface : interfaces) {
        if (!iface.flags().testFlag(QNetworkInterface::IsUp) || //是否启用
            !iface.flags().testFlag(QNetworkInterface::IsRunning) || // 是否运行
            iface.flags().testFlag(QNetworkInterface::IsLoopBack)) // 是否回环
            continue; // 遍历后继续
        macadd = iface.hardwareAddress();// 设置macadd为MAC地址
        //qInfo()<< macadd << iface.humanReadableName();
        ui->Mac->setText(macadd + "（" + iface.humanReadableName() + "）"); // 设置UI: Mac地址为macadd变量

        for (const QNetworkAddressEntry &entry : iface.addressEntries()) { // 遍历接口地址
            QHostAddress ip = entry.ip(); // 获取IP地址
            if (ip.protocol() == QAbstractSocket::IPv4Protocol) {// 检测是否有V4

                lanv4_add = ip.toString(); // 获取V4字符串
                ui -> localv4add -> setText(lanv4_add.isEmpty() ? "查询失败喵🐱！请检查网络配置🐱！" : lanv4_add);// UI：输出V4字符串

                if(lanv4_add.isEmpty()){
                    qCritical() << "请检查网络配置喵🐱 IPv4" <<lanv4_add.isEmpty();
                }

            } else if (ip.protocol() == QAbstractSocket::IPv6Protocol) {//检测是否有V6
                if (!ip.toString().startsWith("fe80"))// 屏蔽本地IP地址
                    lanv6_add = ip.toString(); // 获取V6字符串
                ui -> localv6add -> setText(lanv6_add.isEmpty() ? "请求失败喵🐱请把鼠标放在我上面喵" : lanv6_add); // UI：输出V6字符串
                ui -> localv6add -> setToolTip(lanv6_add.isEmpty() ? "请手动检查IP ADDR/IPCONFIG喵🐱是否存在V6地址喵" : lanv6_add);

                if(lanv6_add.isEmpty()){
                    qCritical() << "请检查网络配置喵🐱 IPv6" <<lanv6_add.isEmpty();
                }

            }
        }

        QString lanip_tooltip, MAC_tooltip;

        for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces()) {

            lanip_tooltip += "<b>" + iface.humanReadableName() + "</b><br>";
            MAC_tooltip += "<b>" + iface.humanReadableName() + "</b><br>";
            MAC_tooltip += "&nbsp;&nbsp;MAC: " + iface.hardwareAddress() + "<br>";

            for (const QNetworkAddressEntry &entry : iface.addressEntries()) {
                QHostAddress ip = entry.ip();

                if (ip.protocol() == QAbstractSocket::IPv4Protocol) {
                    lanip_tooltip += "&nbsp;&nbsp;IPv4: " + ip.toString() + "<br>";
                } else if (ip.protocol() == QAbstractSocket::IPv6Protocol &&
                           !ip.toString().startsWith("fe80")) {
                    lanip_tooltip += "&nbsp;&nbsp;IPv6: " + ip.toString() + "<br>";
                }
            }

            lanip_tooltip += "<br>";
        }

        ui->localv4->setToolTip(lanip_tooltip);
        ui->currentMac->setToolTip(MAC_tooltip);
    }
}

/* 菜单栏业务相关定义 */

/* 工具实现 */

/* 多出口在线版 - 使用 Qt 桌面服务
void home::Tools_MOWeb_Trigger(){
    qInfo()<<"muti_out_website_trigger";

    QUrl MowebUrl("https://raw.githack.com/yumeyo23/netinfochecker/main/checker-web.html");
    QDesktopServices::openUrl(MowebUrl);

    qDebug() << "桌面服务信号已发出，请检查浏览器 MutiOutWeb";
}
*/

/* 多出口在线版 - 使用 Qt Web Engine */
void home::Tools_MOWeb_Trigger(){
    qInfo()<<"已触发 MOUT";

    MultiOut *MODialog = new MultiOut(this);   // 加载窗口
    MODialog->setAttribute(Qt::WA_DeleteOnClose); // 关闭窗口后删除对象
    MODialog->setModal(false);
    MODialog->show();
    qDebug() << "请检查窗口 MutiOutWeb";
}


/*打开文档页*/

void home::help_Blog_trigger(){

    qInfo()<<"已触发help_Wiki_trigger";

    QUrl BlogUrl("https://ne0w0r1d.top");//使用QUrl定义*Wiki URL*
    QDesktopServices::openUrl(BlogUrl);//用Qt桌面服务打开*Wiki URL*

    qDebug() << "桌面服务信号已发出，请检查浏览器 Blog";

    /*以下菜单栏相关代码同理 QUrl & Desktup Services*/

}

/* 打开文档页 */
void home::help_Wiki_trigger(){

    qInfo()<<"已触发help_Wiki_trigger";

    QUrl WikiUrl("https://ct.ne0w0r1d.top");// 使用QUrl定义*Wiki URL*
    QDesktopServices::openUrl(WikiUrl);// 用Qt桌面服务打开*Wiki URL*

    qDebug() << "桌面服务信号已发出，请检查浏览器 Wiki";

}
/*打开 CNB*/
void home::help_repoCNB_trigger(){

    qInfo()<<"已触发help_repoCNB_trigger";

    QUrl cnb_repo("https://cnb.cool/neoengine_dev/Cipher_Tools");
    QDesktopServices::openUrl(cnb_repo);

    qDebug() << "桌面服务信号已发出，请检查浏览器 CNB Repo";

}
/*打开 github*/
void home::help_repoGithub_trigger(){

    qInfo()<<"已触发help_repoGithub_trigger";

    QUrl wikiurl("https://github.com/akass-org/Cipher_Tools/");
    QDesktopServices::openUrl(wikiurl);

    qDebug() << "打开Github信号已发出，请检查浏览器";

}

/*打开 Codeberg */
void home::help_repoCodeberg_trigger(){

    qInfo()<<"已触发help_repoGithub_trigger";

    QUrl wikiurl("https://codeberg.org/Ne0W0r1d/Cipher_Tools/");
    QDesktopServices::openUrl(wikiurl);

    qDebug() << "打开Github信号已发出，请检查浏览器";

}

/*打开关于窗口*/
void home::help_About_trigger(){

    about *aboutWidget = new about(this);//打开about组件
    aboutWidget->setAttribute(Qt::WA_DeleteOnClose);//
    aboutWidget->show();//exec为模态，show为非模态，改为非模态显示避免影响操作
    qDebug()<<aboutWidget<<"aboutWidget 已打开，请检查窗口状态";

}

/*打开更新日志*/
void home::help_log_trigger(){

    QUrl updateurl("https://ct.ne0w0r1d.top/update/");
    QDesktopServices::openUrl(updateurl);
    qDebug() << "打开更新日志信号已发出，请检查浏览器";

}

/*IssueCNB*/
void home::help_issueCNB_trigger(){

    QUrl issuecnb("https://cnb.cool/neoengine_dev/Cipher_Tools/-/issues");
    QDesktopServices::openUrl(issuecnb);
    qDebug() << "打开CNB议题 信号已发出，请检查浏览器";

}

/*IssueGithub*/
void home::help_issueGithub_trigger(){

    QUrl issuegithub("https://github.com/akass-org/Cipher_Tools/issues");
    QDesktopServices::openUrl(issuegithub);
    qDebug() << "打开Github议题已发出，请检查浏览器";

}

/*IssueCodeberg*/
void home::help_issueCodeberg_trigger(){

    QUrl issuegithub("https://codeberg.com/Ne0W0r1d/Cipher_Tools/issues");
    QDesktopServices::openUrl(issuegithub);
    qDebug() << "打开Github议题已发出，请检查浏览器";

}





