#ifndef CYCLEPROCESS_H
#define CYCLEPROCESS_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QGridLayout>

class CycleProcess : public QWidget
{
    Q_OBJECT
public:
    explicit CycleProcess(QWidget *parent = nullptr);
    ~CycleProcess();

    void paintEvent(QPaintEvent *event);
    void setLabelText(QString text);
    QLabel *getCenterLabel();
signals:

public slots:
    void onRotateTimer();
    void startCycleProcess(int msec);
    void stopCycleProcess();
private:
    int m_angle;
    QTimer *m_rotateTimer;
    int m_paintOffset;
    QLabel *m_centerLabel;
};

#endif // CYCLEPROCESS_H
