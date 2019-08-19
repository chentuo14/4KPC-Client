#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QPainter>
#include <QBitmap>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

public slots:
    void onCloseButtonSlot();
    void onMinButtonSlot();

protected:
    void InitMyWidget();
    void InitRightTopButton();

private:
    Ui::Widget *ui;
    QPoint m_mouseMovePoint;
    bool m_mousePressed;
    QToolButton *m_minButton, *m_closeButton, *m_skinButton, *m_settingButton;
};

#endif // WIDGET_H
