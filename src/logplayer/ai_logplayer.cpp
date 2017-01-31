#include "ai_logplayer.h"

AI_logPlayer::AI_logPlayer(QObject *parent) :
    logPlayer(parent)
{
    qDebug() <<"AI log player Initilization...";

    this->interval = AI_TIMER;
}

void AI_logPlayer::playLog()
{
    if( frameNumber < chunks.size() )
    {
        current_chunk = chunks.at(frameNumber++);
        QTimer::singleShot(15, this, SLOT(timerShot()));
        emit dataReady();
    }
}

bool AI_logPlayer::loadLog()
{

}

bool AI_logPlayer::loadLog(SSL_log logs)
{
    chunks.clear();
    this->frameNumber = 0;
    for(int i = 0; i < logs.chunks().size(); i++ )
    {
        chunks.append(logs.chunks(i));
    }
}

SSL_log AI_logPlayer::saveLog()
{
    SSL_log logs;
    logs.set_numberofchunks(this->counter);
    logs.set_timerinterval(AI_TIMER);

    for(int i = 0; i < chunks.size(); i++)
    {
        log_chunk *chunk = logs.add_chunks();
        chunk->CopyFrom(chunks.at(i));
    }

    return logs;
}

void AI_logPlayer::recordLog(WorldModel *wm, QList<RobotCommand> RCs)
{
    log_chunk data_chunk;

    data_chunk.set_chunk_number(this->counter++);

    Ball_message* ball(data_chunk.mutable_ball());
    ball->set_isvalid(wm->ball.isValid);
    position_message* ball_pos(ball->mutable_position());
    ball_pos->set_x(wm->ball.pos.loc.x);
    ball_pos->set_y(wm->ball.pos.loc.y);
    ball_pos->set_dir(wm->ball.pos.dir);
    position_message* ball_vel(ball->mutable_velocity());
    ball_vel->set_x(wm->ball.vel.loc.x);
    ball_vel->set_y(wm->ball.vel.loc.y);
    ball_vel->set_dir(wm->ball.vel.dir);

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

        position_message* robo_pos(our->mutable_position());
        robo_pos->set_x(wm->ourRobot[i].pos.loc.x);
        robo_pos->set_y(wm->ourRobot[i].pos.loc.y);
        robo_pos->set_dir(wm->ourRobot[i].pos.dir);

        position_message* robo_vel(our->mutable_velocity());
        robo_vel->set_x(wm->ourRobot[i].vel.loc.x);
        robo_vel->set_y(wm->ourRobot[i].vel.loc.y);
        robo_vel->set_dir(wm->ourRobot[i].vel.dir);

        //        RobotCommand_message rc = our->rc();
        //        position_message fin_pos = rc.fin_pos();
        //        fin_pos.set_x(wm->ourRobot[i].);
    }

    for(int i = 0; i < PLAYERS_MAX_NUM; i++ )
    {
        Robot_message *opp = data_chunk.add_opps();
        opp->set_isvalid(wm->oppRobot[i].isValid);

        position_message* robo_pos(opp->mutable_position());
        robo_pos->set_x(wm->oppRobot[i].pos.loc.x);
        robo_pos->set_y(wm->oppRobot[i].pos.loc.y);
        robo_pos->set_dir(wm->oppRobot[i].pos.dir);

        position_message* robo_vel(opp->mutable_velocity());
        robo_vel->set_x(wm->oppRobot[i].vel.loc.x);
        robo_vel->set_y(wm->oppRobot[i].vel.loc.y);
        robo_vel->set_dir(wm->oppRobot[i].vel.dir);
    }

    chunks.append(data_chunk);
}

void AI_logPlayer::pauseLog()
{
    pauseShot();
}

WorldModel *AI_logPlayer::returnCurrentPacket()
{
    WorldModel *wm = new WorldModel(new OutputBuffer());

    wm->ball.isValid = current_chunk.ball().isvalid();
    wm->ball.pos.loc.x = current_chunk.ball().position().x();
    wm->ball.pos.loc.y = current_chunk.ball().position().y();
    wm->ball.pos.dir = current_chunk.ball().position().dir();
    wm->ball.vel.loc.x = current_chunk.ball().velocity().x();
    wm->ball.vel.loc.y = current_chunk.ball().velocity().y();
    wm->ball.vel.dir = current_chunk.ball().velocity().dir();

    for(int i = 0; i < current_chunk.ours().size(); i++)
    {
        wm->ourRobot[i].isValid = current_chunk.ours(i).isvalid();
        wm->ourRobot[i].Role = returnAgentRole(current_chunk.ours(i).role());
        wm->ourRobot[i].Status = returnAgentStatus(current_chunk.ours(i).status());
        wm->ourRobot[i].Region = returnAgentRegion(current_chunk.ours(i).region());

        wm->ourRobot[i].pos.loc.x = current_chunk.ours(i).position().x();
        wm->ourRobot[i].pos.loc.y = current_chunk.ours(i).position().y();
        wm->ourRobot[i].pos.dir = current_chunk.ours(i).position().dir();

        wm->ourRobot[i].vel.loc.x = current_chunk.ours(i).velocity().x();
        wm->ourRobot[i].vel.loc.y = current_chunk.ours(i).velocity().y();
        wm->ourRobot[i].vel.dir = current_chunk.ours(i).velocity().dir();
    }

    for(int i = 0; i < current_chunk.opps().size(); i++)
    {
        wm->oppRobot[i].isValid = current_chunk.opps(i).isvalid();

        wm->oppRobot[i].pos.loc.x = current_chunk.opps(i).position().x();
        wm->oppRobot[i].pos.loc.y = current_chunk.opps(i).position().y();
        wm->oppRobot[i].pos.dir = current_chunk.opps(i).position().dir();

        wm->oppRobot[i].vel.loc.x = current_chunk.opps(i).velocity().x();
        wm->oppRobot[i].vel.loc.y = current_chunk.opps(i).velocity().y();
        wm->oppRobot[i].vel.dir = current_chunk.opps(i).velocity().dir();
    }

    return wm;
}

