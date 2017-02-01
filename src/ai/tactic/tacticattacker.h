#ifndef TACTICATTACKER_H
#define TACTICATTACKER_H

#include "tactic.h"
#include "geom2/shape2d.h"

#define SECURE_DIST 600

class TacticAttacker : public Tactic
{
    Q_OBJECT
public:
    explicit TacticAttacker(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    RobotCommand goBehindBall();
    RobotCommand KickTheBallIndirect();
    RobotCommand KickTheBallDirect();
    RobotCommand StartTheGame();

    RobotCommand ChipTheBallIndirect();

    int findBestPlayerForPass();
    void isKicker();
    void isChiper();
    void isKicker(int recieverID);
    void isKicker(Vector2D pos);
    void isChiper(Vector2D pos);
    void setGameOnPositions(Position pos);
    void setGameOnPositions(Vector2D pos);
    void setIdlePosition(Position pos);
    void setIdlePosition(Vector2D pos);

    void youHavePermissionForKick(int index);
    void youDontHavePermissionForKick();

    void setFreeKickType(kickType type);

    void setKickerID(int id);

    bool everyOneInTheirPos;
    void setUseNav(bool input);
    bool getUseNav();
private:
    bool isFree(int index);

    Vector2D receiverPos;
    bool findReciever;
    Position idlePosition;
    bool pastMidPoint; // FreeKick
    kickType freeKickType;
    double maxDistance;

    SkillKick* sKick;
    SkillOneTouch* sOneTouch;

    bool holdKickPos;
    Position kickPos;
    int kickerID;
    bool UseNav=true;
protected:
    bool canKick;
};

#endif // TACTICATTACKER_H
