#ifndef ROLLINGCONTROL_H
#define ROLLINGCONTROL_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QPen>
#include <QMouseEvent>
#include <QPropertyAnimation>

class rollingControl : public QWidget
{
    Q_OBJECT
public:
    explicit rollingControl(QWidget *parent = nullptr);
    ~rollingControl();
    void initAmiationConfig();
    void drawMyTestNum(int x, int y, int num);
    void drawMyTestNum(int x, int y, int num, int size);
    int caculateMoveLength(int xPos, int width);
    bool checkPosOverMax(int pos);
    bool checkPosUnderMin(int pos);
    bool checkPosOutOfSize(int pos);
    void updateNumWidth(int size);
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
signals:

public slots:
    void onMoveCenterValueChange(QVariant value);
private:
    QPropertyAnimation *m_movCenterAnimation;       //回中动画
    int m_numPos;                                   //数字串的位置
    int m_mouseStartPos;                            //鼠标按下左键的坐标
    int m_mouseMoveDistance;                        //移动的距离
    int m_mouseReleasePos;                          //鼠标释放
    bool m_animationFlag;                           //动画执行标志
    int m_numWidth;                                 //单个数字的宽度
    int m_maxPos;                                   //数字的最大位置
    int m_minPos;                                   //数字的最小位置
    int m_currentCenterPos;                         //当前中心位置坐标
};

#endif // ROLLINGCONTROL_H
