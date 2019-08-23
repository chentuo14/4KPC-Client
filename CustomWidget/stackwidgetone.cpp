#include "stackwidgetone.h"
#include "ui_stackwidgetone.h"
#include <QDebug>

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
    m_btnSetting->setStyleSheet("border:1px solid rgb(105,105,105);border-radius:25px;");
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
}
