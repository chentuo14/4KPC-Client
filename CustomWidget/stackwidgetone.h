#ifndef STACKWIDGETONE_H
#define STACKWIDGETONE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>
#include "CustomWidget/printingwidget.h"

namespace Ui {
class StackWidgetOne;
}

class StackWidgetOne : public QWidget
{
    Q_OBJECT

public:
    explicit StackWidgetOne(QWidget *parent = 0);
    ~StackWidgetOne();
public slots:
    void CheckTimeTimerSlot();
    void OnPrintBtnClicked();
    void OnHistoryBtnClicked();
    void OnSettingBtnClicked();
signals:
    void btnHistoryClicked();
    void btnSettingClicked();
private:
    Ui::StackWidgetOne *ui;
    QLabel *m_labelTitle;
    QLabel *m_settingTitle, *m_settingStatus;       //设置部分
    QLabel *m_historyTitle, *m_historyStatus;
    QPushButton *m_btnPrint,*m_btnSetting,*m_btnHistory;
    QTimer *m_checkTimeTimer;
    PrintingWidget *m_printingWidget;

};

#endif // STACKWIDGETONE_H
