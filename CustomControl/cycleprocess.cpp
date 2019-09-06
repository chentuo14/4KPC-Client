#include "cycleprocess.h"

CycleProcess::CycleProcess(QWidget *parent) : QWidget(parent),
    m_angle(0),m_paintOffset(2)
{
    m_rotateTimer = new QTimer(this);
    connect(m_rotateTimer, &QTimer::timeout, this, &CycleProcess::onRotateTimer);
    m_centerLabel = new QLabel(this);
    m_centerLabel->setText("Hello");
    m_centerLabel->setAlignment(Qt::AlignCenter);
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_centerLabel);
    this->setLayout(mainLayout);
}

CycleProcess::~CycleProcess()
{

}

void CycleProcess::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/CustomControl/cycle.png");
    painter.translate(this->width()/2, this->height()/2);
    painter.rotate(m_angle);
    painter.translate(-1*this->width()/2, -1*this->height()/2);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

void CycleProcess::setLabelText(QString text)
{
    m_centerLabel->setText(text);
}

QLabel *CycleProcess::getCenterLabel()
{
    return m_centerLabel;
}

void CycleProcess::onRotateTimer()
{
    m_angle+=1;
    m_angle%=360;
    update();
}

void CycleProcess::startCycleProcess(int msec)
{
    m_rotateTimer->start(msec);
}

void CycleProcess::stopCycleProcess()
{
    if(m_rotateTimer->isActive())
        m_rotateTimer->stop();
}
