#include "class.h"
#include "Player.h"          //Contains the static variables declaration

void Player::initiatePlayer()
{
    if (_image.LoadFromFile ("data/Images/Player/SpriteSheet/SpriteSheet.png"))
    {
        _isLoaded = true;
    }
    else
    {
        _isLoaded = false;
    }
    playerDirection = Right;
    playerState = Standing;
    previousState = Standing;
    nextState = Standing;
    currentFrameNumber = 1;
    xVelocity = 0;
    height = 0;
    playerScore = 0;
    playerHealth = 100;
    position = 0;

    isMovable = true;
    isJumpable = true;
    _sprite.SetImage(_image);

    SetPosition(.26 * SCREEN_WIDTH,0); //Player's starting position
}

void Player::Load(bool isFlipped, int x, int y)
{
    y *= 120;
    x *= 60;
    _sprite.FlipX(isFlipped);
    SetSubRect(x, y, x + 60, y + 120);
    SetCenter(30 , 102);
}

void Player::frameHandler(void)
{
    {
        //Write here if needed to pause frame
        if (playerState == Climbing and !Game::_button[Game::Key_Up] and !Game::_button[Game::Key_Down])
        {
            if (currentFrameNumber > 1) currentFrameNumber--;
        }
        if (playerState == Standing and pausedFrameCount > 0)
        {
            pausedFrameCount = 0;
        }
        if (playerState == RTurning and currentFrameNumber == 2 and xVelocity != 0)
        {
            currentFrameNumber--;
        }
        if (playerState == Falling and currentFrameNumber == 2 and yVelocity > 0)
        {
            currentFrameNumber--;
            if (yVelocity > 30)
            {
                fallPending = true;
            }
        }
        if (playerState == DFalling and currentFrameNumber == 7 and pausedFrameCount < 30)
        {
            currentFrameNumber--;
            pausedFrameCount++;
        }
        else if (playerState == DFalling and pausedFrameCount >= 30)
        {
            pausedFrameCount = 0;
        }
        if (playerState == Jumping and previousState == Running and currentFrameNumber == 7 and pausedFrameCount < 6)
        {
            currentFrameNumber--;
            pausedFrameCount++;
        }
        else if (playerState == Jumping and pausedFrameCount >= 6)
        {
            pausedFrameCount=0;
        }
        if (playerState == Jumping and !bottomWall and currentFrameNumber == 9)
        {
            previousState = Standing;
            playerState = Falling;
            currentFrameNumber =1;
        }
        if (playerState == HitNTurning and currentFrameNumber == 3 and pausedFrameCount < 8)
        {
            currentFrameNumber--;
            pausedFrameCount++;
        }
        else if (playerState == HitNTurning and pausedFrameCount >= 8)
        {
            pausedFrameCount = 0;
        }
    }

    if (currentFrameNumber > maxFrameNumber)
    {
        if (playerState == Standing or playerState == Walking)
        {
            isMovable = true;
            currentFrameNumber = 1;
        }
        else if (playerState == Running)
        {
            currentFrameNumber = 2;
            if (Game::allKeyUp)
            {
                isMovable = true, currentFrameNumber = 1;
            }
        }
        else if (playerState == Jumping)
        {
            nextState = Standing;
            if ( currentFrameNumber > 9 and !bottomWall)
            {
                playerState = Falling;
                currentFrameNumber = 1;
            }
            else
            {
                playerState = Standing;
                currentFrameNumber = 1;
                isMovable = true;
            }
            previousState = Jumping;
        }
        else if (playerState == ClimbingUp)
        {
            playerState = Standing;
            previousState = ClimbingUp;
            currentFrameNumber = 1;
            _sprite.SetPosition(_sprite.GetPosition().x - (directionSign * 10), _sprite.GetPosition().y);
            isMovable = true;
        }
        else if (playerState == ClimbingDown)
        {
            playerState = Climbing;
            previousState = ClimbingDown;
            currentFrameNumber = 1;
            _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y);
            isMovable = true;
        }
        else if (playerState == Falling)
        {
            playerState = Standing;
            previousState = Falling;
            nextState = Standing;
            currentFrameNumber = 1;
            isMovable = true;
            fallPending = false;
        }
        else if (playerState == RollingDown)
        {
            if (previousState != Running)
            {
                currentFrameNumber--;
            }
            else
            {
                playerState = Rolling;
                nextState = Standing;
                previousState = RollingDown;
                currentFrameNumber = 1;
            }
        }
        else if (playerState == RollingUp)
        {
            currentFrameNumber = 1;
            previousState = RollingUp;
            playerState = Standing;
            isMovable = true;
        }
        else if (playerState == Turning)
        {
            currentFrameNumber = 1;
            previousState = Turning;
            playerState = Standing;
            isMovable = true;
            if (playerDirection == Left)
            {
                playerDirection = Right;
            }
            else
            {
                playerDirection = Left;
            }
        }
        else if (playerState == RTurning)
        {
            currentFrameNumber = 1;
            previousState = RTurning;
            playerState = Standing;
            if (playerDirection == Left)
            {
                playerDirection = Right;
            }
            else
            {
                playerDirection = Left;
            }
        }
        else if (playerState == HitNTurning)
        {
            currentFrameNumber = 1;
            for (int i=0; i<4; i++)
            {
                Game::_button[i]=0;
            }
            if (previousState == Running)
            {
                playerState = Walking;
            }
            else
            {
                playerState = Standing;
            }
            previousState = HitNTurning;
            nextState = Standing;
            if (playerDirection == Left)
            {
                playerDirection = Right;
            }
            else
            {
                playerDirection = Left;
            }
        }
        else if (playerState == Climbing)
        {
            currentFrameNumber = 1;
        }
        else if (playerState == Rolling)
        {
            currentFrameNumber = 4;
            playerState = RollingDown;
            previousState = Rolling;
        }
        else if (playerState == JumpingDown)
        {
            if (bottomWall)
            {
                playerState = Running;
            }
            else
            {
                playerState = Falling;
            }
            previousState = JumpingDown;
            nextState = Standing;
            currentFrameNumber = 1;
        }
        else if  (playerState == DFalling)
        {
            if (playerHealth != 0)
            {
                previousState = DFalling;
                playerState = GettingUp;
                nextState = Standing;
                currentFrameNumber = 1;
            }
            else
            {
                currentFrameNumber--;
            }
        }
        else if (playerState == GettingUp)
        {
            previousState = GettingUp;
            playerState = Standing;
            nextState = Standing;
            currentFrameNumber = 1;
            isMovable = true;
        }
        else if (currentFrameNumber < maxFrameNumber)
        {
            for (int i=0; i<4; i++)
                Game::_button[i] = false;
        }
    }
}

