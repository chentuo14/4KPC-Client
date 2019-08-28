#ifndef MYSTACKEDWIDGET_H
#define MYSTACKEDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QPainter>

class MyStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MyStackedWidget(QWidget *parent =0);
    void paintEvent(QPaintEvent *event);
    void paintPrintingWidget(int oldIndex, int newIndex);

public slots:
    void onFinishSlideAnimation();
    void onPrintingSlideValueChanged(QVariant value);
    void onEnterPrintingWidget(int startValue);
    void onExitPrintingWidget(int startValue);
    void onWidgetChanged(int index);
    void onPrintStartDisplay();
    void onPrintCancelDisplay();

private:
    QPropertyAnimation *m_slideWidgetAnimation;
    QVariant m_changedValue;
    int m_slideFlag;
    const int m_printReadyIndex = 0;
    const int m_printingIndex = 6;
};

#endif // MYSTACKWIDGET_H
