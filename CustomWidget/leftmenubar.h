#ifndef LEFTMENUBAR_H
#define LEFTMENUBAR_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QVector>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPoint>
#include <QLabel>
#include "CustomWidget/customtoolbutton.h"

namespace Ui {
class LeftMenuBar;
}

class LeftMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftMenuBar(QWidget *parent = 0);
    ~LeftMenuBar();

    void DeleteLayout();                /* 删除布局 */
    void InitControl();                 /* 按钮之外初始化 */
    void initBtns(int num);             /* 初始化按钮 */
    void addBtn(CustomToolButton *btn, int id); /* 向buttonGroup中添加button */
    void setBtnIcon(int index, QString uncheckedPath, QString checkedPath);
    QButtonGroup *getLeftMenuButtonGroup();     /* 获取group指针 */
    QVector<CustomToolButton *> *getCustomToolButtonVec();
    void paintEvent(QPaintEvent *event);        /* 界面重绘 */
public slots:
    void OnBtnClicked(int index);               /* 按钮点击事件 */

signals:

private:
    Ui::LeftMenuBar *ui;
    QButtonGroup *m_btnGroup;
    QVector<CustomToolButton *> *m_btnVec;
    QVBoxLayout *m_menuLayout;
    QGridLayout *m_logoLayout;
    QPropertyAnimation *m_animation;
    QVector<QString> m_buttonIconPath;
    int m_buttonCurrIndex;
    int m_buttonPrevIndex;
    int m_bottomSpace;
};

#endif // LEFTMENUBAR_H
