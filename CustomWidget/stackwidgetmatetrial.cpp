#include "stackwidgetmaterial.h"

StackWidgetMaterial::StackWidgetMaterial(QWidget *parent) : QWidget(parent)
{
    m_materialListRect.setX(0);
    m_materialListRect.setY(0);
    m_materialListRect.setWidth(280);
    m_materialListRect.setHeight(400);

    InitControl();
}

StackWidgetMaterial::~StackWidgetMaterial()
{

}

void StackWidgetMaterial::InitControl()
{
    IinitMatrailList();

    InitDefaultAndCustomMaterialSwitch();

    InitBaseLayerAndCureTime();

    InitNormalLayerAndCureTime();
}

void StackWidgetMaterial::IinitMatrailList()
{
    /* 材料列表 */
    m_materialListWidget = new MyListWidget(this);
    m_materialListWidget->setGeometry(0,0,m_materialListRect.width(),m_materialListRect.height());
}

void StackWidgetMaterial::InitDefaultAndCustomMaterialSwitch()
{
    /* 默认材料和自定义材料初始化 */
    m_defaultMaterialCheck = new QCheckBox(this);
    m_customMaterialCheck = new QCheckBox(this);
    m_defaultMaterialCheck->move(50,m_materialListRect.height()+5);
    m_customMaterialCheck->move(150,m_materialListRect.height()+5);
    m_defaultMaterialCheck->setText(QString("默认材料"));
    m_customMaterialCheck->setText(QString("自定义材料"));
}

void StackWidgetMaterial::InitBaseLayerAndCureTime()
{
    /* 基层数和曝光时间 */
    m_labelBaseLayerNumName = new QLabel(this);
    m_labelBaseLayerNumName->setText("基层数量");
    m_labelBaseLayerNumName->move(m_materialListRect.width()+50, 100);

    m_labelBaseLayerCureTimeName = new QLabel(this);
    m_labelBaseLayerCureTimeName->setText("基层固化时间");
    m_labelBaseLayerCureTimeName->move(m_materialListRect.width()+50, 250);

    /* 基层数 */
    m_baseLayerNum = new MyNumRoll(this);
    m_baseLayerNum->setGeometry(m_materialListRect.width()+100, 100, 100, 50);
    m_baseLayerNum->setMaxRange(100);
    m_baseLayerNum->setMinRange(0);
    m_baseLayerNum->setIsVertial(false);
    m_baseLayerNum->setCurrentValue(3);
    /* 基层曝光时间整数部分 */
    m_baseLayerCureTimeUnit = new MyNumRoll(this);
    m_baseLayerCureTimeUnit->setGeometry(m_materialListRect.width()+150, 200, 50, 100);
    m_baseLayerCureTimeUnit->setMaxRange(99);
    m_baseLayerCureTimeUnit->setMinRange(0);
    m_baseLayerCureTimeUnit->setIsVertial(true);
    m_baseLayerCureTimeUnit->setCurrentValue(1);
    /* 基层曝光时间小数部分 */
    m_baseLayerCureTimeDecimal = new MyNumRoll(this);
    m_baseLayerCureTimeDecimal->setMaxRange(99);
    m_baseLayerCureTimeDecimal->setMinRange(0);
    m_baseLayerCureTimeDecimal->setCurrentValue(0);
    m_baseLayerCureTimeDecimal->setGeometry(m_baseLayerCureTimeUnit->x()+m_baseLayerCureTimeUnit->width()+10,200,50,100);

}

void StackWidgetMaterial::InitNormalLayerAndCureTime()
{
    /* 选择厚度 */
    m_labelLayerThicknessName = new QLabel(this);
    m_labelLayerThicknessName->move(m_materialListRect.width()+50, 320);
    m_labelLayerThicknessName->setText("层厚");
//    m_thickRolling = new rollingControl(this);
//    m_thickRolling->setGeometry(m_materialListRect.width()+100, 300, 90, 50);
    m_thicknessesRol = new MyNumRoll(this);
    m_thicknessesRol->setGeometry(m_materialListRect.width()+100, 300, 100, 50);
    m_thicknessesRol->setIsVertial(false);
    m_thicknessesRol->setMaxRange(100);
    m_thicknessesRol->setMinRange(10);
    m_thicknessesRol->setInterval(10);
    m_thicknessesRol->setCurrentValue(50);

    m_labelNormalLayerCureTimeName = new QLabel(this);
    m_labelNormalLayerCureTimeName->move(m_materialListRect.width()+50, 350);
    m_labelNormalLayerCureTimeName->setText("片层固化时间");
    m_dsNormalLayerCureTime = new QDoubleSpinBox(this);
    m_dsNormalLayerCureTime->move(m_materialListRect.width()+100, 350);
}
