#include "stackwidgetsetting.h"

StackWidgetSetting::StackWidgetSetting(QWidget *parent) : QWidget(parent)
{
    m_thickRolling = new rollingControl(this);
    m_thickRolling->setGeometry(50, 50, 90, 50);
}
