#include "sslvision_single.h"

SSLVision_Single::SSLVision_Single(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent) :
    SSLVision(ip,port,color,side,camera,wm,parent),
    _fpscam0(parent),
    _fpscam1(parent)
{
}

int SSLVision_Single::getFPS(int c)
{
    if(c == 0) return _fpscam0.FPS();
    if(c == 1) return _fpscam1.FPS();
    return 0;
}

void SSLVision_Single::parse(SSL_DetectionFrame &pck)
{
    // update camera fps
    int cid = pck.camera_id();
    if(cid == 0) _fpscam0.Pulse();
    if(cid == 1) _fpscam1.Pulse();

    switch(_camera)
    {
    case CAMERA_ALL:
        break;
    case CAMERA_0:
        if (cid==1) return;
        break;
    case CAMERA_1:
        if (cid==0) return;
        break;
    case CAMERA_NONE:
    default:
        return;
    }

    // update vision frame
    //_vframe[cid].frame_number =  pck.frame_number();

    vector<Position> pt;

    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    double time = _time.elapsed(); //pck.t_capture();

    // insert balls
    int max_balls=min(VOBJ_MAX_NUM, pck.balls_size());
    for(int i=0; i<max_balls; ++i)
    {
        auto b = pck.balls(i);
        if(b.has_confidence() && b.has_x() && b.has_y())
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_SINGLE_MAX_X && fabs(b.y()) < FIELD_SINGLE_MAX_Y)
            {
                Position tp;
                tp.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
                pt.push_back(tp);
            }
    }
    _wm->ball.seenAt(pt, time, cid);

    if(_color == COLOR_BLUE)
    {
        APPEND_ROBOTS_SINGLE(blue, our);
        APPEND_ROBOTS_SINGLE(yellow, opp);
    }
    else // _color == COLOR_YELLOW
    {
        APPEND_ROBOTS_SINGLE(yellow, our);
        APPEND_ROBOTS_SINGLE(blue, opp);
    }
}

void SSLVision_Single::parseLog(SSL_DetectionFrame &pck)
{
    // update camera fps
    int cid = pck.camera_id();

    switch(_camera)
    {
    case CAMERA_ALL:
        break;
    case CAMERA_0:
        if (cid==1) return;
        break;
    case CAMERA_1:
        if (cid==0) return;
        break;
    case CAMERA_NONE:
    default:
        return;
    }

    // update vision frame
    //_vframe[cid].frame_number =  pck.frame_number();

    vector<Position> pt;

    // Team side Coefficient
    float ourSide = (_side == SIDE_RIGHT)? -1.0f : 1.0f;
    double time = _time.elapsed(); //pck.t_capture();

    // insert balls
    int max_balls=min(VOBJ_MAX_NUM, pck.balls_size());
    for(int i=0; i<max_balls; ++i)
    {
        auto b = pck.balls(i);
        if(b.has_confidence() && b.has_x() && b.has_y())
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_SINGLE_MAX_X && fabs(b.y()) < FIELD_SINGLE_MAX_Y)
            {
                Position tp;
                tp.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
                pt.push_back(tp);
            }
    }
    _wm->ball.seenAt(pt, time, cid);

    if(_color == COLOR_BLUE)
    {
        APPEND_ROBOTS_SINGLE(blue, our);
        APPEND_ROBOTS_SINGLE(yellow, opp);
    }
    else // _color == COLOR_YELLOW
    {
        APPEND_ROBOTS_SINGLE(yellow, our);
        APPEND_ROBOTS_SINGLE(blue, opp);
    }
}
