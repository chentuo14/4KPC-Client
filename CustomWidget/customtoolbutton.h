#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QPropertyAnimation>
#include <QPainter>

namespace Ui {
class Widget;
}

class CustomToolButton : public QToolButton
{
    enum BUTTON_STATUS{
        STATUS_NORMAL,
        STATUS_ENTER,
        STATUS_PRESSED
    };
public:
    explicit CustomToolButton(QWidget *parent = 0);
    void setButtonStatus(BUTTON_STATUS status);
    BUTTON_STATUS getButtonStatus();
    void paintEvent(QPaintEvent * event);
    void enterEvent(QEvent *evnet);
    void leaveEvent(QEvent *event);
public slots:
    void onValueChanged(QVariant val);
    void onBtnClickedDislapy();
    void onBtnClickedCancelDisplay();
private:
    QPropertyAnimation *m_animation;
    int m_animationOffset;
    bool m_mouseClickedFlag;
    BUTTON_STATUS m_buttonStatus;
};

#endif // CUSTOMTOOLBUTTON_H
