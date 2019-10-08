#ifndef MYPRINTINGTHREAD_H
#define MYPRINTINGTHREAD_H

#include <QObject>
#include <QThread>

class MyPrintingThread : public QThread
{
    Q_OBJECT
public:
    MyPrintingThread();

signals:
    void message(const QString &info);
    void progress(int present);
};

#endif // MYPRINTINGTHREAD_H
