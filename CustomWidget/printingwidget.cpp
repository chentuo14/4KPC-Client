#include "printingwidget.h"
#include "ui_printingwidget.h"

PrintingWidget::PrintingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintingWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

PrintingWidget::~PrintingWidget()
{
    delete ui;
}
