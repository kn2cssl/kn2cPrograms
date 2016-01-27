#ifndef AI_H
#define AI_H

#include <QtCore>
#include <QObject>
#include "constants.h"
#include "outputbuffer.h"
#include "play.h"
#include "fpscounter.h"
#include <QUdpSocket>
#include "logplayer/ai_logplayer.h"

class AI : public QObject
{
    Q_OBJECT
public:
    explicit AI(WorldModel* worldmodel, QString field_size, OutputBuffer* outputbuffer, QObject *parent = 0);
    FPSCounter fps;
    Play* getCurrentPlay();
    Tactic* getCurrentTactic(int i);
    void startRecording();
    SSL_log stopRecording();
    void startPlaying();
    void stopPlaying();
    void pausePlaying();
    void loadPlaying(SSL_log logs);
    int logLength();
    void setLogFrame(int msec);

public slots:
    void Start();
    void Stop();

private:
    WorldModel *wm;
    OutputBuffer *outputbuffer;
    QTimer timer;
    Play *current_play;
    Tactic *current_tactic[PLAYERS_MAX_NUM];
    AI_logPlayer *logplayer;
    QUdpSocket *udp;
    QHostAddress ip;
    int firstWait;
    bool recordPermission;

private slots:
    void timer_timeout();
    void updateWorldModel();

private:
    QList<Play*> plays;

};

#endif // AI_H
