#ifndef STACKWIDGETSETTING_H
#define STACKWIDGETSETTING_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QRect>

#include "CustomControl/rollingcontrol.h"
#include "CustomControl/mylistitem.h"
#include "CustomControl/mylistwidget.h"

class StackWidgetSetting : public QWidget
{
    Q_OBJECT
public:
    explicit StackWidgetSetting(QWidget *parent = nullptr);
    ~StackWidgetSetting();
    void InitControl();
protected:
    void IinitMatrailList();
    void InitDefaultAndCustomMatrialSwitch();
    void InitBaseLayerAndCureTime();
    void InitNormalLayerAndCureTime();

signals:

public slots:

private:
    /* 界面控件 */
    rollingControl *m_thickRolling;
    QCheckBox *m_defaultMatrialCheck;
    QCheckBox *m_customMatrialCheck;
    QLabel *m_labelBaseLayerCureTimeName, *m_labelBaseLayerNumName;
    QLabel *m_labelLayerThicknessName, *m_labelNormalLayerCureTimeName;
    QDoubleSpinBox *m_dsBaseLayerNum, *m_dsBaseLayerCureTime;
    QDoubleSpinBox *m_dsNormalLayerCureTime;
    MyListWidget *m_matrialListWidget;
    /* 参数 */
    QRect m_matrialListRect;
};

#endif // STACKWIDGETSETTING_H
