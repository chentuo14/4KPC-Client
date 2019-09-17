#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QPoint>
#include <QDrag>
#include <QApplication>
#include <QListWidgetItem>

#include "CustomControl/mylistitem.h"
#include "CustomControl/nofocusdelegate.h"

class MyListWidget : public QListWidget
{
public:
    MyListWidget(QWidget *parent = 0);
    ~MyListWidget();

    void LoadDefaultMatrialList(QString filePath);
    void LoadCustomMatrialList(QString filePath);
    void InsertCustomItem(MyListItem *customItem);
    void InsertCustomItem(int rowIndex, MyListItem *customItem);
    void ConnectCustomSignalAndSlot(MyListItem *customItem);
    void DisconnectCustomSignalAndSlot(MyListItem *customItem);
    QPixmap ChangeQImageBackTransparency(QImage image);
    void ClearDragPointer();
public slots:
    void OnDelItemClicked(QPoint pos);
    void OnEditItemClicked(QPoint pos);
    void OnSelectedClicked(QPoint pos);
    void OnHideDefaultMatrial(bool flag);
    void OnHideCustomMatrial(bool flag);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
//    bool eventFilter(QObject *obj, QEvent *event);

    bool IsDragOutRage(QPoint pos);

private:
    QPoint m_startPos, m_endPos;
    QListWidgetItem *m_startItem;
    MyListItem *m_dragItem;
    bool m_isDragFlag, m_ignoreMoveFlag, m_mousePressFlag;
    QStringList m_matrialList;
};

#endif // MYLISTWIDGET_H
