#include "stackwidgetsetting.h"

StackWidgetSetting::StackWidgetSetting(QWidget *parent) : QWidget(parent)
{
    m_matrialListRect.setX(0);
    m_matrialListRect.setY(0);
    m_matrialListRect.setWidth(280);
    m_matrialListRect.setHeight(400);

    InitControl();
}

StackWidgetSetting::~StackWidgetSetting()
{

}

void StackWidgetSetting::InitControl()
{
    IinitMatrailList();

    InitDefaultAndCustomMatrialSwitch();

    InitBaseLayerAndCureTime();

    InitNormalLayerAndCureTime();
}

void StackWidgetSetting::IinitMatrailList()
{
    /* 材料列表 */
    m_matrialListWidget = new MyListWidget(this);
    m_matrialListWidget->setGeometry(0,0,m_matrialListRect.width(),m_matrialListRect.height());
}

void StackWidgetSetting::InitDefaultAndCustomMatrialSwitch()
{
    /* 默认材料和自定义材料初始化 */
    m_defaultMatrialCheck = new QCheckBox(this);
    m_customMatrialCheck = new QCheckBox(this);
    m_defaultMatrialCheck->move(50,m_matrialListRect.height()+5);
    m_customMatrialCheck->move(150,m_matrialListRect.height()+5);
    m_defaultMatrialCheck->setText(QString("默认材料"));
    m_customMatrialCheck->setText(QString("自定义材料"));
}

void StackWidgetSetting::InitBaseLayerAndCureTime()
{
    /* 基层数和曝光时间 */
    m_labelBaseLayerNumName = new QLabel(this);
    m_labelBaseLayerCureTimeName = new QLabel(this);
    m_labelBaseLayerNumName->setText("基层数量");
    m_labelBaseLayerCureTimeName->setText("基层固化时间");
    m_labelBaseLayerNumName->move(m_matrialListRect.width()+50, 200);
    m_labelBaseLayerCureTimeName->move(m_matrialListRect.width()+50, 250);
    m_dsBaseLayerNum = new QDoubleSpinBox(this);
    m_dsBaseLayerCureTime = new QDoubleSpinBox(this);
    m_dsBaseLayerNum->move(m_matrialListRect.width()+100, 200);
    m_dsBaseLayerCureTime->move(m_matrialListRect.width()+100, 250);
}

void StackWidgetSetting::InitNormalLayerAndCureTime()
{
    /* 选择厚度 */
    m_labelLayerThicknessName = new QLabel(this);
    m_thickRolling = new rollingControl(this);
    m_labelLayerThicknessName->move(m_matrialListRect.width()+50, 300);
    m_thickRolling->setGeometry(m_matrialListRect.width()+100, 300, 90, 50);
    m_labelLayerThicknessName->setText("层厚");
    m_labelNormalLayerCureTimeName = new QLabel(this);
    m_labelNormalLayerCureTimeName->move(m_matrialListRect.width()+50, 350);
    m_labelNormalLayerCureTimeName->setText("片层固化时间");
    m_dsNormalLayerCureTime = new QDoubleSpinBox(this);
    m_dsNormalLayerCureTime->move(m_matrialListRect.width()+100, 350);
}
