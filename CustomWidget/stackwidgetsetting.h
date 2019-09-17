#ifndef STACKWIDGETSETTING_H
#define STACKWIDGETSETTING_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDoubleSpinBox>
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

signals:

public slots:

private:
    rollingControl *m_thickRolling;
    QCheckBox *m_defaultMatrialCheck;
    QCheckBox *m_customMatrialCheck;
    QLabel *m_labelMatrialName, *m_labelMatrialDescription;
    QLabel *m_labelBaseLayerCureTimeName, *m_labelBaseLayerNumName;
    QLabel *m_labelLayerThicknessName, *m_labelNormalLayerCureTimeName;
    QDoubleSpinBox *m_dsBaseLayerNum, *m_dsBaseLayerCureTime;
    QDoubleSpinBox *m_dsNormalLayerCureTime;
    QComboBox *m_cbMatrialName;
    QLineEdit *m_leMatrialDescption;
    MyListWidget *m_matrialListWidget;
};

#endif // STACKWIDGETSETTING_H
