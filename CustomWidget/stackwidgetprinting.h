#ifndef STACKWIDGETPRINTING_H
#define STACKWIDGETPRINTING_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include "CustomControl/mytablewidget.h"
#include "CustomControl/cycleprocess.h"

namespace Ui {
class StackWidgetPrinting;
}

class StackWidgetPrinting : public QWidget
{
    Q_OBJECT

public:
    explicit StackWidgetPrinting(QWidget *parent = 0);
    ~StackWidgetPrinting();
public slots:
    void onCancelBtnClicked();
    void onTestTimer();
    void onProgressValueChange(int value);

signals:
    void onStartCycleSignal(int msec);
    void onStopCycleSignal();
    void onCancelSignal();

private:
    Ui::StackWidgetPrinting *ui;
    QPushButton *m_btnCancel, *m_btnPasuse;                     //取消按钮、暂停按钮
    CycleProcess *m_cycleProcess;                               //圆圈进度
    QLabel *m_statusTitle, *m_statusContext;                    //主状态、此状态label
    QProgressBar *m_pritingBar;                                 //打印进度条
    QTimer m_testTimer;
    MyTableWidget *m_printStatusTable;                          //打印信息表格
    int m_progressValue = 0;

};

#endif // STACKWIDGETPRINTING_H
