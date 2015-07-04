#include "sslvision_double.h"

SSLVision_Double::SSLVision_Double(QString ip, int port, TeamColorType color, TeamSideType side, CameraConfigType camera, WorldModel *wm, QObject *parent) :
    SSLVision(ip,port,color,side,camera,wm,parent),
    _fpscam0(parent),
    _fpscam1(parent),
    _fpscam2(parent),
    _fpscam3(parent)
{
}

int SSLVision_Double::getFPS(int c)
{
    if(c == 0) return _fpscam0.FPS();
    if(c == 1) return _fpscam1.FPS();
    if(c == 2) return _fpscam2.FPS();
    if(c == 3) return _fpscam3.FPS();
    return 0;
}

void SSLVision_Double::parse(SSL_DetectionFrame &pck)
{

    // update camera fps
    int cid = pck.camera_id();
    if(cid == 0) _fpscam0.Pulse();
    if(cid == 1) _fpscam1.Pulse();
    if(cid == 2) _fpscam2.Pulse();
    if(cid == 3) _fpscam3.Pulse();

    switch(_camera)
    {
    case CAMERA_ALL:
        break;
    case CAMERA_0:
        if (cid==1 || cid==2 || cid==3) return;
        break;
    case CAMERA_1:
        if (cid==0 || cid==2 || cid==3) return;
        break;
    case CAMERA_2:
        if (cid==0 || cid==1 || cid==3) return;
        break;
    case CAMERA_3:
        if (cid==0 || cid==1 || cid==2) return;
        break;
    case CAMERA_BOTH_L:
        if (cid==2 || cid==3) return;
        break;
    case CAMERA_BOTH_R:
        if (cid==0 || cid==1) return;
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
            if(b.confidence() > MIN_CONF && fabs(b.x()) < FIELD_DOUBLE_MAX_X && fabs(b.y()) < FIELD_DOUBLE_MAX_Y)
//            if(b.confidence() > MIN_CONF && (fabs(b.x()) < FIELD_MAX_X && fabs(b.x()) > 600) && fabs(b.y()) < FIELD_MAX_Y)
            {
                Position tp;
                tp.loc = Vector2D(b.x()*ourSide, b.y()*ourSide);
                pt.push_back(tp);
            }
    }
    _wm->ball.seenAt(pt, time, cid);

    if(_color == COLOR_BLUE)
    {
        APPEND_ROBOTS_DOUBLE(blue, our);
        APPEND_ROBOTS_DOUBLE(yellow, opp);
    }
    else // _color == COLOR_YELLOW
    {
        APPEND_ROBOTS_DOUBLE(yellow, our);
        APPEND_ROBOTS_DOUBLE(blue, opp);
    }

}
