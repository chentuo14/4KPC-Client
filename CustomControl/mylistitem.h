#ifndef MYLIST_H
#define MYLIST_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>
#include <QLineEdit>
#include <QPainter>
#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include <QMimeData>

class MyListItem : public QWidget
{
    Q_OBJECT
public:
    explicit MyListItem(QWidget *parent = nullptr);
    explicit MyListItem(MyListItem *item);

    void SetItemMatrialInfo(QString name, QString description);
    void GetMimData(QMimeData *data);
    void SetMimData(const QMimeData *data);
    void SetMatrialName(QString name);
    QString GetMatrialName();
    void SetMatrialDescription(QString description);
    QString GetMatrialDescription();
    void SetItemSelectedFlag(bool flag);
    bool GetItemSelectedFlag();
    void SetItemEditable(bool flag);
    bool GetItemEditable();
    void SetMatrials(QString string);
    QStringList GetMatrials();

    void SelectMatrialDisplay();
    void UnselectMatrialDisplay();
    void SetItemEditText();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    void InitDefaultParamters();
    void InitMatrialInfomations();
    void InitButtons();
    void InitLayout();
    void HideOperationButton();
    void ShowOperationButton();

signals:
    void onBtnDelClickedSignal(QPoint pos);
    void onBtnEditClickedSignal(QPoint pos);
    void onBtnSelectClickedSignal(QPoint pos);

public slots:
    void onBtnUpClicked();
    void onBtnDownClicked();
    void onBtnEditClicked();
    void onBtnDelClicked();
    void onBtnSelectClicked();
private:
    /* 材料相关 */
    QLabel *m_titleName, *m_titleDescritpion;
    QLabel *m_matrialName, *m_matrialDescription;
    QLabel *m_selectIcon;
    QStringList m_matrials;
    /* 右侧按钮 */
    QPushButton *m_btnDel, *m_btnEdit, *m_btnSelect;
    QGridLayout *m_mainlayout;
    QLineEdit *m_matrialNameEdit, *m_matrialDescriptionEdit;
    bool m_mouseEnterFlag, m_selectedFlag;
    bool m_isEditable;

};

#endif // MYLIST_H