void Player::updatePlayer(Event & currentEvent)
{
    if (playerDirection == Left)
    {
        directionSign = -1;
    }
    else
    {
        directionSign = 1;
    }

    getPlayerVelocity();
    getPlayerScore();
    getPlayerHealth();

    _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y + yVelocity);


    if (playerHealth == 0 and bottomWall and playerState != DFalling)
    {
        playerState = DFalling;
    }
    if ((playerState == Jumping or playerState == Falling)
            and
            ((playerDirection == Left and leftWall)
             or
             (playerDirection == Right and rightWall)))
    {
        if (playerState == Jumping and currentFrameNumber > 5 and bottomWall)
        {
            if (Game::world1.column1[Game::world1.player_column() + 1].height - 1
                    == Game::world1.column1[Game::world1.player_column()].height)
            {
                _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y - 10);
            }
            else
            {
                _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y - 25);
            }
        }
        previousState = playerState;
        playerState = Climbing;
        currentFrameNumber = 1;
        fallPending = false;
        return;
    }

    if (playerState == Falling and yVelocity == 0)
    {
        if (fallPending)
        {
            if (previousState != JumpingDown)
            {
                playerState = DFalling;
            }
            else
            {
                playerState = Standing;
            }
            previousState = Falling;
            nextState = Standing;
            currentFrameNumber = 1;
        }
        fallPending = false;
        return;

    }
    if (yVelocity > 0 and playerState != Climbing and playerState != ClimbingDown and playerState != JumpingDown)
    {
        playerState = Falling;
        return;
    }
    if (playerState == Climbing and Game::_button[Game::Key_Up])
    {
        if (_sprite.GetPosition().y - 3 * yPadding < Game::world1.column1[Game::world1.player_column()+directionSign].yPosition)
        {
            previousState = Climbing;
            playerState = ClimbingUp;
            nextState = Standing;
            _sprite.SetPosition(_sprite.GetPosition().x + (directionSign * 10), _sprite.GetPosition().y);
            currentFrameNumber = 1;
            return;
        }
    }

    if (playerState == Standing and Game::_button[Game::Key_Down])
    {
        if ((playerDirection == Left and _sprite.GetPosition().x - 110 > Game::world1.column1[Game::world1.player_column()].xPosition)
                or
                (playerDirection == Right and _sprite.GetPosition().x - 30 < Game::world1.column1[Game::world1.player_column()].xPosition))
        {
            if (Game::world1.column1[Game::world1.player_column()].height >
                    Game::world1.column1[Game::world1.player_column() + directionSign].height)
            {
                _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y + 60);
                playerState = ClimbingDown;
                currentFrameNumber = 1;
                return;
            }
        }
    }
    if (playerState == Running and Game::_button[Game::Key_Down])
    {
        if ((playerDirection == Left and _sprite.GetPosition().x - 40 < Game::world1.column1[Game::world1.player_column()].xPosition)
                or
                (playerDirection == Right and _sprite.GetPosition().x -110 > Game::world1.column1[Game::world1.player_column()].xPosition))
        {
            if (Game::world1.column1[Game::world1.player_column()].height >
                    Game::world1.column1[Game::world1.player_column() + directionSign].height)
            {
                playerState = JumpingDown;
                currentFrameNumber = 1;
                return;
            }
        }
        else
        {
            playerState = RollingDown;
            previousState = Running;
            currentFrameNumber = 1;
            nextState = Rolling;
            return;
        }
    }


    if (nextState == Jumping)
    {
        if (playerState == Standing and ((Game::_button[Game::Key_Left] and playerDirection == Left)
                                         or
                                         (Game::_button[Game::Key_Right] and playerDirection == Right)))
        {
            previousState = Walking;
            playerState = Jumping;
            nextState = Standing;
            currentFrameNumber = 1;
            return;
        }
        else if (playerState == Walking)
        {
            previousState = Walking;
            playerState = Jumping;
            nextState = Standing;
            currentFrameNumber = 1;
            return;
        }
        else if (playerState == Standing)
        {
            previousState = playerState;
            playerState = Jumping;
            nextState = Standing;
            currentFrameNumber = 1;
            return;
        }
        else if (playerState == Running)
        {
            {
                previousState = playerState;
                playerState = Jumping;
                nextState = Standing;
                currentFrameNumber = 1;
                return;
            }
        }
    }

    if (nextState == RollingDown)
    {
        previousState = playerState;
        playerState = RollingDown;
        nextState = Standing;
        xVelocity = 0;
        currentFrameNumber = 1;
    }

    if(Game::allKeyUp and isMovable)
    {
        if (playerState != Standing)
        {
            previousState = playerState;
            playerState = Standing;
            xVelocity = 0;
            currentFrameNumber = 1;
            return;
        }
    }

    if (!Game::_button[Game::Key_Down] and playerState == RollingDown)
    {
        previousState = RollingDown;
        playerState = RollingUp;
        currentFrameNumber = 6 - currentFrameNumber;
        isMovable = false;
        return;
    }

    if ((Game::_button[Game::Key_Left] and !Game::_button[Game::Key_Right])
            or
            (Game::_button[Game::Key_Right] and !Game::_button[Game::Key_Left]))
    {
        directionMovement (Game::_button[Game::Key_Left], Game::_button[Game::Key_Right]);
        return;
    }

    if(Game::_button[Game::Key_Down])
    {
        if ((playerState == Standing or playerState == Running) and playerState!=Rolling)
        {
            nextState = RollingDown;
            return;
        }
    }


    if(Game::_button[Game::Key_Up])
    {
        if (playerState==Standing or playerState == Walking or playerState==Running)
        {
            nextState = Jumping;
            return;
        }
    }
}

