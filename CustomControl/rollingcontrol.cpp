#include "rollingcontrol.h"
#include <QDebug>

rollingControl::rollingControl(QWidget *parent) : QWidget(parent)
{
    m_numPos = 0;
    m_mouseStartPos = 0;
    m_mouseMoveDistance = 0;
    m_mouseReleasePos = 0;
    m_currentCenterPos = 0;
    m_mouseStartPos = this->width()/2;
    updateNumWidth(this->width()/3);

    initAmiationConfig();
    //    qDebug()<<"Start test.";
}

rollingControl::~rollingControl()
{

}

void rollingControl::initAmiationConfig()
{
    /* 配置动画效果 */
    m_animationFlag = false;
    m_movCenterAnimation = new QPropertyAnimation(this, "");
    m_movCenterAnimation->setDuration(300);
    m_movCenterAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(m_movCenterAnimation, &QPropertyAnimation::valueChanged, this, &rollingControl::onMoveCenterValueChange);
    connect(m_movCenterAnimation, &QPropertyAnimation::finished, this, [=](){
        m_animationFlag = false;
        m_currentCenterPos = m_numPos;
        qDebug()<<"m_currentCenterPos:"<<m_currentCenterPos;
    });
}

void rollingControl::drawMyTestNum(int x, int y, int num)
{
    /* 画单个数字 */
    QPainter painter(this);
    QFont font;
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(QColor(0,0,0,200));
    painter.drawText(QRectF(x, y, m_numWidth, 50),
                     Qt::AlignCenter,
                     QString::number(num));
}

void rollingControl::drawMyTestNum(int x, int y, int num, int size)
{
    QPainter painter(this);
    QFont font;
    font.setPixelSize(size);
    painter.setFont(font);
    painter.setPen(QColor(0,0,0,200));
    painter.drawText(QRectF(x, y, m_numWidth, 50),
                     Qt::AlignCenter,
                     QString::number(num));
}

int rollingControl::caculateMoveLength(int xPos, int width)
{
//    qDebug()<<"xPos:"<<xPos;
    int mod = 0;
    int move = 0;
    if(xPos<0) {         //负数
        mod = xPos%width*(-1);
        if(mod<width/2) {
            move = mod;
        } else {
            move = (-1)*(width-mod);
        }
    } else {            //正数
        mod = xPos%width;
        if(mod<width/2) {
            move = (-1)*mod;
        } else {
            move = width-mod;
        }
    }
    return move;
}

bool rollingControl::checkPosOverMax(int pos)
{
    if(pos>m_maxPos)
        return true;
    else
        return false;
}

bool rollingControl::checkPosUnderMin(int pos)
{
    if(pos<m_minPos)
        return true;
    else
        return false;
}

bool rollingControl::checkPosOutOfSize(int pos)
{
    if(pos>m_maxPos) {
        qDebug()<<"pos value too more";
        return true;
    }
    if(pos<m_minPos) {
        qDebug()<<"pos value too few";
        return true;
    }
    return false;
}

void rollingControl::updateNumWidth(int size)
{
    m_numWidth = size;
    m_maxPos = (m_numWidth*5);
    m_minPos = (-1)*(m_numWidth*4);
    qDebug()<<"m_mouseStartPos:"<<m_mouseStartPos<<",m_maxPos:"<<m_maxPos;
}

void rollingControl::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateNumWidth(this->width()/3);
}

void rollingControl::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    /* 画中间的线 */
    QPainter painter(this);
//    painter.drawLine(this->width()/2, 0, this->width()/2, this->height());
    qDebug()<<"width 3/8:"<<this->width()/8*3<<"width 5/8:"<<this->width()*5/8;
    QPointF pointsUp[3] = {
        QPointF(this->width()/9*4, 0),
        QPointF(this->width()/9*5, 0),
        QPointF(this->width()/2, this->height()/4)
    };
    QPointF pointsDown[3] = {
        QPointF(this->width()/9*4, this->height()-2),
        QPointF(this->width()/9*5, this->height()-2),
        QPointF(this->width()/2, this->height()/4*3)
    };
    QPainterPath triPath;
    QBrush brush(QColor(Qt::black));
    triPath.moveTo(pointsUp[0]);
    triPath.lineTo(pointsUp[1]);
    triPath.lineTo(pointsUp[2]);
    painter.fillPath(triPath, brush);
    triPath.moveTo(pointsDown[0]);
    triPath.lineTo(pointsDown[1]);
    triPath.lineTo(pointsDown[2]);
    painter.fillPath(triPath, brush);

    if(checkPosOverMax(m_numPos))
        m_numPos = m_maxPos;
    if(checkPosUnderMin(m_numPos))
        m_numPos = m_minPos;
    int pos = (-1)*(m_numPos+m_mouseMoveDistance);              //初始位置+鼠标移动距离
    int offset = (-1)*(m_numWidth*4);                           //左偏4个字宽

    /* 画数字 */
    for(int i=1;i<11;i++) {
        drawMyTestNum(offset+pos+i*m_numWidth, 0, i*10);
    }
}

void rollingControl::mousePressEvent(QMouseEvent *event)
{
    m_mouseStartPos = event->pos().x();
//    qDebug()<<"startPos:"<<m_mouseStartPos;
}

void rollingControl::mouseMoveEvent(QMouseEvent *event)
{
    m_mouseMoveDistance = m_mouseStartPos - event->pos().x();
    qDebug()<<"move distance:"<<m_mouseMoveDistance;
    repaint();
}

void rollingControl::mouseReleaseEvent(QMouseEvent *event)
{
    m_mouseReleasePos = event->pos().x();

    /* 判断边界 */
    if(checkPosOverMax(m_numPos))
        m_numPos = m_maxPos;
    if(checkPosUnderMin(m_numPos))
        m_numPos = m_minPos;
    m_numPos = m_numPos+m_mouseStartPos-m_mouseReleasePos;             //更新移动后的坐标

    /* 判断动画 */
    int move = caculateMoveLength(m_numPos, m_numWidth);
    m_mouseStartPos = 0;
    m_mouseReleasePos = 0;
    m_mouseMoveDistance = 0;
    qDebug()<<"m_numPos:"<<m_numPos<<",move:"<<move;
    if(!m_animationFlag) {
        m_movCenterAnimation->setStartValue(m_numPos);
        m_movCenterAnimation->setEndValue(m_numPos+move);
        m_movCenterAnimation->start();
        m_animationFlag = true;
    }
}

//滚轮事件
void rollingControl::wheelEvent(QWheelEvent *event)
{
    qDebug()<<"delta():"<<event->delta();

    if(event->delta()>0) {
        if(!m_animationFlag) {
            if(checkPosOverMax(m_numPos+m_numWidth))           //判断最大边界
                return;
            m_movCenterAnimation->setStartValue(m_numPos);
            m_movCenterAnimation->setEndValue(m_numPos+m_numWidth);
            m_movCenterAnimation->start();
            m_animationFlag = true;
        }
    } else {
        if(!m_animationFlag) {
            if(checkPosUnderMin(m_numPos-m_numWidth))          //判断最小边界
                return;
            m_movCenterAnimation->setStartValue(m_numPos);
            m_movCenterAnimation->setEndValue(m_numPos-m_numWidth);
            m_movCenterAnimation->start();
            m_animationFlag = true;
        }
    }
}

void rollingControl::onMoveCenterValueChange(QVariant value)
{
    qDebug()<<"value:"<<value.toInt();
    m_numPos = value.toInt();
    repaint();
}
