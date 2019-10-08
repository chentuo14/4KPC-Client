#include "stackwidgetone.h"
#include "ui_stackwidgetone.h"
#include <QDebug>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDir>

StackWidgetOne::StackWidgetOne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetOne)
{
    ui->setupUi(this);
    /* 标签设置 */
    m_labelTitle = new QLabel(this);
    m_labelTitle->setText("Hello,Ready for printing.");
    m_labelTitle->setStyleSheet("color:white");
    QFont font;
    font.setPointSize(25);
    m_labelTitle->setFont(font);
    m_labelTitle->setGeometry(100, 50, 400, 200);
    /* 打印按钮 */
    m_btnPrint = new QPushButton(this);
    m_btnPrint->setText("Print");
    m_btnPrint->setGeometry(100, 280, 150, 50);
    m_btnPrint->setStyleSheet("border:none;background-color:green;color:white");
    connect(m_btnPrint, &QPushButton::clicked, this, &StackWidgetOne::OnPrintBtnClicked);

    /* 设置按钮 */
    m_btnSetting = new QPushButton(this);
    m_btnSetting->setText("");
    m_btnSetting->setIcon(QIcon(":/buttonIcon/printsetting.png"));
    m_btnSetting->setGeometry(100, 200, 50, 50);
    m_btnSetting->setStyleSheet("/*border:1px solid rgb(105,105,105);*/QPushButton{border-radius:25px;background-color:rgba(255,255,255,200);}QPushButton:hover{border:1px solid rgb(0,0,255);}");
    m_settingTitle = new QLabel(this);
    m_settingTitle->setText("Print setting");
    m_settingTitle->setGeometry(160, 200, 140, 25);
    m_settingTitle->setFont(QFont("Arial", 15));
    m_settingTitle->setStyleSheet("color:rgba(255,255,255,200)");
    m_settingStatus = new QLabel(this);
    m_settingStatus->setText("more infos");
    m_settingStatus->setGeometry(160, 225, 140, 25);
    m_settingStatus->setFont(QFont("Arial", 10));
    m_settingStatus->setStyleSheet("color:rgb(0,0,255);");
    /* 历史按钮 */
    m_btnHistory = new QPushButton(this);
    m_btnHistory->setText("");
    m_btnHistory->setGeometry(300, 200, 50, 50);
    m_btnHistory->setStyleSheet("/*border:1px solid rgb(105,105,105);*/QPushButton{border-radius:25px;background-color:rgba(255,255,255,200);}QPushButton:hover{border:1px solid rgb(0,0,255);}");
    m_btnHistory->setIcon(QIcon(":/buttonIcon/printhistory.png"));

    m_historyTitle = new QLabel(this);
    m_historyTitle->setText("Print history");
    m_historyTitle->setGeometry(360, 200, 140, 25);
    m_historyTitle->setStyleSheet("color:rgba(255,255,255,200)");
    m_historyTitle->setFont(QFont("Arial", 15));

    m_historyStatus = new QLabel(this);
    m_historyStatus->setText("more infos");
    m_historyStatus->setGeometry(360, 225, 140, 25);
    m_historyStatus->setFont(QFont("Arial", 10));
    m_historyStatus->setStyleSheet("color:rgb(0,0,255);");
    /* 设置定时器获取当前时间 */
    m_checkTimeTimer = new QTimer(this);
    m_checkTimeTimer->setInterval(60*1000*10);  /* 10分钟 */
    connect(m_checkTimeTimer, &QTimer::timeout, this, &StackWidgetOne::CheckTimeTimerSlot);
//    m_checkTimeTimer->start();
}

StackWidgetOne::~StackWidgetOne()
{
    delete ui;
}

//CheckTimeTimerSlot 定时器判断时间
void StackWidgetOne::CheckTimeTimerSlot()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    qDebug()<<currentTime.toString("hh:mm:ss")<<endl<<QString::number(QTime::currentTime().hour());
    //    if(QTime::hour())
}

void StackWidgetOne::OnPrintBtnClicked()
{
    qDebug()<<"print button clicked";
//    emit(btnPrintClicked(this->height()));
    QFileDialog fileDialog;
    fileDialog.setWindowFlags(Qt::FramelessWindowHint);
    fileDialog.setStyleSheet("background-color:red;");
    QString printName = fileDialog.getOpenFileName(this, "select file", QDir::homePath(), "*.ssj", 0, QFileDialog::DontUseNativeDialog);
    if(printName.isEmpty())
        return;
    emit(btnPrintClicked(this->width()));

}

void StackWidgetOne::OnHistoryBtnClicked()
{
    emit(btnHistoryClicked());
}

void StackWidgetOne::OnSettingBtnClicked()
{
    emit(btnSettingClicked());
}
