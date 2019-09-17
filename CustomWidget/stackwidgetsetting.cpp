#include "stackwidgetsetting.h"

StackWidgetSetting::StackWidgetSetting(QWidget *parent) : QWidget(parent)
{
    InitControl();
}

StackWidgetSetting::~StackWidgetSetting()
{

}

void StackWidgetSetting::InitControl()
{
    /* 材料列表 */
    int matrialWidth = 280;
    int matrialHeight = 400;
    m_matrialListWidget = new MyListWidget(this);
    m_matrialListWidget->setGeometry(0,0,matrialWidth,matrialHeight);

    /* 默认材料和自定义材料初始化 */
    m_defaultMatrialCheck = new QCheckBox(this);
    m_customMatrialCheck = new QCheckBox(this);
    m_defaultMatrialCheck->move(50,matrialHeight+5);
    m_customMatrialCheck->move(150,matrialHeight+5);
    m_defaultMatrialCheck->setText(QString("默认材料"));
    m_customMatrialCheck->setText(QString("自定义材料"));

    /* 材料名称初始化 */
    m_labelMatrialName = new QLabel(this);
    m_labelMatrialDescription = new QLabel(this);
    m_labelMatrialName->setText("材料名称：");
    m_labelMatrialDescription->setText("材料描述：");
    m_labelMatrialName->move(matrialWidth+50, 100);
    m_labelMatrialDescription->move(matrialWidth+50, 150);

    m_cbMatrialName = new QComboBox(this);
    m_cbMatrialName->move(matrialWidth+100, 100);
    m_leMatrialDescption = new QLineEdit(this);
    m_leMatrialDescption->move(matrialWidth+100, 150);

    /* 基层数和曝光时间 */
    m_labelBaseLayerNumName = new QLabel(this);
    m_labelBaseLayerCureTimeName = new QLabel(this);
    m_labelBaseLayerNumName->setText("基层数量");
    m_labelBaseLayerCureTimeName->setText("基层固化时间");
    m_labelBaseLayerNumName->move(matrialWidth+50, 200);
    m_labelBaseLayerCureTimeName->move(matrialWidth+50, 250);
    m_dsBaseLayerNum = new QDoubleSpinBox(this);
    m_dsBaseLayerCureTime = new QDoubleSpinBox(this);
    m_dsBaseLayerNum->move(matrialWidth+100, 200);
    m_dsBaseLayerCureTime->move(matrialWidth+100, 250);

    /* 选择厚度 */
    m_labelLayerThicknessName = new QLabel(this);
    m_thickRolling = new rollingControl(this);
    m_labelLayerThicknessName->move(matrialWidth+50, 300);
    m_thickRolling->setGeometry(matrialWidth+100, 300, 90, 50);
    m_labelLayerThicknessName->setText("层厚");
    m_labelNormalLayerCureTimeName = new QLabel(this);
    m_labelNormalLayerCureTimeName->move(matrialWidth+50, 350);
    m_labelNormalLayerCureTimeName->setText("片层固化时间");
    m_dsNormalLayerCureTime = new QDoubleSpinBox(this);
    m_dsNormalLayerCureTime->move(matrialWidth+100, 350);
}
