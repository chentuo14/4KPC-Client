#include "CustomControl/mylistwidget.h"
#include <QDebug>

MyListWidget::MyListWidget(QWidget *parent):QListWidget(parent),
  m_mousePressFlag(false)
{
    /* 增加item */
    MyListItem *list = new MyListItem(this);
    list->SetMatrialName("name");
    MyListItem *list1 = new MyListItem(this);
    list1->SetMatrialName("name1");
    MyListItem *list2 = new MyListItem(this);
    list2->SetMatrialName("name2");
    MyListItem *list3 = new MyListItem(this);
    list3->SetMatrialName("name3");

    this->InsertCustomItem(list);
    this->InsertCustomItem(list1);
    this->InsertCustomItem(list2);
    this->InsertCustomItem(list3);

    this->setGeometry(0,0,250,400);
    this->setItemDelegate(new NoFocusDelegate());
    this->setMovement(QListView::Free);
    this->setStyleSheet("selection-color:rgb(255,255,255);/* 设置选中的字体颜色*/ "
                        "selection-background-color:rgba(200,200,200,150);"
                        "background:rgba(255,255,255,100);");

//    this->LoadDefaultMatrialList("./matrialList.txt");
}

MyListWidget::~MyListWidget()
{

}

//从文件中加载item数据
void MyListWidget::LoadDefaultMatrialList(QString filePath)
{
    QFile matrialFile(filePath);
    if(!matrialFile.open(QFile::ReadWrite)) {
        qDebug()<<"open fialed";
        return;
    }
    while(!matrialFile.atEnd()) {
        char cell[1024];
        int readNum = matrialFile.readLine(cell, 50);
//        qDebug()<<"readNum:"<<readNum<<cell;
        QString string(cell);
        MyListItem *item = new MyListItem(this);
        item->SetMatrials(string);
        item->SetMatrialName(item->GetMatrials().at(0));
        item->SetMatrialDescription(item->GetMatrials().at(1));
        item->SetItemEditable(false);
        this->InsertCustomItem(this->count(), item);
    }
}

void MyListWidget::LoadCustomMatrialList(QString filePath)
{

}

void MyListWidget::InsertCustomItem(MyListItem *customItem)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    this->addItem(item);
    item->setSizeHint(QSize(0, 50));
    this->setItemWidget(item, customItem);
    ConnectCustomSignalAndSlot(customItem);
}

void MyListWidget::InsertCustomItem(int rowIndex, MyListItem *customItem)
{
    QListWidgetItem *item = new QListWidgetItem();
    this->insertItem(rowIndex, item);
    item->setSizeHint(QSize(0, 50));
    this->setItemWidget(item, customItem);
    ConnectCustomSignalAndSlot(customItem);
}

void MyListWidget::ConnectCustomSignalAndSlot(MyListItem *customItem)
{
    connect(customItem, &MyListItem::onBtnDelClickedSignal, this, &MyListWidget::OnDelItemClicked);
    connect(customItem, &MyListItem::onBtnEditClickedSignal, this, &MyListWidget::OnEditItemClicked);
    connect(customItem, &MyListItem::onBtnSelectClickedSignal, this, &MyListWidget::OnSelectedClicked);
}

void MyListWidget::DisconnectCustomSignalAndSlot(MyListItem *customItem)
{
    disconnect(customItem, &MyListItem::onBtnDelClickedSignal, this, &MyListWidget::OnDelItemClicked);
    disconnect(customItem, &MyListItem::onBtnEditClickedSignal, this, &MyListWidget::OnEditItemClicked);
    disconnect(customItem, &MyListItem::onBtnSelectClickedSignal, this, &MyListWidget::OnSelectedClicked);
}

QPixmap MyListWidget::ChangeQImageBackTransparency(QImage image)
{
    QPixmap pix = QPixmap::fromImage(image);
    QPixmap tmpPix(pix.size());
    tmpPix.fill(Qt::transparent);
    QPainter p1(&tmpPix);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, pix);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p1.fillRect(tmpPix.rect(), QColor(0, 0, 0, 200));
    p1.end();
    return tmpPix;
}

//清除指针
void MyListWidget::ClearDragPointer()
{
    m_startItem = nullptr;
    m_dragItem = nullptr;
    m_isDragFlag = false;
}

//删除按钮槽函数
void MyListWidget::OnDelItemClicked(QPoint pos)
{
    QListWidgetItem *item = this->itemAt(pos);
    MyListItem *myItem = (MyListItem *)itemWidget(item);
    DisconnectCustomSignalAndSlot(myItem);
    if(myItem)
        myItem->deleteLater();
    this->takeItem(row(item));
    ClearDragPointer();
}

//新增按钮槽函数
void MyListWidget::OnEditItemClicked(QPoint pos)
{
//    qDebug()<<"OnEditItemClicked, pos:"<<pos;
    QListWidgetItem *btnItem = itemAt(pos);
    int btnRow = row(btnItem);
    MyListItem *addItem = new MyListItem(this);
    addItem->SetMatrialName("custom");
    InsertCustomItem(btnRow, addItem);
    qDebug()<<"OnEditItemClicked:additem"<<addItem->geometry();
    addItem->SetItemEditText();
}

//选择材料的槽函数
void MyListWidget::OnSelectedClicked(QPoint pos)
{
//    qDebug()<<"OnSelectedClicked";
    for(int i=0;i<this->count();i++) {
        MyListItem *item = ((MyListItem *)this->itemWidget(this->item(i)));
        if(item && item->GetItemSelectedFlag()) {
//            qDebug()<<"UnselectMatrialDisplay";
            item->UnselectMatrialDisplay();
            break;
        }
    }
    MyListItem *selectItem = ((MyListItem *)this->itemWidget(this->itemAt(pos)));
    selectItem->SelectMatrialDisplay();
}

