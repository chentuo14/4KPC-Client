#include "mytablewidget.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QPalette>
#include <QHeaderView>
#include <QHeaderView>

MyTableWidget::MyTableWidget(QWidget *parent) : QTableWidget(parent)
{
    /* 透明 */
    QPalette pll = this->palette();
    pll.setBrush(QPalette::Base,QBrush(QColor(255,255,255,0)));
    this->setPalette(pll);
    /* 去掉行号 */
    this->verticalHeader()->setHidden(true);;
    this->setGeometry(250,250,350,200);
    /* 数据设置 */
    QStringList  headTitleList;
    headTitleList<<"图标"<<"打印项"<<"打印统计"<<"状态";
    this->setColumnCount(headTitleList.count());
    this->setHorizontalHeaderLabels(headTitleList);
    this->horizontalHeader()->setHidden(true);
    this->setRowCount(5);
    this->setItem(0, 0, new QTableWidgetItem("图标"));
    this->setItem(0, 1, new QTableWidgetItem("打印项"));
    this->setItem(0, 2, new QTableWidgetItem("打印统计"));
    this->setItem(0, 3, new QTableWidgetItem("状态"));

    this->setItem(1, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progress0.png"), ""));
    this->setItem(2, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progressWait.png"), ""));
    this->setItem(3, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progressWait.png"), ""));
    this->setItem(4, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progressFinish.png"), ""));
    this->setItem(5, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progressWait.png"), ""));

    this->setShowGrid(false);                      //去表格线
    this->setStyleSheet("QTableView{ border:none; background:transparent; }  QTableView::item:selected{ color:white; background:rgba(200, 200, 200, 0);}");       //去外边框
    this->setItemDelegate(new NoFocusDelegate());  /* 单元格无法选中 */
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i=0;i<this->columnCount();i++) {
        this->item(0,i)->setFlags(this->item(0,i)->flags()&~Qt::ItemIsSelectable);
    }
    this->setColumnWidth(0, 30);
    this->setItem(1, 1, new QTableWidgetItem("平台下移初始化"));
    this->setItem(2, 1, new QTableWidgetItem("打印基层"));
    this->setItem(3, 1, new QTableWidgetItem("打印片层"));
    this->setItem(4, 1, new QTableWidgetItem("平台完成上移"));
    this->setItem(1, 2, new QTableWidgetItem("打印1项"));
    this->setItem(2, 2, new QTableWidgetItem("打印xx基层"));
    this->setItem(3, 2, new QTableWidgetItem("打印xx片层"));
    this->setItem(4, 2, new QTableWidgetItem("打印1项"));
    this->setItem(1, 3, new QTableWidgetItem("运行中..."));
    this->setItem(2, 3, new QTableWidgetItem("等待中..."));
    this->setItem(3, 3, new QTableWidgetItem("等待中..."));
    this->setItem(4, 3, new QTableWidgetItem("等待中..."));
//    this->setCellWidget(5, 3, new QLabel("完成"));
    ((QLabel)this->cellWidget(5, 3)).setAlignment(Qt::AlignCenter);
    /* 初始化图标等待计时器 */
    m_iconTimer = new QTimer();
    m_iconTimer->setInterval(150);
    m_iconCount = 0;
    m_iconWaitRow = -1;
    connect(m_iconTimer, &QTimer::timeout, this, &MyTableWidget::onIconWaitTimer);
    this->setSpan(0,0,1,1);
    this->item(0,0)->setText("");
    this->item(0,1)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    this->setTableSize(0);
}

void MyTableWidget::setTableSize(int level)
{
    switch(level) {
    case 0:
        this->setGeometry(100, 250, 500, 200);
//        this->setStyleSheet("QTableView{ border:1px solid black; background:transparent; }  QTableView::item:selected{ color:white; background:rgb(200, 200, 200);}");
        this->setColumnWidth(0, 50);
        this->setColumnWidth(1, 150);
        this->setColumnWidth(2, 150);
        this->setColumnWidth(3, 150);
        break;
    case 1:
        break;
    case 2:
        break;
    case 5:
        break;
    default:
        break;
    }
}

void MyTableWidget::onIconWaitTimer()
{
    if(m_iconWaitRow==-1) {
        m_iconTimer->stop();
    }
    m_iconCount %= 8;
    this->setItem(m_iconWaitRow, 0, new QTableWidgetItem(QIcon(QString(":/buttonIcon/progress%0.png").arg(m_iconCount)), ""));
    m_iconCount++;
}

void MyTableWidget::onPrintLogoChange(int rowIndex, PrintStatus status)
{
    switch(status) {
    case PrintStatus::StatusWaiting:
        this->setItem(rowIndex, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progressWait.png"), ""));
        break;
    case PrintStatus::StatusPrinting:
        m_iconWaitRow = rowIndex;
        m_iconTimer->start();
        break;
    case PrintStatus::StatusFinished:
        this->setItem(rowIndex, 0, new QTableWidgetItem(QIcon(":/buttonIcon/progressFinish.png"), ""));
        break;
    default:
        break;
    }
}

void MyTableWidget:: onPrintBaseLayerChange(int rowIndex, int num)
{
    QTableWidgetItem *pItem = this->item(rowIndex, 2);
    if(pItem == 0) {
        qDebug()<<"No this item";
        return;
    }
    this->item(rowIndex, 2)->setText(QString("已打印%1层基层").arg(num));
}

void MyTableWidget::onPrintNormalLayerChange(int rowIndex, int num)
{
     QTableWidgetItem *pItem = this->item(rowIndex, 0);
     if(pItem == 0) {
         qDebug()<<"No this item";
         return;
     }
     this->item(rowIndex, 2)->setText(QString("已打印%1层片层").arg(num));
}

void MyTableWidget::onPrintStatusChange(int rowIndex, PrintStatus status)
{
    switch(status) {
    case PrintStatus::StatusWaiting:
        this->item(rowIndex, 3)->setText("等待中...");
        this->item(rowIndex, 3)->setTextColor(QColor(0, 0, 0));
        break;
    case PrintStatus::StatusPrinting:
        this->item(rowIndex, 3)->setText("运行中...");
        this->item(rowIndex, 3)->setTextColor(QColor(0, 0, 0));
        break;
    case PrintStatus::StatusFinished:
        this->item(rowIndex, 3)->setText("完成");
        this->item(rowIndex, 3)->setTextColor(QColor(14, 209, 69));
        break;
    default:
        break;
    }
}
