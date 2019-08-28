#include "stackwidgetprinting.h"
#include "ui_stackwidgetprinting.h"
#include <QDebug>

StackWidgetPrinting::StackWidgetPrinting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetPrinting)
{
    ui->setupUi(this);

    /* 转圈 */
    m_cycleProcess = new CycleProcess(this);
    m_cycleProcess->setGeometry(0, 0, 100, 100);
    connect(this, &StackWidgetPrinting::onStartCycleSignal, m_cycleProcess, &CycleProcess::startCycleProcess);
    connect(this, &StackWidgetPrinting::onStopCycleSignal, m_cycleProcess, &CycleProcess::stopCycleProcess);
    emit(onStartCycleSignal(50));
    /* 文字状态 */
    m_statusTitle = new QLabel(this);
    m_statusTitle->setText("Printing...");
    m_statusTitle->setStyleSheet("color:white");
    QFont title("Arial", 25);
    m_statusTitle->setFont(title);
    m_statusTitle->setGeometry(115, 0, 200, 100);
    m_statusTitle->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    m_statusContext = new QLabel(this);
    m_statusContext->setText("machine is printing base layer");
    m_statusContext->setStyleSheet("color:balck");
    QFont context("Arial", 10);
    m_statusContext->setFont(context);
    m_statusContext->setGeometry(115, 5, 200, 100);
    m_statusTitle->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    /* 进度条 */
    m_pritingBar = new QProgressBar(this);
    m_pritingBar->setGeometry(110, 70, 400, 20);
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
    m_testTimer.setInterval(100);
    connect(&m_testTimer, &QTimer::timeout, this, &StackWidgetPrinting::onTestTimer);
    m_testTimer.start();

    /* 取消按钮 */
    m_btnCancel = new QPushButton("Cancel", this);
    m_btnCancel->setGeometry(340, 10, 50, 30);
    connect(m_btnCancel, &QPushButton::clicked, this, &StackWidgetPrinting::onCancelBtnClicked);
    /* 暂停按钮 */
    m_btnPasuse = new QPushButton("Pause", this);
    m_btnPasuse->setGeometry(280, 10, 50, 30);
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
    m_pritingBar->setValue(m_progressValue%100);
    m_cycleProcess->setLabelText(QString("%1\%").arg(m_pritingBar->value()));
    update();
}