int AI_logPlayer::getLength()
{
    if( !chunks.isEmpty() )
        return chunks.size()*15;

    return 0;
}

void AI_logPlayer::setFrameNumber(int msec)
{
    int foundIndex = msec / interval;

    if( foundIndex >= 0)
    {
        this->current_chunk = chunks.at(foundIndex - 1);
        this->frameNumber = foundIndex;
        timerShot();
    }
}

Robot_message_AgentStatus AI_logPlayer::returnProtoStatus(AgentStatus status)
{
    switch (status)
    {
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
        return Robot_message_AgentStatus_Idle;
        break;
    }
}

AgentStatus AI_logPlayer::returnAgentStatus(Robot_message_AgentStatus status)
{
    switch (status)
    {
    case Robot_message_AgentStatus_Passing:
        return AgentStatus::Passing;
        break;
    case Robot_message_AgentStatus_Kicking:
        return AgentStatus::Kicking;
        break;
    case Robot_message_AgentStatus_Chiping:
        return AgentStatus::Chiping;
        break;
    case Robot_message_AgentStatus_FollowingBall:
        return AgentStatus::FollowingBall;
        break;
    case Robot_message_AgentStatus_BlockingBall:
        return AgentStatus::BlockingBall;
        break;
    case Robot_message_AgentStatus_BlockingRobot:
        return AgentStatus::BlockingRobot;
        break;
    case Robot_message_AgentStatus_RecievingPass:
        return AgentStatus::RecievingPass;
        break;
    default:
        return AgentStatus::Idle;
        break;
    }
}

Robot_message_AgentRole AI_logPlayer::returnProtoRole(AgentRole role)
{
    switch (role)
    {
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
        return Robot_message_AgentRole_NoRole;
        break;
    }
}

AgentRole AI_logPlayer::returnAgentRole(Robot_message_AgentRole role)
{
    switch (role)
    {
    case Robot_message_AgentRole_ArcMid:
        return AgentRole::ArcMid;
        break;
    case Robot_message_AgentRole_ArcLeft:
        return AgentRole::ArcLeft;
        break;
    case Robot_message_AgentRole_ArcRight:
        return AgentRole::ArcRight;
        break;
    case Robot_message_AgentRole_FixedPositionLeft:
        return AgentRole::FixedPositionLeft;
        break;
    case Robot_message_AgentRole_FixedPositionRight:
        return AgentRole::FixedPositionRight;
        break;
    case Robot_message_AgentRole_FixedPositionMid:
        return AgentRole::FixedPositionMid;
        break;
    case Robot_message_AgentRole_AttackerLeft:
        return AgentRole::AttackerLeft;
        break;
    case Robot_message_AgentRole_AttackerRight:
        return AgentRole::AttackerRight;
        break;
    case Robot_message_AgentRole_AttackerMid:
        return AgentRole::AttackerMid;
        break;
    case Robot_message_AgentRole_Blocker:
        return AgentRole::Blocker;
        break;
    case Robot_message_AgentRole_DefenderLeft:
        return AgentRole::DefenderLeft;
        break;
    case Robot_message_AgentRole_DefenderRight:
        return AgentRole::DefenderRight;
        break;
    case Robot_message_AgentRole_DefenderMid:
        return AgentRole::DefenderMid;
        break;
    case Robot_message_AgentRole_Golie:
        return AgentRole::Golie;
        break;
    default:
        return AgentRole::NoRole;
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
        return Robot_message_AgentRegion_NoRegion;
        break;
    }
}

AgentRegion AI_logPlayer::returnAgentRegion(Robot_message_AgentRegion region)
{
    switch (region)
    {
    case Robot_message_AgentRegion_Left:
        return AgentRegion::Left;
        break;
    case Robot_message_AgentRegion_Center:
        return AgentRegion::Center;
        break;
    case Robot_message_AgentRegion_Right:
        return AgentRegion::Right;
        break;
    default:
        return AgentRegion::NoRegion;
        break;
    }
}

void AI_logPlayer::timerShot()
{
    if( frameNumber < chunks.size() )
    {
        current_chunk = chunks.at(frameNumber++);
        //qDebug()<<"playPermisssion:"<<playPermisssion;
        if( playPermisssion )
            QTimer::singleShot(15, this, SLOT(timerShot()));
        emit dataReady();
    }
}

void AI_logPlayer::pauseShot()
{
    if( logIsPaused )
        QTimer::singleShot(15, this, SLOT(pauseShot()));
    emit dataReady();
}

