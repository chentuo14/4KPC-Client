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
#include "customtoolbutton.h"

namespace Ui {
class LeftMenuBar;
}

class LeftMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeftMenuBar(QWidget *parent = 0);
    ~LeftMenuBar();

    void DeleteLayout();
    void InitControl();
    void initBtns(int num);
    void addBtn(CustomToolButton *btn, int id);
    void paintEvent(QPaintEvent *event);
public slots:
    void OnBtnClicked(int index);

signals:


private:
    Ui::LeftMenuBar *ui;
    QButtonGroup *m_btnGroup;
    QVector<CustomToolButton *> m_btnVec;
    QVBoxLayout *m_menuLayout;
    QGridLayout *m_logoLayout;
    QPropertyAnimation *m_animation;
    int m_buttonCurrIndex;
    int m_buttonPrevIndex;
    int m_bottomSpace;
};

#endif // LEFTMENUBAR_H
