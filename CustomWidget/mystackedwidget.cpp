#include "mystackedwidget.h"

MyStackedWidget::MyStackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{

}

void MyStackedWidget::paintEvent(QPaintEvent *event)
{
    QStackedWidget::paintEvent(event);
}

void MyStackedWidget::onDisplayPrintingWidget()
{

}
