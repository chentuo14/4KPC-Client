#ifndef MYNUMROLL_H
#define MYNUMROLL_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPainter>
#include <QWheelEvent>

class MyNumRoll : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int m_deviation READ getDeviation WRITE setDeviation)
    Q_PROPERTY(double m_minRange READ getMinRange WRITE setMinRange)
    Q_PROPERTY(double m_maxRange READ getMaxRange WRITE setMaxRange)
    Q_PROPERTY(double m_currentValue READ getCurrentValue WRITE setCurrentValue NOTIFY onCurrentValueChanged)
    Q_PROPERTY(double m_numSize READ getNumSize WRITE setNumSize)
    Q_PROPERTY(double m_interval READ getInterval WRITE setInterval)
    Q_PROPERTY(bool m_isVertial READ getIsVertial WRITE setIsVertial)
    Q_PROPERTY(int m_height READ getMHeight WRITE setMHeight)
    Q_PROPERTY(int m_width READ getMWidth WRITE setMWidth)
    Q_PROPERTY(QColor m_numColor READ getNumColor WRITE setNumColor)
    Q_PROPERTY(bool m_hasUnderLine READ getHasUnderLine WRITE setHasUnderLine)
    Q_PROPERTY(int m_separateNum READ getSeparateNum WRITE setSeparateNum)

public:
    explicit MyNumRoll(QWidget *parent = nullptr);
    void SetDefaultParamers();
    /* getset函数 */
    void setDeviation(int deviation) { m_deviation = deviation; repaint();}
    int getDeviation() {return m_deviation;}
    void setMinRange(double minValue) {m_minRange = minValue;}
    double getMinRange() {return m_minRange;}
    void setMaxRange(double maxValue) {m_maxRange = maxValue;}
    double getMaxRange() {return m_maxRange;}
    void setCurrentValue(double value) {m_currentValue = value;}
    double getCurrentValue() {return m_currentValue;}
    void setNumSize(double size) {m_numSize = size;}
    double getNumSize() {return m_numSize;}
    void setInterval(double value) {m_interval = value;}
    double getInterval() {return m_interval;}
    void setIsVertial(bool flag) {m_isVertial = flag;}
    bool getIsVertial() {return m_isVertial;}
    void setMHeight(int height) {m_height = height;}
    int getMHeight() {return m_height;}
    void setMWidth(int width) {m_width = width;}
    int getMWidth() {return m_width;}
    void setNumColor(QColor color) {m_numColor = color;}
    QColor getNumColor() {return m_numColor;}
    void setHasUnderLine(bool flag) { m_hasUnderLine = flag;}
    bool getHasUnderLine() {return m_hasUnderLine;}
    void setSeparateNum(int num) {m_separateNum = num;}
    int getSeparateNum() {return m_separateNum;}

signals:
    void onCurrentValueChanged(double);

public slots:
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintNum(QPainter &painter, double num, int shifting);
    void numMoveCenter();

private:
    double m_minRange;                      //最小值
    double m_maxRange;                      //最大值
    double m_currentValue;                  //当前选中的值
    bool m_isDragging;                      //鼠标是否按下
    int m_deviation;                        //偏移量，记录鼠标按下后移动的垂直距离
    int m_mouseSrcPos;
    double m_numSize;                       //数字大小
    QPropertyAnimation *m_moveCenterAni;
    double m_interval;                      //间隔大小
    int m_separateNum;                      //分隔数量
    bool m_isVertial;                       //是否垂直显示
    int m_height;
    int m_width;
    bool m_hasUnderLine;
    QColor m_numColor;

};

#endif // MYNUMROLL_H
