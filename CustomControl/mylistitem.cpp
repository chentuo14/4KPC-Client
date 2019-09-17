#include "CustomControl/mylistitem.h"
#include <QDebug>

MyListItem::MyListItem(QWidget *parent) : QWidget(parent)
{
    InitDefaultParamters();

    InitMatrialInfomations();

    InitButtons();

    HideOperationButton();

    InitLayout();
}

MyListItem::MyListItem(MyListItem *item) : QWidget((QWidget *)item->parent())
{
    InitDefaultParamters();

    InitMatrialInfomations();

    InitButtons();

    HideOperationButton();

    InitLayout();

    this->SetMatrialName(item->GetMatrialName());
    this->SetMatrialDescription(item->GetMatrialDescription());
//    qDebug()<<"MyListItem"<<this->geometry();
}

void MyListItem::SetItemMatrialInfo(QString name, QString description)
{
    SetMatrialName(name);
    SetMatrialDescription(description);
}

//设置拖拽的信息
void MyListItem::SetMimData(const QMimeData *data)
{
    QString str = data->text();
    QStringList lists =str.split(";");
    /* data格式：材料名；描述；是否可编辑 */
    this->SetMatrialName(lists.first());
    this->SetMatrialDescription(lists[1]);
    this->SetItemEditable(lists[2]=="1"?true:false);
}

void MyListItem::GetMimData(QMimeData *data)
{
    QString matrialName = this->GetMatrialName();
    QString matrialDescription = this->GetMatrialDescription();
    QString editable = this->GetItemEditable()?"1":"0";
    data->setText(matrialName+";"+matrialDescription+";"+editable);
//    qDebug()<<"GetMinData:"<<data->text();
}

void MyListItem::SetMatrialName(QString name)
{
    m_matrialName->setText(name);
}

QString MyListItem::GetMatrialName()
{
    return m_matrialName->text();
}

void MyListItem::SetMatrialDescription(QString description)
{
    m_matrialDescription->setText(description);
}

QString MyListItem::GetMatrialDescription()
{
    return m_matrialDescription->text();
}

void MyListItem::SetItemSelectedFlag(bool flag)
{
    m_selectedFlag = flag;
}

bool MyListItem::GetItemSelectedFlag()
{
    return m_selectedFlag;
}

void MyListItem::SetItemEditable(bool flag)
{
    m_isEditable = flag;
}

bool MyListItem::GetItemEditable()
{
    return m_isEditable;
}

void MyListItem::SetMatrials(QString string)
{
    m_matrials = string.split(";");
}

QStringList MyListItem::GetMatrials()
{
    return m_matrials;
}

void MyListItem::SelectMatrialDisplay()
{
    //重新布局
    m_selectIcon->show();
    m_mainlayout->addWidget(m_selectIcon,1,1,1,1);
    m_mainlayout->addWidget(m_matrialName,1,2,1,1);
    m_mainlayout->addWidget(m_matrialDescription, 2,2,1,1);
    this->setLayout(m_mainlayout);
    QImage *img = new QImage(":/myMatrialList/selected.png");
    m_selectIcon->setPixmap(QPixmap::fromImage(img->scaled(m_selectIcon->size(), Qt::KeepAspectRatio)));
    SetItemSelectedFlag(true);
}

void MyListItem::UnselectMatrialDisplay()
{
    //恢复布局
    m_selectIcon->hide();
    m_mainlayout->addWidget(m_matrialName,1,1,1,1);
    m_mainlayout->addWidget(m_matrialDescription, 2,1,1,1);
    this->setLayout(m_mainlayout);
    SetItemSelectedFlag(false);
}

void MyListItem::SetItemEditText()
{
    HideOperationButton();
    m_matrialNameEdit->setGeometry(m_matrialName->geometry());
    m_matrialNameEdit->setText(GetMatrialName());
    m_matrialNameEdit->show();

    m_matrialDescriptionEdit->setGeometry(m_matrialDescription->geometry());
    m_matrialDescriptionEdit->setText(GetMatrialDescription());
    m_matrialDescriptionEdit->show();
    m_matrialNameEdit->setFocus();
    m_matrialNameEdit->selectAll();
}

void MyListItem::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if(m_mouseEnterFlag) {
        QPainter p(this);
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(240,240,240,240));
        p.drawRect(rect());
    }
}

//鼠标双击事件
void MyListItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
    if(this->GetItemEditable())
        SetItemEditText();
//    qDebug()<<"mouseDoubleClickEvent"<<this->geometry();
}

void MyListItem::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void MyListItem::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

//鼠标进入事件
void MyListItem::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    m_mouseEnterFlag = true;
    ShowOperationButton();
    repaint();
}

