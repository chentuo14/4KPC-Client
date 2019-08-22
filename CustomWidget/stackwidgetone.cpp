#include "stackwidgetone.h"
#include "ui_stackwidgetone.h"

StackWidgetOne::StackWidgetOne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackWidgetOne)
{
    ui->setupUi(this);
    /* 标签设置 */
    m_labelTitle = new QLabel(this);
    m_labelTitle->setText("Hello,Ready for printing.");
    m_labelTitle->setStyleSheet("color:white");
    QFont font;
    font.setPointSize(25);
    m_labelTitle->setFont(font);
    m_labelTitle->setGeometry(100, 50, 400, 200);
    /* 设置按钮 */
    m_btnPrint = new QPushButton(this);
    m_btnPrint->setText("Print");
    m_btnPrint->setGeometry(100, 250, 150, 50);
    m_btnPrint->setStyleSheet("border:none;background-color:green;color:white");
}

StackWidgetOne::~StackWidgetOne()
{
    delete ui;
}