//显示或隐藏，true隐藏，false显示
void MyListWidget::OnHideDefaultMatrial(bool flag)
{
    for(int i=0;i<this->count();i++) {
        MyListItem *myItem = (MyListItem *)itemWidget(this->item(i));
        bool editable = myItem->GetItemEditable();
        if(!editable) {
            this->setItemHidden(this->item(i), flag);
        }
    }
}

//显示或隐藏，true隐藏，false显示
void MyListWidget::OnHideCustomMatrial(bool flag)
{
    for(int i=0;i<this->count();i++) {
        MyListItem *myItem = (MyListItem *)itemWidget(this->item(i));
        bool editable = myItem->GetItemEditable();
        if(editable) {
            this->setItemHidden(this->item(i), flag);
        }
    }
}

//左键按下
void MyListWidget::mousePressEvent(QMouseEvent *event)
{
//    qDebug()<<"mousePressEvent";
//    QListWidgetItem *currentItem = this->itemAt(event->pos());;
//    if(!currentItem) {              //如果移动到了item外
//        ClearDragPointer();
//        return;
//    }

    m_ignoreMoveFlag = IsDragOutRage(event->pos());
    if(m_ignoreMoveFlag) {
        ClearDragPointer();
        return;
    }

    if(event->button() == Qt::LeftButton) {
        m_startPos = event->pos();              //记录起始位置坐标
        m_startItem = itemAt(event->pos());
        m_dragItem = (MyListItem *)itemWidget(m_startItem);        //记录坐标对应的widget
        m_isDragFlag = true;
        m_mousePressFlag = true;                //开始了按下拖动
    } else {
        m_mousePressFlag = false;
    }
    QListWidget::mousePressEvent(event);
}

//左键按下后移动，启动qdrag
void MyListWidget::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<"mouseMoveEvent";
//    QListWidgetItem *currentItem = this->itemAt(event->pos());;
//    if(!currentItem) {              //如果移动到了item外
//        return;
//    }

    if(m_ignoreMoveFlag || !m_mousePressFlag)
        return;


    if(event->buttons() == Qt::LeftButton) {
        int distance = (event->pos() - m_startPos).manhattanLength();
        if(distance >= QApplication::startDragDistance()) {             //判断拖动距离
            if(m_dragItem) {
                QMimeData *mimeData = new QMimeData;
                m_dragItem->GetMimData(mimeData);
                QDrag *m_drag = new QDrag(this);
                m_drag->setMimeData(mimeData);

                //设置拖放预览图
                m_drag->setPixmap(ChangeQImageBackTransparency(m_dragItem->grab().toImage()));
                //拖放在图片位置
                m_drag->setHotSpot(QPoint(event->pos().x() - m_startPos.x()+m_dragItem->width()/4,
                                          event->pos().y() - m_startPos.y()));        //拖动时的对于图片的位置

                Qt::DropAction retAction = m_drag->exec(Qt::MoveAction);
                if(retAction == Qt::MoveAction) {
                    if(m_dragItem)
                        m_dragItem->deleteLater();
                    delete m_startItem;
                };
            }
        }
    }

    QListWidget::mouseMoveEvent(event);
    QListWidgetItem *endItem = this->itemAt(m_endPos);
    if(endItem) {                   //选中移动后的结果
        endItem->setSelected(true);
    }
}

//拖拽移动事件
void MyListWidget::dragMoveEvent(QDragMoveEvent *event)
{
//    qDebug()<<"dragMoveEvent";
    MyListWidget *source = (MyListWidget *)((void *)(event->source()));
    QListWidgetItem *currentItem = this->itemAt(event->pos());;
//    if(!currentItem) {              //如果移动到了item外
//        event->ignore();
//        return;
//    }

    if(!currentItem || m_ignoreMoveFlag) {
        event->ignore();
        return;
    }


    if(source && source == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

//拖拽释放
void MyListWidget::dropEvent(QDropEvent *event)
{
    QListWidgetItem *currentItem = this->itemAt(event->pos());;         //拖拽后所在item
    MyListWidget *source = (MyListWidget *)((void *)(event->source()));

    if(!currentItem) {      //如果移动到了item外
        event->ignore();
        return;
    }

    if(source && source == this) {
        m_endPos = event->pos();                            //拖拽后的释放坐标
        //判断需要插入的行
        int insertRow = row(currentItem);
        if(m_startPos.y() < m_endPos.y()) {
            insertRow +=1;
        } else {
            insertRow = row(currentItem);
        }

        if(m_dragItem) {
            MyListItem *myItem = new MyListItem(m_dragItem);
            myItem->SetMimData(event->mimeData());
            this->InsertCustomItem(insertRow, myItem);
            event->setDropAction(Qt::MoveAction);
            event->accept();
            m_mousePressFlag = false;
        }
    }
}

//拖拽进入事件
void MyListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    MyListWidget *source = (MyListWidget *)((void *)(event->source()));
    if (source && source == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

bool MyListWidget::IsDragOutRage(QPoint pos)
{
//    qDebug()<<"IsDragOutRage";
    QListWidgetItem *currentItem = this->itemAt(pos);
    if(!currentItem) {              //如果移动到了item外
        qDebug()<<"IsDragOutRage:!currentItem";
        return true;
    }

    MyListItem *myItem = (MyListItem *)itemWidget(currentItem);
    QList<QPushButton*> btnList = myItem->findChildren<QPushButton*>();
    for(int i = 0; i < btnList.size(); i++) {
        QPushButton *btn = btnList.at(i);
        bool ret = btn->underMouse();
        if(ret) {
            qDebug()<<"underMouse true";
            return true;
        }
    }

    return false;
}

