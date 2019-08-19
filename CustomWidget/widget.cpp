#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_mousePressed(false)
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
