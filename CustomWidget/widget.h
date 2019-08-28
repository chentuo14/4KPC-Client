#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QToolButton>
#include <QPainter>
#include <QBitmap>
#include <QStackedWidget>
#include <QIcon>
#include "CustomWidget/leftmenubar.h"
#include "CustomWidget/stackwidgetone.h"
#include "CustomWidget/mystackedwidget.h"
#include "CustomWidget/stackwidgetprinting.h"

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
    void InitLeftButton();
    void InitWidgetOne();           /* 起始界面 */

private:
    Ui::Widget *ui;
    /* 左侧菜单 */
    LeftMenuBar *m_leftMenu;
    int m_leftMenuNum;
    int m_leftMenuWidth;
    MyStackedWidget *m_stackWidget;
    QPoint m_mouseMovePoint;
    bool m_mousePressed;
    QToolButton *m_minButton, *m_closeButton, *m_skinButton, *m_settingButton;
    /* 第一个选项的界面 */
    StackWidgetOne *m_widgteOne;
    QLabel *m_widOneTitle;
    StackWidgetPrinting *m_printingWidget;
};

#endif // WIDGET_H
