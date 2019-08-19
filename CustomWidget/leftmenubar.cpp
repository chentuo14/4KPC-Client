#include "CustomWidget/leftmenubar.h"
#include "ui_leftmenubar.h"
#include <QDebug>
LeftMenuBar::LeftMenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftMenuBar),
    m_bottomSpace(2),
    m_buttonCurrIndex(0),
    m_buttonPrevIndex(0)
{
    ui->setupUi(this);
    InitControl();
}

LeftMenuBar::~LeftMenuBar()
{
    delete ui;
}

void LeftMenuBar::DeleteLayout()
{
    //清除布局，包括布局内控件
    if (this->layout() != nullptr)
    {
        QLayoutItem *child;
        while ((child = this->layout()->takeAt(0)) != 0) {
            delete child->widget();
            delete child;
            child = nullptr;
        }
        m_btnVec.clear();
        delete this->layout();
        this->setLayout(nullptr);
    }
}

void LeftMenuBar::InitControl()
{
    /* 创建需要的控件 */
    m_btnGroup = new QButtonGroup(this);
    connect(m_btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(OnBtnClicked(int)));
    m_animation = new QPropertyAnimation(this, "");
    m_animation->setDuration(200);
    /* 初始化logo */
    QPixmap *img = new QPixmap(":/icon/SoonSolid_icon.png");
    img->scaled(QSize(50,50), Qt::KeepAspectRatio);
    ui->labelLogo->setScaledContents(true);
    ui->labelLogo->setPixmap(*img);
    ui->labelName->setText("Soon Solid");
    ui->labelVersion->setText("Version:0.1");
    ui->labelLogo->setAlignment(Qt::AlignCenter);
    ui->labelLogo->setMaximumSize(50, 50);
    ui->labelName->setMaximumSize(120,50);
    ui->labelVersion->setMaximumSize(100,50);
    /* 创建布局 */
    DeleteLayout();
    m_menuLayout = new QVBoxLayout(this);
    m_menuLayout->setContentsMargins(0, 0, 0, m_bottomSpace);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout()->setSpacing(1);
    /* 创建logo布局 */
    m_logoLayout = new QGridLayout(this);
    m_logoLayout->addWidget(ui->labelLogo,    1, 1, 2, 1);
    m_logoLayout->addWidget(ui->labelName,    1, 2, 1, 1);
    m_logoLayout->addWidget(ui->labelVersion, 2, 2, 1, 1);
    m_logoLayout->setAlignment(ui->labelLogo, Qt::AlignCenter);
    m_menuLayout->addLayout(m_logoLayout);
    setLayout(m_menuLayout);
}

void LeftMenuBar::initBtns(int num)
{
    m_btnVec.resize(num);
    for(int i=0;i<num;i++) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setText(QString("Button%1").arg(i));
        btn->setMinimumSize(QSize(this->width(), 50));      //Note:must after setGeometry
        btn->setAutoRaise(true);
        btn->setCheckable(true);
        btn->setStyleSheet(QString("border:none;background-color:transparent"));
        m_btnVec[i] = btn;
        addBtn(btn, i);
    }
    m_menuLayout->addStretch(0);
}

void LeftMenuBar::addBtn(CustomToolButton *btn, int id)
{
    m_btnGroup->addButton(btn, id);
    m_menuLayout->addWidget(btn);
}

void LeftMenuBar::paintEvent(QPaintEvent *event)
{
    QPainter winPainter(this);
    winPainter.setRenderHints(QPainter::Antialiasing);
    winPainter.setPen(Qt::NoPen);
    winPainter.setBrush(QColor(220,220,220,50));
    winPainter.drawRect(0, 0, this->width(), this->height());
}

void LeftMenuBar::OnBtnClicked(int index)
{
    m_buttonPrevIndex = m_buttonCurrIndex;
    m_buttonCurrIndex = index;
    m_btnVec[m_buttonPrevIndex]->onBtnClickedCancelDisplay();
    m_btnVec[m_buttonCurrIndex]->setChecked(true);
    m_btnVec[m_buttonCurrIndex]->onBtnClickedDislapy();
}
