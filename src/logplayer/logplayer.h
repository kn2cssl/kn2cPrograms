#ifndef LOGPLAYER_H
#define LOGPLAYER_H

#include <QObject>
#include <QDebug>
#include <QTime>
#include <QTimer>

class logPlayer : public QObject
{
    Q_OBJECT
public:
    explicit logPlayer(QObject *parent = 0);

    virtual void setFrameNumber(int msec) = 0;
    virtual int getLength() = 0;

    void setPlayPermission(bool input);
    void setPauseStatus(bool input);
    void restartCounters();

protected:
    int counter;
    bool playPermisssion;
    bool logIsPaused;
    int frameNumber;

signals:

public slots:
    virtual void playLog() = 0;
    virtual void pauseLog() = 0;

private slots:

};

#endif // LOGPLAYER_H