void Player::directionMovement (bool _left, bool _right)
{
    Direction _front, _back;
    bool frontWall, backWall;
    if (_left and !_right)
    {
        frontWall = leftWall;
        backWall = rightWall;
        _front = Left;
        _back = Right;
    }
    else if (_right and !_left)
    {
        frontWall = rightWall;
        backWall = leftWall;
        _front = Right;
        _back = Left;
    }

    if (playerDirection == _back)
    {
        if (playerState == Standing)
        {
            playerState = Turning;
            previousState = Standing;
            currentFrameNumber = 1;
            return;
        }
        if (playerState == Running)
        {
            playerState = RTurning;
            previousState = Running;
            currentFrameNumber = 1;
            return;
        }
        if (playerState == Climbing)
        {
            if (!bottomWall)
            {
                playerState = Jumping;
                previousState = Running;
                nextState = Standing;
                _sprite.SetPosition(_sprite.GetPosition().x, _sprite.GetPosition().y + 25);
                currentFrameNumber = 7;
                pausedFrameCount = 4;
            }
            else
            {
                playerState = Standing;
                previousState = Climbing;
                currentFrameNumber = 1;
            }
            if (playerDirection == Left)
            {
                playerDirection = Right;
            }
            else
            {
                playerDirection = Left;
            }
            nextState = Standing;

        }
    }
    if (playerDirection == _front and frontWall and playerState != Climbing)
    {
        previousState = playerState;
        playerState = HitNTurning;
        currentFrameNumber = 1;
    }
    if (playerDirection == _front and !frontWall)
    {
        if (playerState == Walking)
        {
            if (Game::_button[Game::Key_Up])
            {
                playerState = Jumping;
                previousState = Walking;
                currentFrameNumber = 1;
                pausedFrameCount = 6;
                return;
            }
            else if (currentFrameNumber > 2)
            {
                previousState = Walking;
                playerState = Running;
                return;
            }
        }
        else if (playerState == Standing)
        {
            if (Game::_button[Game::Key_Up])
            {
                playerState = Jumping;
                previousState = Walking;
                currentFrameNumber = 1;
                pausedFrameCount = 6;
                return;
            }
            else
            {
                currentFrameNumber = 1;
                playerState = Walking;
                previousState = Standing;
                return;
            }
        }
        else if(playerState == Running and Game::_button[Game::Key_Up])
        {
            nextState = Jumping;
            return;
        }
        else if (playerState == RollingDown and currentFrameNumber > 4)
        {
            currentFrameNumber = 1;
            playerState = Rolling;
            previousState = RollingDown;
            nextState = RollingUp;
            return;
        }
        else if (playerState == Climbing)
        {
            if (_sprite.GetPosition().y - 3 * yPadding < Game::world1.column1[Game::world1.player_column()+directionSign].yPosition)
            {
                previousState = Climbing;
                playerState = ClimbingUp;
                nextState = Standing;
                _sprite.SetPosition(_sprite.GetPosition().x + (directionSign * 10), _sprite.GetPosition().y);
                currentFrameNumber = 1;
                return;
            }
        }
    }
}

