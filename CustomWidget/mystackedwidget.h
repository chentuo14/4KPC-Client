#ifndef MYSTACKEDWIDGET_H
#define MYSTACKEDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>

class MyStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MyStackedWidget(QWidget *parent =0);
    void paintEvent(QPaintEvent *event);

public slots:
    void onDisplayPrintingWidget();

private:
    QPropertyAnimation *m_slideWidgetAnimation;
};

#endif // MYSTACKWIDGET_H