//鼠标离开事件
void MyListItem::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    HideOperationButton();
    if(!m_matrialNameEdit->isHidden()) {
        SetMatrialName(m_matrialNameEdit->text());
        m_matrialNameEdit->hide();
    }
    if(!m_matrialDescriptionEdit->isHidden()) {
        SetMatrialDescription(m_matrialDescriptionEdit->text());
        m_matrialDescriptionEdit->hide();
    }

    m_mouseEnterFlag = false;
    repaint();
}

void MyListItem::focusInEvent(QFocusEvent *event)
{
    QWidget::focusInEvent(event);
}

void MyListItem::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);
    repaint();
}

void MyListItem::InitDefaultParamters()
{
    m_mouseEnterFlag = false;               //鼠标进入标志位
    m_isEditable = true;                    //是否可编辑，默认的行
    m_selectedFlag = false;                 //是否被选中
}

void MyListItem::InitMatrialInfomations()
{
    /* 材料信息 */
    m_matrialName = new QLabel(this);
    m_matrialDescription = new QLabel(this);
    m_matrialNameEdit = new QLineEdit(this);
    m_matrialDescriptionEdit = new QLineEdit(this);
    SetMatrialName("name");
    SetMatrialDescription("null");
    m_matrialNameEdit->hide();
    m_matrialDescriptionEdit->hide();
    /* 选中图标 */
    m_selectIcon = new QLabel(this);
    QImage *backGround = new QImage(":/myMatrialList/selected.png");
    m_selectIcon->setFixedSize(50, 50);
    backGround->scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_selectIcon->setPixmap(QPixmap::fromImage(*backGround));
    m_selectIcon->hide();
}

void MyListItem::InitButtons()
{
    /* 操作按钮 */
    m_btnEdit = new QPushButton(this);
    m_btnDel = new QPushButton(this);
    m_btnSelect = new QPushButton(this);

    m_btnEdit->setStyleSheet("QPushButton{border:0px solid;image:url(:/myMatrialList/plus.png);}QPushButton::Hover{image:url(:/myMatrialList/plusHover.png);}");
    m_btnDel->setStyleSheet("QPushButton{border:0px solid;image:url(:/myMatrialList/close.png);}QPushButton::Hover{image:url(:/myMatrialList/closeHover.png);}");
    m_btnSelect->setStyleSheet("QPushButton{border:0px solid;image:url(:/myMatrialList/ok.png);}QPushButton::Hover{image:url(:/myMatrialList/okHover.png);}");
    connect(m_btnEdit, &QPushButton::clicked, this, &MyListItem::onBtnEditClicked);
    connect(m_btnDel, &QPushButton::clicked, this, &MyListItem::onBtnDelClicked);
    connect(m_btnSelect, &QPushButton::clicked, this, &MyListItem::onBtnSelectClicked);

    int size = 15;
    int xPos=180;
    int yPos=20;
    int separation = 5;
    m_btnDel->setGeometry(xPos+(size+separation),yPos,size,size);
    m_btnEdit->setGeometry(xPos+2*(size+separation),yPos,size,size);
    m_btnSelect->setGeometry(xPos+3*(size+separation),yPos,size,size);
}

void MyListItem::InitLayout()
{
    /* 布局 */
    m_mainlayout = new QGridLayout(this);
    m_mainlayout->addWidget(m_matrialName, 1,1,1,1);
    m_mainlayout->addWidget(m_matrialDescription,2,1,1,1);
    this->setGeometry(0,0,264,50);
    this->setLayout(m_mainlayout);
}

//隐藏左边按钮
void MyListItem::HideOperationButton()
{
    m_btnEdit->hide();
    m_btnSelect->hide();
    m_btnDel->hide();
}

//显示左边按钮
void MyListItem::ShowOperationButton()
{
    m_btnEdit->show();
    m_btnSelect->show();
    if(this->GetItemEditable())
        m_btnDel->show();
}

void MyListItem::onBtnUpClicked()
{
    qDebug()<<"onBtnUpClicked";
}

void MyListItem::onBtnDownClicked()
{
//    qDebug()<<"onBtnDownClicked";
}

void MyListItem::onBtnEditClicked()
{
//    qDebug()<<"onBtnEditClicked";
    emit(onBtnEditClickedSignal(this->pos()));
}

void MyListItem::onBtnDelClicked()
{
//    qDebug()<<"onBtnDelClicked";
    emit(onBtnDelClickedSignal(this->pos()));
}

void MyListItem::onBtnSelectClicked()
{
//    qDebug()<<"onBtnChooseClicked";
    emit(onBtnSelectClickedSignal(this->pos()));
}
