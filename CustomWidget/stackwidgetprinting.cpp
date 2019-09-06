#include "stackwidgetprinting.h"
#include "ui_stackwidgetprinting.h"
#include <QDebug>

StackWidgetPrinting::StackWidgetPrinting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetPrinting)
{
    ui->setupUi(this);
    int cycleLeftPosX = 100;
    int cycleLeftPosY = 100;
    /* 转圈 */
    m_cycleProcess = new CycleProcess(this);
    m_cycleProcess->setGeometry(cycleLeftPosX, cycleLeftPosY, 100, 100);\
    QFont printProgress("Arial", 20);
    m_cycleProcess->getCenterLabel()->setFont(printProgress);
    connect(this, &StackWidgetPrinting::onStartCycleSignal, m_cycleProcess, &CycleProcess::startCycleProcess);
    connect(this, &StackWidgetPrinting::onStopCycleSignal, m_cycleProcess, &CycleProcess::stopCycleProcess);
    emit(onStartCycleSignal(50));
    /* 文字状态 */
    m_statusTitle = new QLabel(this);
    m_statusTitle->setText("Printing...");
    m_statusTitle->setStyleSheet("/*border: 2px solid black;*/color:white");
    QFont title("Arial", 25);
    m_statusTitle->setFont(title);
    m_statusTitle->setGeometry(cycleLeftPosX+115, cycleLeftPosY, 200, 50);
    m_statusTitle->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    m_statusContext = new QLabel(this);
    m_statusContext->setText("machine is printing base layer");
    m_statusContext->setStyleSheet("/*border: 2px solid black;*/color:balck");
    QFont context("Arial", 10);
    m_statusContext->setFont(context);
    m_statusContext->setGeometry(cycleLeftPosX+115, cycleLeftPosY+25, 200, 50);
    m_statusTitle->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    /* 进度条 */
    m_pritingBar = new QProgressBar(this);
    m_pritingBar->setGeometry(cycleLeftPosX+110, cycleLeftPosY+70, 400, 20);
    m_pritingBar->setRange(0, 100);
    m_pritingBar->setTextVisible(false);
    m_pritingBar->setOrientation(Qt::Horizontal);
    m_pritingBar->setStyleSheet("  background:rgba(0,0,0,50);\
                                QProgressBar { \
                                   border: 2px solid black; \
                                   border-radius: 5px;\
                                    text-align:right\
                               }\
                               QProgressBar::chunk:enable { \
                                   background-color: #05B8CC; \
                                   width: 1px; \
                               }");
    /* 测试进度条计时器 */
    m_testTimer.setInterval(1000);
    connect(&m_testTimer, &QTimer::timeout, this, &StackWidgetPrinting::onTestTimer);
    m_testTimer.start();

    /* 取消按钮 */
    m_btnCancel = new QPushButton("Cancel", this);
    m_btnCancel->setGeometry(cycleLeftPosX+360, cycleLeftPosY+10, 50, 30);
    connect(m_btnCancel, &QPushButton::clicked, this, &StackWidgetPrinting::onCancelBtnClicked);
    /* 暂停按钮 */
    m_btnPasuse = new QPushButton("Pause", this);
    m_btnPasuse->setGeometry (cycleLeftPosX+300, cycleLeftPosY+10, 50, 30);
    /* 打印状态设置 */
    m_printStatusTable = new MyTableWidget(this);
    m_printStatusTable->onPrintLogoChange(1, PrintStatus::StatusPrinting);
    m_printStatusTable->onPrintStatusChange(1, PrintStatus::StatusPrinting);
//    m_printStatusTable->setTableSize();
}

StackWidgetPrinting::~StackWidgetPrinting()
{
    delete ui;
}

void StackWidgetPrinting::onCancelBtnClicked()
{
    qDebug()<<"onCancel signal";
    emit(onCancelSignal());
}

void StackWidgetPrinting::onTestTimer()
{
    m_progressValue++;
    onProgressValueChange(m_progressValue%100);
}

void StackWidgetPrinting::onProgressValueChange(int value)
{
    m_pritingBar->setValue(value);
    m_cycleProcess->setLabelText(QString("%1\%").arg(value));
    update();
}