void Player::getPlayerInstance(void)
{
    bool flip;
    switch (playerDirection)
    {
    case Left:
    {
        flip = true;
        break;
    }
    case Right:
    {
        flip = false;
        break;
    }
    default:
    {
        break;
    }
    }

    if (playerState == Standing)
    {
        maxFrameNumber = 4;
    }
    else if (playerState == Walking)
    {
        maxFrameNumber = 8;
    }
    else if (playerState == Running)
    {
        maxFrameNumber = 8;
    }
    else if (playerState == Jumping)
    {
        maxFrameNumber = 9;
    }
    else if (playerState == RollingDown)
    {
        maxFrameNumber = 4;
    }
    else if (playerState == RollingUp)
    {
        maxFrameNumber = 4;
    }
    else if (playerState == ClimbingUp)
    {
        maxFrameNumber = 7;
    }
    else if (playerState == ClimbingDown)
    {
        maxFrameNumber = 7;
    }
    else if (playerState == Falling)
    {
        maxFrameNumber = 5;
    }
    else if (playerState == Turning)
    {
        maxFrameNumber = 4;
    }
    else if (playerState == RTurning)
    {
        maxFrameNumber = 2;
    }
    else if (playerState == HitNTurning)
    {
        maxFrameNumber = 5;
    }
    else if (playerState == Climbing)
    {
        maxFrameNumber = 2;
    }
    else if (playerState == Rolling)
    {
        maxFrameNumber = 8;
    }
    else if (playerState == JumpingDown)
    {
        maxFrameNumber = 8;
    }
    else if (playerState == DFalling)
    {
        maxFrameNumber = 7;
    }
    else if (playerState == GettingUp)
    {
        maxFrameNumber = 7;
    }
    else
    {
        maxFrameNumber = 0;
    }

    isMovable = false;

    frameHandler();
    Load (flip, currentFrameNumber-1, playerState);
    currentFrameNumber++;
}

