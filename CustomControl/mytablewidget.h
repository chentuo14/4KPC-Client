#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QEvent>
#include <QObject>
#include <QTimer>
#include <QLabel>
#include "CustomControl/nofocusdelegate.h"
#include "myglobal.h"

class MyTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit MyTableWidget(QWidget *parent = nullptr);
    void setTableSize(int level);
signals:

public slots:
    void onIconWaitTimer();
    void onPrintLogoChange(int rowIndex, PrintStatus status);
    void onPrintBaseLayerChange(int rowIndex, int num);
    void onPrintNormalLayerChange(int rowIndex, int num);
    void onPrintStatusChange(int rowIndex, PrintStatus status);
private:
    QTimer *m_iconTimer;
    int m_iconCount;
    int m_iconWaitRow;
};

#endif // MYTABLEWIDGET_H
