#include "CustomWidget/customtoolbutton.h"
#include <QDebug>

CustomToolButton::CustomToolButton(QWidget *parent) :
    QToolButton(parent),
    m_mouseClickedFlag(false),
    m_buttonStatus(STATUS_NORMAL),
    m_iconSize(50, 50)
{
    /* 鼠标悬停动画效果 */
    m_animationHover = new QPropertyAnimation(this, "");
    m_animationHover->setDuration(150);
    m_animationHover->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_animationHover, &QPropertyAnimation::valueChanged, this, &CustomToolButton::onHoverValueChanged);
    /* 选择后的图片动画效果 */
    m_animationIcon = new QPropertyAnimation(this, "");
    m_animationIcon->setDuration(150);
    m_animationIcon->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_animationIcon, &QPropertyAnimation::valueChanged, this, &CustomToolButton::onIconValueChanged);
}

void CustomToolButton::setButtonStatus(CustomToolButton::BUTTON_STATUS status)
{
    m_buttonStatus = status;
}

CustomToolButton::BUTTON_STATUS CustomToolButton::getButtonStatus()
{
    return m_buttonStatus;
}

void CustomToolButton::setMyIconSize(QSize size)
{
    m_iconSize = size;
    this->setIconSize(m_iconSize);
}

QSize CustomToolButton::getMyIconSize()
{
    return m_iconSize;
}

void CustomToolButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);
    QPainter buttonPainter(this);
    if(m_buttonStatus == STATUS_ENTER) {
        buttonPainter.setRenderHints(QPainter::Antialiasing);
        buttonPainter.setPen(Qt::NoPen);
        buttonPainter.setBrush(QColor(45,45,45,40));                       /* 鼠标悬浮颜色 */
        buttonPainter.drawRect(0, 0, m_animationHoverOffset, this->height());
        this->setAutoRaise(true);
    } else if(m_buttonStatus == STATUS_PRESSED) {
        buttonPainter.setRenderHints(QPainter::Antialiasing);
        buttonPainter.setPen(Qt::NoPen);
        buttonPainter.setBrush(QColor(25,25,25,50));                      /* 鼠标选中颜色 */
        buttonPainter.drawRect(0, 0, this->width(), this->height());
        this->setAutoRaise(true);
    }
}

//enterEvent 鼠标进入后启动动画
void CustomToolButton::enterEvent(QEvent *evnet)
{
    if(getButtonStatus() == STATUS_PRESSED) {
        return;
    }
    setButtonStatus(STATUS_ENTER);
    int startX = this->pos().x();
    int endX = this->pos().x()+ this->width();
    m_animationHover->setStartValue(startX);
    m_animationHover->setEndValue(endX);
    m_animationHover->start();
}

void CustomToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(getButtonStatus() == STATUS_PRESSED)
        return;
    setButtonStatus(STATUS_NORMAL);
}

void CustomToolButton::onHoverValueChanged(QVariant val)
{
    m_animationHoverOffset = val.toInt();
    update();
}

//onIconValueChanged 图标动画
void CustomToolButton::onIconValueChanged(QVariant val)
{
//    qDebug()<<"val:"<<val;
    QSize size = val.toSize();
    this->setIconSize(size);
    update();
}

void CustomToolButton::onBtnClickedDislapy()
{
    setButtonStatus(STATUS_PRESSED);
//    m_animationIcon->setStartValue(QSize(0, 53/2));
//    m_animationIcon->setEndValue(QSize(this->width()/4, 53));
//    m_animationIcon->start();
    update();
}

void CustomToolButton::onBtnClickedCancelDisplay()
{
    setButtonStatus(STATUS_NORMAL);
//    m_animationIcon->setStartValue(QSize(this->width()/4, 53/2));
//    m_animationIcon->setEndValue(QSize(this->width()/4, 53));
//    m_animationIcon->start();
    update();
}
