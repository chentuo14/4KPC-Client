#ifndef STACKWIDGETPRINTING_H
#define STACKWIDGETPRINTING_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
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

signals:
    void onStartCycleSignal(int msec);
    void onStopCycleSignal();
    void onCancelSignal();

private:
    Ui::StackWidgetPrinting *ui;
    QPushButton *m_btnCancel, *m_btnPasuse;
    CycleProcess *m_cycleProcess;
    QLabel *m_statusTitle, *m_statusContext;
    QProgressBar *m_pritingBar;
    QTimer m_testTimer;
    int m_progressValue = 0;

};

#endif // STACKWIDGETPRINTING_H
