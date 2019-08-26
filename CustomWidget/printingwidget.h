#ifndef PRINTINGWIDGET_H
#define PRINTINGWIDGET_H

#include <QWidget>

namespace Ui {
class PrintingWidget;
}

class PrintingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrintingWidget(QWidget *parent = 0);
    ~PrintingWidget();

private:
    Ui::PrintingWidget *ui;
};

#endif // PRINTINGWIDGET_H
