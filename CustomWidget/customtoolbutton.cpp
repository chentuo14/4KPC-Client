#include "customtoolbutton.h"
#include <QDebug>

CustomToolButton::CustomToolButton(QWidget *parent) :
    QToolButton(parent),
    m_mouseClickedFlag(false),
    m_buttonStatus(STATUS_NORMAL)
{
    m_animation = new QPropertyAnimation(this, "");
    m_animation->setDuration(50);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_animation, &QPropertyAnimation::valueChanged, this, &CustomToolButton::onValueChanged);
}

void CustomToolButton::setButtonStatus(CustomToolButton::BUTTON_STATUS status)
{
    m_buttonStatus = status;
}

CustomToolButton::BUTTON_STATUS CustomToolButton::getButtonStatus()
{
    return m_buttonStatus;
}

void CustomToolButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);
    QPainter buttonPainter(this);
    if(m_buttonStatus == STATUS_ENTER) {
        buttonPainter.setRenderHints(QPainter::Antialiasing);
        buttonPainter.setPen(Qt::NoPen);
        buttonPainter.setBrush(QColor(0,0,0,80));
        buttonPainter.drawRect(0, 0, m_animationOffset, this->height());
        this->setAutoRaise(true);
    } else if(m_buttonStatus == STATUS_PRESSED) {
        buttonPainter.setRenderHints(QPainter::Antialiasing);
        buttonPainter.setPen(Qt::NoPen);
        buttonPainter.setBrush(QColor(0,0,0,120));
        buttonPainter.drawRect(0, 0, this->width(), this->height());
        this->setAutoRaise(true);
    }
}

void CustomToolButton::enterEvent(QEvent *evnet)
{
    if(getButtonStatus() == STATUS_PRESSED) {
        return;
    }
    setButtonStatus(STATUS_ENTER);
    int startX = this->pos().x();
    int endX = this->pos().x()+ this->width();
    m_animation->setStartValue(startX);
    m_animation->setEndValue(endX);
    m_animation->start();
}

void CustomToolButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if(getButtonStatus() == STATUS_PRESSED)
        return;
    setButtonStatus(STATUS_NORMAL);
}

void CustomToolButton::onValueChanged(QVariant val)
{
    m_animationOffset = val.toInt();
    update();
}

void CustomToolButton::onBtnClickedDislapy()
{
    setButtonStatus(STATUS_PRESSED);
    update();
}

void CustomToolButton::onBtnClickedCancelDisplay()
{
    setButtonStatus(STATUS_NORMAL);
    update();
}
