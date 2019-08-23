#ifndef STACKWIDGETONE_H
#define STACKWIDGETONE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDateTime>

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
private:
    Ui::StackWidgetOne *ui;
    QLabel *m_labelTitle;
    QPushButton *m_btnPrint;
    QTimer *m_checkTimeTimer;
};

#endif // STACKWIDGETONE_H
