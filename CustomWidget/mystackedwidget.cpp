#include "mystackedwidget.h"
#include <QDebug>

MyStackedWidget::MyStackedWidget(QWidget *parent) :
    QStackedWidget(parent),
    m_slideFlag(false)
{
    /* 暂时取消动画
    m_slideWidgetAnimation = new QPropertyAnimation(this, "");
    m_slideWidgetAnimation->setDuration(100);
    connect(m_slideWidgetAnimation, SIGNAL(valueChanged(QVariant)), this,
            SLOT(onPrintingSlideValueChanged(QVariant)));
    connect(m_slideWidgetAnimation, &QPropertyAnimation::finished, this,
            &MyStackedWidget::onFinishSlideAnimation);
            */

}

void MyStackedWidget::paintEvent(QPaintEvent *event)
{
    QStackedWidget::paintEvent(event);
//    if(m_slideFlag) {
//        qDebug()<<"paintEvent";
//        paintPrintingWidget(0, m_printingIndex);
//    }
    if(m_slideFlag) {
        this->widget(0)->hide();
    }
}

void MyStackedWidget::paintPrintingWidget(int oldIndex, int newIndex)
{
    QPainter paint(this);
    QWidget *prevWidget = this->widget(oldIndex);
    QWidget *nextWidget = this->widget(newIndex);
    prevWidget->hide();
    QPixmap prevPixmap(prevWidget->size());
    prevPixmap.fill(QColor(0,0,0,0));
    QPixmap nextPixmap(nextWidget->size());
//    nextPixmap.fill(QColor(255,255,255,255));
    prevWidget->render(&prevPixmap);
    /* 先画widgetone */
    paint.drawPixmap(0, 0, prevWidget->width(), prevWidget->height(),
                     prevPixmap,
                     0, 0, prevWidget->width(), prevWidget->height());
    /* 再画printingWidget */
    nextWidget->render(&nextPixmap);
    QRectF target(0, m_changedValue.toInt(),
                  nextWidget->width(), nextWidget->height()-m_changedValue.toInt());
    QRectF source(0, 0, nextWidget->width(), nextWidget->height()-m_changedValue.toInt());
    paint.drawPixmap(target, nextPixmap, source);
}

void MyStackedWidget::onFinishSlideAnimation()
{
    qDebug()<<"finished";
    QPixmap pixmap(this->size());
    this->render(&pixmap);
    this->widget(m_printingIndex)->show();
    m_slideFlag = false;
}

void MyStackedWidget::onPrintingSlideValueChanged(QVariant value)
{
    qDebug()<<"m_changedValue:"<<m_changedValue;
    m_changedValue = value;
    update();
}

void MyStackedWidget::onEnterPrintingWidget(int startValue)
{
    m_slideWidgetAnimation->setStartValue(startValue);
    m_slideWidgetAnimation->setEndValue(0);
    m_slideWidgetAnimation->start();
    m_slideFlag = true;
    qDebug()<<"onEnterPrintingWidget";
}

void MyStackedWidget::onExitPrintingWidget(int startValue)
{
    m_slideWidgetAnimation->setStartValue(startValue);
    m_slideWidgetAnimation->setEndValue(0);
    m_slideWidgetAnimation->start();
}

void MyStackedWidget::onWidgetChanged(int index)
{
    qDebug()<<"onWidgetChanged";
    if(index == this->currentIndex())
        return;

    if(!this->widget(m_printingIndex)->isHidden())
        this->widget(m_printingIndex)->hide();

    this->setCurrentIndex(index);
}

void MyStackedWidget::onPrintStartDisplay()
{
    this->widget(m_printingIndex)->show();
    this->widget(m_printReadyIndex)->hide();
}

void MyStackedWidget::onPrintCancelDisplay()
{
    this->widget(m_printingIndex)->hide();
    this->widget(m_printReadyIndex)->show();
}
