#ifndef STACKWIDGETPRINTING_H
#define STACKWIDGETPRINTING_H

#include <QWidget>
#include <QPushButton>

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
signals:
    void onCancelSignal();

private:
    Ui::StackWidgetPrinting *ui;
    QPushButton *m_btnCancel;
};

#endif // STACKWIDGETPRINTING_H
