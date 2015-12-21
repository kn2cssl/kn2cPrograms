#ifndef SSLVISION_DOUBLE_H
#define SSLVISION_DOUBLE_H

#include <QObject>
#include <QTime>

#include "proto/sslvision/messages_robocup_ssl_wrapper.pb.h"
#include "base.h"
#include "constants.h"
#include "sslvision.h"
#include "geom.h"
#include "util.h"
#include "worldmodel.h"

class SSLVision_Double : public SSLVision
{
    Q_OBJECT

public:
    explicit SSLVision_Double(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent = 0);
    virtual int getFPS(int c);

private:
    FPSCounter _fpscam0;
    FPSCounter _fpscam1;
    FPSCounter _fpscam2;
    FPSCounter _fpscam3;

    virtual void parse(SSL_DetectionFrame &pck);

};


//*180.0f/M_PI+(1.0-ourSide)*90.0f,rid));

#define APPEND_ROBOTS_DOUBLE(__COLOR__,__TEAM__) \
for (int i=0; i<pck.robots_##__COLOR__##_size(); ++i) \
{ \
    pt.clear(); \
    int rid = pck.robots_##__COLOR__(i).robot_id(); \
    if ((pck.robots_##__COLOR__(i).has_orientation())&&(pck.robots_##__COLOR__(i).has_confidence())&&(pck.robots_##__COLOR__(i).confidence()>MIN_CONF)&&(fabs(pck.robots_##__COLOR__(i).x())<FIELD_DOUBLE_MAX_X /*&& fabs(pck.robots_##__COLOR__(i).x())>600*/)&&(fabs(pck.robots_##__COLOR__(i).y())<FIELD_DOUBLE_MAX_Y)) \
    { \
        Position tp; \
        tp.loc = Vector2D(pck.robots_##__COLOR__(i).x()*ourSide, pck.robots_##__COLOR__(i).y()*ourSide); \
        tp.dir = pck.robots_##__COLOR__(i).orientation()+(1.0-ourSide)*M_PI_2; \
        if(tp.dir>M_PI) tp.dir -= M_2PI; \
        pt.push_back(tp); \
        _wm->__TEAM__##Robot[rid].seenAt(pt, time, cid); \
    } \
}


#endif // SSLVISION_H
