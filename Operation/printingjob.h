#ifndef PRINTINGJOB_H
#define PRINTINGJOB_H

#include <QObject>

class PrintingJob : public QObject
{
    Q_OBJECT
public:
    explicit PrintingJob(QObject *parent = nullptr);

signals:

public slots:


};

#endif // PRINTINGJOB_H
