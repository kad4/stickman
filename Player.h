#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
Player::Direction Player::playerDirection = Right;
Player::State Player::playerState = Standing;
Player::State Player::previousState = Standing;
Player::State Player::nextState = Standing;

int Player::currentFrameNumber = 1;
int Player::maxFrameNumber = 4;
int Player::pausedFrameCount = 0;

int Player::directionSign = 1;

float Player::height = 0;
float Player::position = 0;
float Player::playerScore = 0;
float Player::playerHealth = 100;

bool Player::bottomWall = false;
bool Player::leftWall = false;
bool Player::rightWall = false;
bool Player::isMovable = true;
bool Player::isJumpable = true;
bool Player::fallPending = true;
#endif // PLAYER_H_INCLUDED