void Player::displayText(string fieldName, string fieldValue)
{
    float fontSize = 11;

    sf::String fName(fieldName, Game::debugFont, fontSize - 1);
    sf::String fValue(fieldValue, Game::debugFont, fontSize - 1);

    fName.SetPosition(0,Game::itemsDisplayed * fontSize);
    fValue.SetPosition(150, Game::itemsDisplayed * fontSize);

    fName.SetColor(sf::Color(255, 255, 255));
    fValue.SetColor(sf::Color(255,255,255));

    Game::_mainWindow.Draw(fName);
    Game::_mainWindow.Draw(fValue);

    Game::itemsDisplayed++;
}

void Player::displayText(string fieldName, Player::Direction directionValue)
{
    string fieldValue = directionToString(directionValue);

    displayText(fieldName, fieldValue);
}

void Player::displayText(string fieldName, Player::State stateValue)
{
    string fieldValue = stateToString(stateValue);

    displayText(fieldName, fieldValue);
}

void Player::displayText(string fieldName, double fieldValueNumber)
{
    string fieldValue = numberToString(fieldValueNumber);

    displayText(fieldName, fieldValue);
}

void Player::displayText(string fieldName, bool fieldBoolean)
{
    string fieldValue = booleanToString(fieldBoolean);

    displayText(fieldName, fieldValue);
}

string Player::stateToString(Player::State temp)
{
    switch (temp)
    {
    case Standing:
    {
        return "Standing";
    }
    case Walking:
    {
        return "Walking";
    }
    case Running:
    {
        return "Running";
    }
    case Jumping:
    {
        return "Jumping";
    }
    case RollingDown:
    {
        return "Rolling Down";
    }
    case Rolling:
    {
        return "Rolling";
    }
    case RollingUp:
    {
        return "Rolling Up";
    }
    case ClimbingUp:
    {
        return "Climbing Up";
    }
    case ClimbingDown:
    {
        return "Climbing Down";
    }
    case Falling:
    {
        return "Falling";
    }
    case Turning:
    {
        return "Turning";
    }
    case RTurning:
    {
        return "RTurning";
    }
    case HitNTurning:
    {
        return "HitNTurning";
    }
    case Climbing:
    {
        return "Climbing";
    }
    case JumpingDown:
    {
        return "JumpingDown";
    }
    case DFalling:
    {
        return "DFalling";
    }
    case GettingUp:
    {
        return "GettingUp";
    }
    default:
    {
        return "Undefined";
    }
    }
}

string Player::directionToString(Direction dir)
{
    switch (dir)
    {
    case Left:
    {
        return "Left";
    }
    case Right:
    {
        return "Right";
    }
    case Up:
    {
        return "Up";
    }
    case Down:
    {
        return "Down";
    }
    case DownLeft:
    {
        return "DownLeft";
    }
    case DownRight:
    {
        return "DownRight";
    }
    default:
    {
        return "Undefined";
    }
    }
}

string Player::numberToString(double num)
{
    stringstream convert;
    convert << num;
    return convert.str();
}

string Player::booleanToString(bool bl)
{
    if (bl)
    {
        return "True";
    }
    else
    {
        return "False";
    }
}

