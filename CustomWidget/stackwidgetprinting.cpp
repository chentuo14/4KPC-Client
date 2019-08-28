#include "stackwidgetprinting.h"
#include "ui_stackwidgetprinting.h"
#include <QDebug>

StackWidgetPrinting::StackWidgetPrinting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetPrinting)
{
    ui->setupUi(this);
    m_btnCancel = new QPushButton("Cancel", this);
    m_btnCancel->setGeometry(200, 200, 80, 50);
    connect(m_btnCancel, &QPushButton::clicked, this, &StackWidgetPrinting::onCancelBtnClicked);
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
