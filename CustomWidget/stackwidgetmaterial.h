#ifndef STACKWIDGETMATERIAL_H
#define STACKWIDGETMATERIAL_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QRect>

//#include "CustomControl/rollingcontrol.h"
#include "CustomControl/mylistitem.h"
#include "CustomControl/mylistwidget.h"
#include "CustomControl/mynumroll.h"

class StackWidgetMaterial : public QWidget
{
    Q_OBJECT
public:
    explicit StackWidgetMaterial(QWidget *parent = nullptr);
    ~StackWidgetMaterial();
    void InitControl();
protected:
    void IinitMatrailList();
    void InitDefaultAndCustomMaterialSwitch();
    void InitBaseLayerAndCureTime();
    void InitNormalLayerAndCureTime();

signals:

public slots:

private:
    /* 界面控件 */
//    rollingControl *m_thickRolling;
    MyNumRoll *m_thicknessesRol;                //层厚滚动选择
    QCheckBox *m_defaultMaterialCheck;
    QCheckBox *m_customMaterialCheck;
    QLabel *m_labelBaseLayerCureTimeName, *m_labelBaseLayerNumName;
    QLabel *m_labelLayerThicknessName, *m_labelNormalLayerCureTimeName;
//    QDoubleSpinBox *m_dsBaseLayerNum, *m_dsBaseLayerCureTime;
    MyNumRoll *m_baseLayerNum;                  //基层层数滚动选择
    MyNumRoll *m_baseLayerCureTimeUnit, *m_baseLayerCureTimeDecimal;
    QDoubleSpinBox *m_dsNormalLayerCureTime;
    MyListWidget *m_materialListWidget;
    /* 参数 */
    QRect m_materialListRect;
};

#endif // STACKWIDGETMATERIAL_H
