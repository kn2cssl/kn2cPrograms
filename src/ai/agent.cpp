#include "agent.h"
#include "worldmodel.h"

Agent::Agent() :
    Robot()
{
    wm = 0;
    id = -1;
}

void Agent::setID(int id)
{
    this->id = id;
    nav.setID(id);
}

void Agent::setWorldModel(WorldModel *wm)
{
    this->wm = wm;
    nav.setWorldModel(wm);
}

void Agent::setOutputBuffer(OutputBuffer *outputBuffer)
{
    this->outputBuffer = outputBuffer;
}

void Agent::SendCommand(RobotCommand rc)
{
    if(!wm->ourRobot[id].isValid) return;

    ControllerInput ci = nav.calc(rc);
    ControllerResult co = ctrl.calc(ci);

    // Real Game Packet
    RobotData reRD;
    reRD.RID    = id;
    reRD.Vx_sp  = co.rs.VX * 1000;
    reRD.Vy_sp  = co.rs.VY * 1000;
    reRD.Wr_sp  = co.rs.VW * 1000;
    reRD.Vx     = wm->ourRobot[id].vel.loc.x * 1000;
    reRD.Vy     = wm->ourRobot[id].vel.loc.y * 1000;
    reRD.Wr     = wm->ourRobot[id].vel.dir * 100;
    reRD.alpha  = wm->ourRobot[id].pos.dir * 1000;
    reRD.KICK   = (quint8) rc.kickspeedx;
    reRD.CHIP   = (quint8) rc.kickspeedz;
    reRD.SPIN   = 128;//for test
    outputBuffer->wpck.AddRobot(reRD);

    // grSim Packet
    grRobotData grRD;

    grRD.rid    = id;
    grRD.velx   = co.rs.VX;
    grRD.vely   = co.rs.VY;
    grRD.velw   = co.rs.VW;
    grRD.wheel1 = co.msS.M0;
    grRD.wheel2 = co.msS.M1;
    grRD.wheel3 = co.msS.M2;
    grRD.wheel4 = co.msS.M3;
    grRD.kickspeedx = rc.kickspeedx;
    grRD.kickspeedz = rc.kickspeedz;
    grRD.spinner = 0;
    if( packetIsValid(grRD) )
        outputBuffer->grpck.AddRobot(grRD);
}

void Agent::Halt()
{
    // Real Game Packet
    RobotData reRD;
    reRD.RID = id;
    reRD.M0 = 0;
    reRD.M1 = 0;
    reRD.M2 = 0;
    reRD.M3 = 0;
    reRD.KCK = 0;
    reRD.CHP = 0;
    outputBuffer->wpck.AddRobot(reRD);
    // grSim Packet
    grRobotData grRD;
    grRD.rid=id;
    grRD.velx = 0;
    grRD.vely = 0;
    grRD.velw = 0;
    grRD.wheel1=0;
    grRD.wheel2=0;
    grRD.wheel3=0;
    grRD.wheel4=0;
    grRD.kickspeedx=0;
    grRD.kickspeedz=0;
    grRD.spinner=0;
    outputBuffer->grpck.AddRobot(grRD);
}

bool Agent::packetIsValid(grRobotData grRD)
{
    if( !isnan(grRD.velx) && !isnan(grRD.vely) && !isnan(grRD.velw) &&
            !isnan(grRD.wheel1) && !isnan(grRD.wheel2) && !isnan(grRD.wheel3) && !isnan(grRD.wheel4) )
        return  true;

    return false;
}
