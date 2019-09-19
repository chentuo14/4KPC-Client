#include "CustomControl/mynumroll.h"
#include <QDebug>

MyNumRoll::MyNumRoll(QWidget *parent) : QWidget(parent)
{
    SetDefaultParamers();
}

void MyNumRoll::SetDefaultParamers()
{
    m_minRange = 0;                     //最小值
    m_maxRange = 9;                     //最大值
    m_currentValue = 5;                 //当前选中的值
    m_isDragging = false;               //鼠标是否按下
    m_deviation = 1;                    //偏移量，记录鼠标按下后移动的垂直距离
    m_mouseSrcPos = 0;
    m_numSize = 5;
    m_interval = 1;                     //间隔大小
    m_separateNum = 3;                  //分隔数量
    m_isVertial = true;
    m_moveCenterAni = new QPropertyAnimation(this, "m_deviation");
    m_moveCenterAni->setDuration(300);
    m_moveCenterAni->setEasingCurve(QEasingCurve::InOutQuad);
    m_numColor = QColor(255, 2, 2, 255);
    setHasUnderLine(false);
    if(m_isVertial) {
        m_width = this->width();
        m_height = this->height();
    } else {
        m_width = this->height();
        m_height = this->width();
    }
}

void MyNumRoll::mousePressEvent(QMouseEvent *event)
{
    m_isDragging = true;

    int pos;
    if(m_isVertial)
        pos = event->pos().y();
    else
        pos = event->pos().x();

    m_mouseSrcPos = pos;
    QWidget::mousePressEvent(event);
}

void MyNumRoll::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isDragging) {
        int pos;
        if(m_isVertial) {
            pos = event->pos().y();
        } else {
            pos = event->pos().x();
        }

        //判断越界
        if((getCurrentValue()-getInterval() < getMinRange() && pos >= m_mouseSrcPos) ||
                (getCurrentValue()+getInterval() > getMaxRange() && pos <= m_mouseSrcPos))
            return;

        m_deviation = pos - m_mouseSrcPos;
        if(getDeviation() > (getMHeight()/m_separateNum))
            m_deviation = getMHeight()/m_separateNum;
        else if(getDeviation() < -getMHeight()/m_separateNum)
            m_deviation = -getMHeight()/m_separateNum;

        repaint();
    }
}

void MyNumRoll::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_isDragging) {
        m_moveCenterAni->stop();
        m_isDragging = false;
        numMoveCenter();
    }
}

void MyNumRoll::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        if(m_currentValue-m_interval < m_minRange)
            return;
        m_deviation = getMHeight() / m_separateNum;
    } else {
        if(m_currentValue+m_interval > m_maxRange)
            return;
        m_deviation = -getMHeight() / m_separateNum;
    }
    repaint();
    numMoveCenter();
}

void MyNumRoll::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if(getDeviation() >= getMHeight()/m_separateNum && m_currentValue >= m_minRange) {
        m_deviation -= getMHeight()/m_separateNum;
        m_currentValue -= m_interval;
        m_mouseSrcPos += getMHeight()/m_separateNum;
    }

    if(getDeviation() <= -getMHeight()/m_separateNum && m_currentValue <= m_maxRange) {
        m_deviation += getMHeight()/m_separateNum;
        m_currentValue += m_interval;
        m_mouseSrcPos -= getMHeight()/m_separateNum;
    }

    for(int i=0;i<=m_separateNum/2;i++) {
        if(m_currentValue-m_interval*i>=m_minRange)
            paintNum(painter, m_currentValue-m_interval*i, getDeviation() - getMHeight()/m_separateNum*i);
        if(m_currentValue+m_interval*i<=m_maxRange)
            paintNum(painter, m_currentValue+m_interval*i, getDeviation() + getMHeight()/m_separateNum*i);
    }

    if(getHasUnderLine()) {
        painter.fillRect(QRect(this->width()/2-this->width()/32,
                               this->height()/8*5,
                               this->width()/16, 2),Qt::black);
    }
}

void MyNumRoll::resizeEvent(QResizeEvent *event)
{
    if(m_isVertial) {
        m_width = this->width();
        m_height = this->height();
    } else {
        m_width = this->height();
        m_height = this->width();
    }
}

//num 需要显示的数字  deviation 数字相对中间的偏移量
void MyNumRoll::paintNum(QPainter &painter, double num, int shifting)
{
    int size = (getMHeight() - qAbs(shifting))/m_numSize;
    QFont font;
    font.setPixelSize(size);
    painter.setFont(font);
    painter.setPen(m_numColor);

    int pos = getMHeight()/2 + shifting - (getMHeight()/m_separateNum)/2;
    if(m_isVertial) {
        painter.drawText(QRectF(0, pos, getMWidth(), getMHeight()/m_separateNum),
                         Qt::AlignCenter,
                         QString::number(num));
    } else {
        painter.drawText(QRectF(pos, 0, getMHeight()/m_separateNum, getMWidth()),
                         Qt::AlignCenter,
                         QString::number(num));
    }
    painter.drawRect(QRect(0,0,this->width(),this->height()));
}

void MyNumRoll::numMoveCenter()
{
//    qDebug()<<"m_deviation:"<<m_deviation<<"height()/m_separateNum:"<<height()/m_separateNum;

    if(getDeviation() > getMHeight()/m_separateNum /2) {
        m_currentValue -= m_interval;
        m_moveCenterAni->setStartValue(getDeviation());
        m_moveCenterAni->setEndValue(0);
    } else if(getDeviation() < -getMHeight()/m_separateNum/2) {
        m_currentValue += m_interval;
        m_moveCenterAni->setStartValue(getDeviation());
        m_moveCenterAni->setEndValue(0);
    } else {
        m_moveCenterAni->setStartValue(getDeviation());
        m_moveCenterAni->setEndValue(0);
    }
    m_moveCenterAni->start();
}