Player::Direction Player::collisionDirection()
{
    int tempWorldIndex = Game::world1.player_column();
    Column temp = Game::world1.column1[tempWorldIndex];

    float playerY = _sprite.GetPosition().y, playerX = _sprite.GetPosition().x;
    float columnY, columnX;

    bool left = false, right = false, down=false;

    columnY = temp.yPosition, columnX = temp.xPosition;

    int i;

    if (tempWorldIndex == 0)
    {
        i = 0;
    }
    else
    {
        i = -1;
    }

    getPlayerPadding();

    if (playerY + yPadding + yVelocity >= columnY)
    {
        down = true;
    }
    if (playerX >= columnX + xPaddingRight + xVelocity and Game::world1.column1[tempWorldIndex + 1].yPosition < playerY)
    {
        right = true;
    }
    else if (playerX <= columnX + xPaddingLeft + xVelocity and Game::world1.column1[tempWorldIndex + i].yPosition < playerY)
    {
        left = true;
    }

    leftWall = false;
    rightWall = false;
    bottomWall = false;

    if (left and !right)
    {
        leftWall = true;
        if (down)
        {
            bottomWall = true;
            return DownLeft;
        }
        else
        {
            return Left;
        }
    }

    if (right and !left)
    {
        rightWall = true;
        if (down)
        {
            bottomWall = true;
            return DownRight;
        }
        else
        {
            return Right;
        }
    }
    if (down)
    {
        bottomWall = true;
        return Down;
    }
    else
    {
        return Up;
    }
}

