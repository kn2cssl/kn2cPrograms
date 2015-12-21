#include "ai_logplayer.h"

AI_logPlayer::AI_logPlayer(WorldModel *worldmodel, QString address, QObject *parent) :
    logPlayer(address,parent),
    wm(worldmodel)
{
    qDebug() <<"AI log player Initilization...";
    qDebug()<<"Log Address: "<<address;
}

void AI_logPlayer::playLog()
{
    for( int i=0; i < chunks.size(); i++)
    {
        log_chunk chunk = chunks.at(i);
        qDebug()<<"Ball is valid: "<<chunk.ball().isvalid();
        Ball_message ball = chunk.ball();
        qDebug()<<"ball pos: "<<ball.position().x()<<" , "<<ball.position().y()<<" , "<<ball.position().dir();
    }
}

bool AI_logPlayer::loadLog()
{

}

bool AI_logPlayer::saveLog()
{

}

void AI_logPlayer::recordLog()
{
    log_chunk data_chunk;

    data_chunk.set_chunk_number(this->counter);

    Ball_message ball = data_chunk.ball();
    ball.set_isvalid(wm->ball.isValid);
    position_message ball_pos = ball.position();
    ball_pos.set_x(wm->ball.pos.loc.x);
    ball_pos.set_y(wm->ball.pos.loc.y);
    ball_pos.set_dir(wm->ball.pos.dir);
    position_message ball_vel = ball.velocity();
    ball_vel.set_x(wm->ball.vel.loc.x);
    ball_vel.set_y(wm->ball.vel.loc.y);
    ball_vel.set_dir(wm->ball.vel.dir);

    for(int i = 0; i < PLAYERS_MAX_NUM; i++ )
    {
        Robot_message *our = data_chunk.add_ours();
        our->set_isvalid(wm->ourRobot[i].isValid);
        Robot_message_AgentRole role = returnProtoRole(wm->ourRobot[i].Role);
        our->set_role(role);
        Robot_message_AgentStatus status = returnProtoStatus(wm->ourRobot[i].Status);
        our->set_status(status);
        Robot_message_AgentRegion region = returnProtoRegion(wm->ourRobot[i].Region);
        our->set_region(region);
        position_message robo_pos = our->position();
        robo_pos.set_x(wm->ourRobot[i].pos.loc.x);
        robo_pos.set_y(wm->ourRobot[i].pos.loc.y);
        robo_pos.set_dir(wm->ourRobot[i].pos.dir);
        position_message robo_vel = our->velocity();
        robo_vel.set_x(wm->ourRobot[i].vel.loc.x);
        robo_vel.set_y(wm->ourRobot[i].vel.loc.y);
        robo_vel.set_dir(wm->ourRobot[i].vel.dir);
        //        RobotCommand_message rc = our->rc();
        //        position_message fin_pos = rc.fin_pos();
        //        fin_pos.set_x(wm->ourRobot[i].);
    }

    chunks.append(data_chunk);
}

Robot_message_AgentStatus AI_logPlayer::returnProtoStatus(AgentStatus status)
{
    switch (status)
    {
    case AgentStatus::Idle:
        return Robot_message_AgentStatus_Idle;
        break;
    case AgentStatus::Passing:
        return Robot_message_AgentStatus_Passing;
        break;
    case AgentStatus::Kicking:
        return Robot_message_AgentStatus_Kicking;
        break;
    case AgentStatus::Chiping:
        return Robot_message_AgentStatus_Chiping;
        break;
    case AgentStatus::FollowingBall:
        return Robot_message_AgentStatus_FollowingBall;
        break;
    case AgentStatus::BlockingBall:
        return Robot_message_AgentStatus_BlockingBall;
        break;
    case AgentStatus::BlockingRobot:
        return Robot_message_AgentStatus_BlockingRobot;
        break;
    case AgentStatus::RecievingPass:
        return Robot_message_AgentStatus_RecievingPass;
        break;
    default:
        break;
    }
}

Robot_message_AgentRole AI_logPlayer::returnProtoRole(AgentRole role)
{
    switch (role)
    {
    case AgentRole::NoRole:
        return Robot_message_AgentRole_NoRole;
        break;
    case AgentRole::ArcMid:
        return Robot_message_AgentRole_ArcMid;
        break;
    case AgentRole::ArcLeft:
        return Robot_message_AgentRole_ArcLeft;
        break;
    case AgentRole::ArcRight:
        return Robot_message_AgentRole_ArcRight;
        break;
    case AgentRole::FixedPositionLeft:
        return Robot_message_AgentRole_FixedPositionLeft;
        break;
    case AgentRole::FixedPositionRight:
        return Robot_message_AgentRole_FixedPositionRight;
        break;
    case AgentRole::FixedPositionMid:
        return Robot_message_AgentRole_FixedPositionMid;
        break;
    case AgentRole::AttackerLeft:
        return Robot_message_AgentRole_AttackerLeft;
        break;
    case AgentRole::AttackerRight:
        return Robot_message_AgentRole_AttackerRight;
        break;
    case AgentRole::AttackerMid:
        return Robot_message_AgentRole_AttackerMid;
        break;
    case AgentRole::Blocker:
        return Robot_message_AgentRole_Blocker;
        break;
    case AgentRole::DefenderLeft:
        return Robot_message_AgentRole_DefenderLeft;
        break;
    case AgentRole::DefenderRight:
        return Robot_message_AgentRole_DefenderRight;
        break;
    case AgentRole::DefenderMid:
        return Robot_message_AgentRole_DefenderMid;
        break;
    case AgentRole::Golie:
        return Robot_message_AgentRole_Golie;
        break;
    default:
        break;
    }
}

Robot_message_AgentRegion AI_logPlayer::returnProtoRegion(AgentRegion region)
{
    switch (region)
    {
    case AgentRegion::Left:
        return Robot_message_AgentRegion_Left;
        break;
    case AgentRegion::Center:
        return Robot_message_AgentRegion_Center;
        break;
    case AgentRegion::Right:
        return Robot_message_AgentRegion_Right;
        break;
    default:
        break;
    }
}

