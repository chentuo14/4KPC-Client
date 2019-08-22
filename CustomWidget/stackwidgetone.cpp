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
    /* 设置按钮 */
    m_btnPrint = new QPushButton(this);
    m_btnPrint->setText("Print");
    m_btnPrint->setGeometry(100, 250, 150, 50);
    m_btnPrint->setStyleSheet("border:none;background-color:green;color:white");
    /* 设置定时器获取当前时间 */
    m_checkTimeTimer = new QTimer(this);
//    m_checkTimeTimer->setInterval(60*1000*10);  /* 10分钟 */
    m_checkTimeTimer->setInterval(1000);
    connect(m_checkTimeTimer, &QTimer::timeout, this, &StackWidgetOne::CheckTimeTimerSlot);
    m_checkTimeTimer->start();
}

StackWidgetOne::~StackWidgetOne()
{
    delete ui;
}

void StackWidgetOne::CheckTimeTimerSlot()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    qDebug()<<currentTime.toString("hh:mm:ss")<<endl<<QString::number(QTime::currentTime().hour());
//    if(QTime::hour())
}