bool Player::collisionDirection(Sprite &tempSprite)
{
    float playerX = _sprite.GetPosition().x;
    float columnY, columnX;

    columnY = tempSprite.GetPosition().y, columnX = tempSprite.GetPosition().x;

    if (playerX >= columnX + xPaddingLeft + xVelocity and playerX <= columnX + xPaddingLeft + xVelocity + tempSprite.GetSize().x)
    {
        return true;
    }
    else if (playerX >= columnX - xPaddingRight - xVelocity and playerX <= columnX - xPaddingRight - xVelocity + tempSprite.GetSize().x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::getPlayerVelocity ()
{
    if (playerState != Jumping and playerState != Climbing and playerState != ClimbingUp and playerState != ClimbingDown)
    {
        if (!bottomWall)
        {
            yVelocity += 5;
        }
        else
        {
            yVelocity = 0;
            collisionDirection();
            if (!bottomWall)
            {
                yVelocity = Game::world1.column1[Game::world1.player_column()].yPosition - _sprite.GetPosition().y - yPadding;
            }
        }
    }

    xVelocity = fabs(xVelocity);

    switch (playerState)
    {
    case Walking:
    {
        xVelocity = .5;
        break;
    }
    case Running:
    {
        xVelocity = 2;
        break;
    }
    case Jumping:
    {
        if (previousState == Running)
        {
            xVelocity = 2;
        }
        else if (previousState == Walking)
        {
            xVelocity = 1;
        }
        else
        {
            xVelocity = 0;
        }
        break;
    }
    case Rolling:
    {
        if (xVelocity < 2)
        {
            xVelocity += .5;
        }
        else
        {
            xVelocity -= .5;
        }
        break;
    }
    case Falling:
    {
        if (currentFrameNumber < 3)
        {
            xVelocity -= .125;
        }
        else
        {
            xVelocity = 0;
        }
        break;
    }
    case RTurning:
    {
        xVelocity -= .25;
        break;
    }
    case JumpingDown:
    {
        xVelocity = 1;
        break;
    }
    case DFalling:
    {
        if (xVelocity > 1)
        {
            xVelocity -= .5;
        }
        else
        {
            xVelocity = 0;
        }
        break;
    }
    case Climbing:
    {
        yVelocity = 0;
        if (Game::_button[Game::Key_Up])
        {
            yVelocity = -5;
        }
        if (Game::_button[Game::Key_Down])
        {
            if (bottomWall == true)
            {
                playerState = Standing;
                previousState = Climbing;
            }
            else
            {
                yVelocity = +5;
            }

        }
        break;
    }
    case ClimbingUp:
    {
        xVelocity = 1;
        break;
    }
    case ClimbingDown:
    {
        if (currentFrameNumber == 2)
        {
            xVelocity = -5;
        }
        else
        {
            xVelocity = 0;
        }
        break;
    }
    default:
    {
        xVelocity = 0;
        if (_sprite.GetPosition().y + yPadding > Game::world1.column1[Game::world1.player_column()].yPosition)
        {
            _sprite.SetPosition(_sprite.GetPosition().x, Game::world1.column1[Game::world1.player_column()].yPosition - yPadding);
        }
        break;
    }
    }

    if (playerDirection == Left)
    {
        if (playerState != ClimbingDown)
        {
            xVelocity = xVelocity > 0 ? xVelocity : -xVelocity;
        }
        else
        {
            xVelocity = xVelocity > 0 ? -xVelocity : xVelocity;
        }
    }
    else if (playerDirection == Right)
    {
        if (playerState != ClimbingDown)
        {
            xVelocity = xVelocity > 0 ? -xVelocity : xVelocity;
        }
        else
        {
            xVelocity = xVelocity > 0 ? xVelocity : -xVelocity;
        }
    }
    if ((playerState != ClimbingUp and ((leftWall and playerDirection == Left)
                                        or
                                        (rightWall and playerDirection == Right))) or (collisionDirection(Game::world1.barrier._sprite) and playerDirection == Left))
    {
        xVelocity = 0;
    }
}

void Player::getPlayerPadding()
{
    switch(playerState)
    {
    case Standing:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case Walking:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case Running:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case Jumping:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case RollingDown:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case Rolling:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case RollingUp:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case ClimbingUp:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case ClimbingDown:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case Falling:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case Turning:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case RTurning:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case JumpingDown:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case DFalling:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    case HitNTurning:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    default:
    {
        xPaddingLeft = 40;
        xPaddingRight = 100;
        yPadding = 15;
        break;
    }
    }
}

void Player::getPlayerScore()
{
    static float fallScore = 0;
    float tempScore = 0;

    if (xVelocity < 0)
    {
        tempScore += fabs(xVelocity);
    }

    if (playerState == Falling)
    {
        fallScore += yVelocity / 10;
    }
    if (previousState == Falling and playerState != DFalling)
    {
        tempScore += fallScore;
        fallScore = 0;
    }
    if (playerState == Climbing and previousState == Falling and currentFrameNumber == 1)
    {
        tempScore += 10;
    }
    if (playerState == JumpingDown and currentFrameNumber == 1)
    {
        tempScore += 10;
    }

    if ((playerDirection == Left and _sprite.GetPosition().x - 40 < Game::world1.column1[Game::world1.player_column()].xPosition)
            or
            (playerDirection == Right and _sprite.GetPosition().x - 90 > Game::world1.column1[Game::world1.player_column()].xPosition)
            and
            (Game::world1.column1[Game::world1.player_column()].height > Game::world1.column1[Game::world1.player_column() + directionSign].            height))
    {
        if (playerState == Jumping and previousState == Running and currentFrameNumber < 3)
        {
            tempScore += 5;
        }
    }

    playerScore += tempScore / 10;
}

void Player::getPlayerHealth()
{
    static int healthDepletion = 0, healthRegeneration = 0;

    if (playerState == DFalling and currentFrameNumber == 2 and Game::gameClock.GetElapsedTime() > 2)
    {
        playerHealth -= 25;
    }

    if (xVelocity == 0 and yVelocity == 0 and playerState != DFalling)
    {
        healthDepletion += 1;
    }
    else if (playerState != DFalling)
    {
        healthRegeneration += 1;
    }
    if (playerState == HitNTurning and currentFrameNumber == maxFrameNumber)
    {
        playerHealth -= 10;
    }
    if (playerState == JumpingDown or playerState == Rolling and currentFrameNumber == 1 )
    {
        playerHealth += 1;
    }
    if ((playerDirection == Left and _sprite.GetPosition().x - 40 < Game::world1.column1[Game::world1.player_column()].xPosition)
            or
            (playerDirection == Right and _sprite.GetPosition().x - 90 > Game::world1.column1[Game::world1.player_column()].xPosition)
            and
            (Game::world1.column1[Game::world1.player_column()].height > Game::world1.column1[Game::world1.player_column() + directionSign].            height))
    {
        if (playerState == Jumping and previousState == Running and currentFrameNumber < 3)
        {
            playerHealth += 1;
        }
    }

    if (healthDepletion >= 10)
    {
        playerHealth -= 1;
        healthDepletion -= 10;
    }
    if (healthRegeneration >= 100)
    {
        playerHealth += 1;
        healthRegeneration -= 100;
    }
    if (playerHealth > 100)
    {
        playerHealth = 100;
    }
    else if (playerHealth < 0)
    {
        playerHealth = 0;
    }

}
