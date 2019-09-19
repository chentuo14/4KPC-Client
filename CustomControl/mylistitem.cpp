#include "CustomControl/mylistitem.h"
#include <QDebug>

MyListItem::MyListItem(QWidget *parent) : QWidget(parent)
{
    InitDefaultParamters();

    InitMaterialInfomations();

    InitButtons();

    HideOperationButton();

    InitLayout();
}

MyListItem::MyListItem(MyListItem *item) : QWidget((QWidget *)item->parent())
{
    InitDefaultParamters();

    InitMaterialInfomations();

    InitButtons();

    HideOperationButton();

    InitLayout();

    this->SetMaterialName(item->GetMaterialName());
    this->SetMaterialDescription(item->GetMaterialDescription());
//    qDebug()<<"MyListItem"<<this->geometry();
}

void MyListItem::SetItemMaterialInfo(QString name, QString description)
{
    SetMaterialName(name);
    SetMaterialDescription(description);
}

//设置拖拽的信息
void MyListItem::SetMimData(const QMimeData *data)
{
    QString str = data->text();
    QStringList lists =str.split(";");
    /* data格式：材料名；描述；是否可编辑 */
    this->SetMaterialName(lists.first());
    this->SetMaterialDescription(lists[1]);
    this->SetItemEditable(lists[2]=="1"?true:false);
}

void MyListItem::GetMimData(QMimeData *data)
{
    QString materialName = this->GetMaterialName();
    QString materialDescription = this->GetMaterialDescription();
    QString editable = this->GetItemEditable()?"1":"0";
    data->setText(materialName+";"+materialDescription+";"+editable);
//    qDebug()<<"GetMinData:"<<data->text();
}

void MyListItem::SetMaterialName(QString name)
{
    m_materialName->setText(name);
}

QString MyListItem::GetMaterialName()
{
    return m_materialName->text();
}

void MyListItem::SetMaterialDescription(QString description)
{
    m_materialDescription->setText(description);
}

QString MyListItem::GetMaterialDescription()
{
    return m_materialDescription->text();
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

void MyListItem::SetMaterials(QString string)
{
    m_materials = string.split(";");
}

QStringList MyListItem::GetMaterials()
{
    return m_materials;
}

void MyListItem::SelectMaterialDisplay()
{
    //重新布局
    m_selectIcon->show();
    m_mainlayout->addWidget(m_selectIcon,1,1,1,1);
    m_mainlayout->addWidget(m_materialName,1,2,1,1);
    m_mainlayout->addWidget(m_materialDescription, 2,2,1,1);
    this->setLayout(m_mainlayout);
    QImage *img = new QImage(":/myMaterialList/selected.png");
    m_selectIcon->setPixmap(QPixmap::fromImage(img->scaled(m_selectIcon->size(), Qt::KeepAspectRatio)));
    SetItemSelectedFlag(true);
}

void MyListItem::UnselectMaterialDisplay()
{
    //恢复布局
    m_selectIcon->hide();
    m_mainlayout->addWidget(m_materialName,1,1,1,1);
    m_mainlayout->addWidget(m_materialDescription, 2,1,1,1);
    this->setLayout(m_mainlayout);
    SetItemSelectedFlag(false);
}

void MyListItem::SetItemEditText()
{
    HideOperationButton();
    m_materialNameEdit->setGeometry(m_materialName->geometry());
    m_materialNameEdit->setText(GetMaterialName());
    m_materialNameEdit->show();

    m_materialDescriptionEdit->setGeometry(m_materialDescription->geometry());
    m_materialDescriptionEdit->setText(GetMaterialDescription());
    m_materialDescriptionEdit->show();
    m_materialNameEdit->setFocus();
    m_materialNameEdit->selectAll();
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
    if(!m_materialNameEdit->isHidden()) {
        SetMaterialName(m_materialNameEdit->text());
        m_materialNameEdit->hide();
    }
    if(!m_materialDescriptionEdit->isHidden()) {
        SetMaterialDescription(m_materialDescriptionEdit->text());
        m_materialDescriptionEdit->hide();
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

void MyListItem::InitMaterialInfomations()
{
    /* 材料信息 */
    m_materialName = new QLabel(this);
    m_materialDescription = new QLabel(this);
    m_materialNameEdit = new QLineEdit(this);
    m_materialDescriptionEdit = new QLineEdit(this);
    SetMaterialName("name");
    SetMaterialDescription("null");
    m_materialNameEdit->hide();
    m_materialDescriptionEdit->hide();
    /* 选中图标 */
    m_selectIcon = new QLabel(this);
    QImage *backGround = new QImage(":/myMaterialList/selected.png");
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

    m_btnEdit->setStyleSheet("QPushButton{border:0px solid;image:url(:/myMaterialList/plus.png);}QPushButton::Hover{image:url(:/myMaterialList/plusHover.png);}");
    m_btnDel->setStyleSheet("QPushButton{border:0px solid;image:url(:/myMaterialList/close.png);}QPushButton::Hover{image:url(:/myMaterialList/closeHover.png);}");
    m_btnSelect->setStyleSheet("QPushButton{border:0px solid;image:url(:/myMaterialList/ok.png);}QPushButton::Hover{image:url(:/myMaterialList/okHover.png);}");
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
    m_mainlayout->addWidget(m_materialName, 1,1,1,1);
    m_mainlayout->addWidget(m_materialDescription,2,1,1,1);
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
