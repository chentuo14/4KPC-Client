#ifndef STACKWIDGETSETTING_H
#define STACKWIDGETSETTING_H

#include <QObject>
#include <QWidget>
#include "CustomControl/rollingcontrol.h"

class StackWidgetSetting : public QWidget
{
    Q_OBJECT
public:
    explicit StackWidgetSetting(QWidget *parent = nullptr);

signals:

public slots:


private:
    rollingControl *m_thickRolling;
};

#endif // STACKWIDGETSETTING_H
