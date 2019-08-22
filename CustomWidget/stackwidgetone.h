#ifndef STACKWIDGETONE_H
#define STACKWIDGETONE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class StackWidgetOne;
}

class StackWidgetOne : public QWidget
{
    Q_OBJECT

public:
    explicit StackWidgetOne(QWidget *parent = 0);
    ~StackWidgetOne();

private:
    Ui::StackWidgetOne *ui;
    QLabel *m_labelTitle;
    QPushButton *m_btnPrint;
};

#endif // STACKWIDGETONE_H
