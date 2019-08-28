#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_mousePressed(false),
    m_leftMenuNum(6),
    m_leftMenuWidth(140)
{
    ui->setupUi(this);
    InitMyWidget();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_mousePressed = true;
        m_mouseMovePoint = event->pos();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed) {
        QPoint movePos = event->globalPos();
        this->move(movePos - m_mouseMovePoint);
    }
}

void Widget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    QPixmap pixmap(":/background/timg.jpg");

    painter.drawPixmap(this->rect(), pixmap, QRect());
}

void Widget::onCloseButtonSlot()
{
    this->close();
}

void Widget::onMinButtonSlot()
{
    this->showMinimized();
}

void Widget::InitMyWidget()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setMouseTracking(true);
    this->setGeometry(0, 0, 880, 543);

    InitLeftButton();
    /* 初始化stackWdiget */
    m_stackWidget = new MyStackedWidget(this);
    m_stackWidget->setGeometry(m_leftMenuWidth, 0, this->width()-m_leftMenuWidth, this->height());
    m_widgteOne = new StackWidgetOne(this);         //第一个界面做打印
    m_widgteOne->setGeometry(0, 0, m_stackWidget->width(), m_stackWidget->height());
    m_stackWidget->addWidget(m_widgteOne);


    for(int i=1;i<m_leftMenuNum;i++) {
        m_stackWidget->addWidget(new QLabel(QString("windowTest%1").arg(i)));
    }
    m_printingWidget = new StackWidgetPrinting(this);
    m_printingWidget->setGeometry(0, 0, this->width(), this->height());
    m_stackWidget->addWidget(m_printingWidget);     //index 6

//    connect(m_widgteOne, &StackWidgetOne::btnPrintClicked, m_stackWidget, &MyStackedWidget::onEnterPrintingWidget);
    connect(m_widgteOne, &StackWidgetOne::btnPrintClicked, m_stackWidget, &MyStackedWidget::onPrintStartDisplay);
    connect(m_leftMenu->getLeftMenuButtonGroup(),SIGNAL(buttonClicked(int)), m_stackWidget,SLOT(onWidgetChanged(int)));
    connect(m_printingWidget, &StackWidgetPrinting::onCancelSignal, m_stackWidget, &MyStackedWidget::onPrintCancelDisplay);
    m_stackWidget->setCurrentIndex(0);

    InitRightTopButton();

}

void Widget::InitRightTopButton()
{
    int width = this->width();//获取界面的宽度
    //构建最小化、最大化、关闭按钮
    m_minButton = new QToolButton(this);
    m_closeButton = new QToolButton(this);
    m_skinButton = new QToolButton(this);
    m_settingButton = new QToolButton(this);

    //获取最小化、关闭按钮图标
    QPixmap minPix(":/icon/mini.png");
    QPixmap closePix(":/icon/close.png");
    QPixmap skinPix(":/icon/skin.png");
    QPixmap settingPix(":/icon/setting.png");

    //设置最小化、关闭按钮图标
    m_closeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_minButton->setIcon(minPix);
    m_closeButton->setIcon(closePix);
    m_skinButton->setIcon(skinPix);
    m_settingButton->setIcon(settingPix);

    //设置最小化、关闭按钮在界面的位置
    m_skinButton->setGeometry(width-88, 5, 20, 20);
    m_settingButton->setGeometry(width-67, 5, 20, 20);
    m_minButton->setGeometry(width-46,5,20,20);
    m_closeButton->setGeometry(width-25,5,20,20);

    //设置鼠标移至按钮上的提示信息
    m_minButton->setToolTip(tr("Minimized"));
    m_closeButton->setToolTip(tr("Close"));

    //设置最小化、关闭按钮的样式
    m_skinButton->setAutoRaise(true);
    m_settingButton->setAutoRaise(true);
    m_minButton->setAutoRaise(true);
    m_closeButton->setAutoRaise(true);

    m_skinButton->setStyleSheet("QToolButton:hover{background:darkgrey;}");
    m_settingButton->setStyleSheet("QToolButton:hover{background:darkgrey;}");
    m_minButton->setStyleSheet("QToolButton:hover{background:darkgrey;}");
    m_closeButton->setStyleSheet("QToolButton:hover{background:darkRed;}");

    connect(m_closeButton, &QToolButton::clicked, this, &Widget::onCloseButtonSlot);
    connect(m_minButton, &QToolButton::clicked, this, &Widget::onMinButtonSlot);
}

void Widget::InitLeftButton()
{
    /* 初始化左侧界面 */
    m_leftMenu = new LeftMenuBar(this);
    m_leftMenu->setGeometry(0, 0, m_leftMenuWidth, this->height());
    m_leftMenu->initBtns(m_leftMenuNum);
    QVector<CustomToolButton *> *vec = m_leftMenu->getCustomToolButtonVec();
    /* 初始化按钮图标 */
    m_leftMenu->setBtnIcon(0, ":/background/monitor_empty.png", ":/background/monitor_fill.png");
    m_leftMenu->setBtnIcon(1, ":/icon/print_unchecked.png", ":/icon/print_checked.png");
    m_leftMenu->setBtnIcon(2, ":/icon/print_unchecked.png", ":/icon/print_checked.png");
    m_leftMenu->setBtnIcon(3, ":/icon/print_unchecked.png", ":/icon/print_checked.png");
    m_leftMenu->setBtnIcon(4, ":/icon/print_unchecked.png", ":/icon/print_checked.png");
    m_leftMenu->setBtnIcon(5, ":/icon/laptop_black.png", ":/icon/laptop_color.png");
    /* 初始化图标的大小 */
    int size = qMin(vec->at(0)->width()/4, vec->at(0)->height());
    for(int i=0;i<6;i++) {
        vec->at(i)->setMyIconSize(QSize(size, size));
    }

    //默认选中按钮0
    m_leftMenu->OnBtnClicked(0);
}

void Widget::InitWidgetOne()
{
    m_widOneTitle = new QLabel(m_stackWidget->widget(0));
    m_widOneTitle->setGeometry(0,0, 100, 100);
    m_widOneTitle->setText("Hello,Ready for printing.");

}
