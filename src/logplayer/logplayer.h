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
    virtual void pauseLog() = 0;
   // virtual void recordLog() = 0;
    virtual void setFrameNumber(int msec) = 0;
    virtual int getLength() = 0;
    void setPlayPermission(bool input);
    void setPauseStatus(bool input);

protected:
    int counter;
    QString address;
    bool playPermisssion;
    bool logIsPaused;

signals:

private slots:

};

#endif // LOGPLAYER_H
