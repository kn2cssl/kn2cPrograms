#ifndef LOGPLAYER_H
#define LOGPLAYER_H

#include <QObject>

class logPlayer : public QObject
{
    Q_OBJECT
public:
    explicit logPlayer(QString address, QObject *parent = 0);
    virtual void playLog() = 0;
    virtual bool loadLog() = 0;
    virtual bool saveLog() = 0;
   // virtual void recordLog() = 0;

protected:
    int counter;
    QString address;

signals:

private slots:

};

#endif // LOGPLAYER_H
