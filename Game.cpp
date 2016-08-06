#include "class.h"
#include "game.h"
void Game::Start(void)
{
    if(_gameState != Uninitialized)
    {
        return;
    }
    _mainWindow.Create(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BIT),"Stick Man Rumble",Style::Fullscreen);
    _mainWindow.UseVerticalSync(false);
    _mainWindow.SetFramerateLimit(FPS);
    _mainWindow.ShowMouseCursor(false);

    _gameState = Game::ShowingSplash;
    loadFonts();

    while(!IsExiting())
    {
        GameLoop();
    }
    _mainWindow.Close();
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen();   //Load the splashscreen and return only when a key is pressed or mouse is clicked
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    mainMenu.SetMenu();

    _mainWindow.SetFramerateLimit(120);

    MainMenu::MenuResult result = mainMenu.Show();
    switch(result)
    {
    case MainMenu::Exit:
    {
        _gameState = Game::Exiting;
        Sounds::PlaySound(Sounds::MenuButton);
        break;
    }
    case MainMenu::Play:
    {
        _gameState = Game::Playing;
        Sounds::PlaySound(Sounds::MenuButton);
        for (int i=0; i<4; i++)
            _button[i]= false;
        player1.initiatePlayer();
        world1.SetWorld();
        Sounds::PlayingGame=true;
        Game::sound1.Launch();             //Launches a thread to play the sounds

        gameClock.Reset();
        break;
    }
    case MainMenu::Score:
    {
        _gameState = Game::ShowingScores;
        Sounds::PlaySound(Sounds::MenuButton);
        break;
    }
    default:
    {
        break;
    }
    }
    Game::_mainWindow.SetFramerateLimit(Game::FPS);
}

void Game::displayGameOverMessage()
{
    int gamePlayedTime = gameClock.GetElapsedTime();
    gameClock.Reset();

    _mainWindow.Clear();
    Image tempImage;
    tempImage.LoadFromFile("gameScreen.jpg");
    Sprite tempSprite(tempImage);

    sf::String messageTitle ("Game Over !!!", messageFont, 75);
    sf::String messageString ("Press any key to see the highscores", messageFont, 25);

    sf::Shape messageBox;
    messageBox.AddPoint(SCREEN_WIDTH / 2 - 1, SCREEN_HEIGHT / 2 - 1,  Color(0, 0, 0, 200), Color(255, 255, 255));
    messageBox.AddPoint(SCREEN_WIDTH / 2 - 1, SCREEN_HEIGHT / 2 + 1,  Color(0, 0, 0, 200), Color(255, 255, 255));
    messageBox.AddPoint(SCREEN_WIDTH / 2 + 1, SCREEN_HEIGHT / 2 - 1,  Color(0, 0, 0, 200), Color(255, 255, 255));
    messageBox.AddPoint(SCREEN_WIDTH / 2 + 1, SCREEN_HEIGHT / 2 + 1,  Color(0, 0, 0, 200), Color(255, 255, 255));

    for (int i=0; i < FPS; i++)
    {
        messageBox.SetPointPosition(0, SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 2 * i/FPS), SCREEN_HEIGHT / 2 - (SCREEN_HEIGHT / 2 * i/FPS));
        messageBox.SetPointPosition(1, SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 2 * i/FPS), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2 * i/FPS));
        messageBox.SetPointPosition(3, SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2 * i/FPS), SCREEN_HEIGHT / 2 - (SCREEN_HEIGHT / 2 * i/FPS));
        messageBox.SetPointPosition(2, SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 2 * i/FPS), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 2 * i/FPS));

        _mainWindow.Draw(tempSprite);
        _mainWindow.Draw(messageBox);

        _mainWindow.Display();
    }

    messageTitle.SetPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
    messageString.SetPosition(SCREEN_WIDTH / 4, 3 * SCREEN_HEIGHT / 4);

    _mainWindow.Draw(messageTitle);
    _mainWindow.Draw(messageString);

    _mainWindow.Display();

    remove("gameScreen.jpg");

    pauseGame();
}

void Game::handle_event(Event & currentEvent)
{
    if(currentEvent.Type == Event::KeyPressed)
    {
        switch(currentEvent.Key.Code)
        {
        case Key::Escape:
        {
            Sounds::PlayingGame=false;
            Sounds::PlaySound(Sounds::EscapeToMenu);
            _gameState=ShowingMenu;
            break;
        }
        case Key::F1:
        {
            Sounds::PlaySound(Sounds::Camera);
            Image Screen = _mainWindow.Capture();
            Screen.SaveToFile("screenshot.jpg");
            break;
        }
        case Key::P:
        {
            gamePaused = true;
            pauseGame();
            break;
        }
        case Key::Left:
        {
            _button[Key_Left]=true;
            break;
        }
        case Key::Right:
        {
            _button[Key_Right]=true;
            break;
        }
        case Key::Up:
        {
            _button[Key_Up]=true;
            break;
        }
        case Key::Down:
        {
            _button[Key_Down]=true;
            break;
        }
        default:
        {
            break;
        }
        } //Switch
    } //If condition
    else if(currentEvent.Type == Event::KeyReleased)
    {
        switch(currentEvent.Key.Code)
        {
        case Key::Left:
        {
            _button[Key_Left]=false;
            break;
        }
        case Key::Right:
        {
            _button[Key_Right]=false;
            break;
        }
        case Key::Up:
        {
            _button[Key_Up]=false;
            break;
        }
        case Key::Down:
        {
            _button[Key_Down]=false;
            break;
        }
        default:
        {
            break;
        }
        } //Switch
    }// Else if

    allKeyUp = true;
    for (int i = 0; i<4; i++)
    {
        if (_button[i] == true)
        {
            allKeyUp = false;
            break;
        }
    }
}

void Game::pauseGame()
{
    Event keyEvent;
    bool keyPressed = false;
    while (!keyPressed)
    {
        _mainWindow.GetEvent(keyEvent);
        if (keyEvent.Type == Event::KeyPressed and !gamePaused)
            keyPressed = true;
        if (keyEvent.Type == Event::KeyPressed and gamePaused)
            if (keyEvent.Key.Code == Key::P)
            {
                keyPressed = true;
                gamePaused = false;
            }
        if (keyEvent.Key.Code == Key::Escape)
        {
            _gameState=ShowingMenu;
        }
    }
}

void Game::GameLoop(void)
{
    while(_mainWindow.IsOpened())
    {
        player1.getPlayerInstance();
        Event currentEvent;
        while(true)
        {
            _mainWindow.GetEvent(currentEvent);
            switch(_gameState)
            {
            case Game::ShowingScores:
            {
                Highscore::displayScore();
                break;
            }
            case Game::ShowingMenu:
            {
                ShowMenu();
                break;
            }
            case Game::ShowingSplash:
            {
                ShowSplashScreen();
                break;
            }
            case Game::Playing:
            {

                float Time = gameClock.GetElapsedTime();
                int frameRate = 1 /_mainWindow.GetFrameTime();
                string tempX, tempY;

                Player::Direction tempCollision = player1.collisionDirection();

                itemsDisplayed = 0;

                player1.getPlayerInstance();
                world1.drawWorld();

                player1.Draw(_mainWindow);
                world1.drawWorldOverlay();

                HUD::displayHUDBackground();
                healthHUD.displayHUD();
                scoreHUD.displayHUD();

                player1.displayText("FPS", (double)frameRate);
                player1.displayText("Previous State", player1.previousState);
                player1.displayText("Current State", player1.playerState);
                player1.displayText("Next State", player1.nextState);
                player1.displayText("Direction", player1.playerDirection);
                player1.displayText("Player Position", player1.position);
                player1.displayText("World Index", (double)world1.player_column());

                {
                    tempX = player1.numberToString((int)world1.column1[world1.player_column()].xPosition),
                    tempY = player1.numberToString((int)world1.column1[world1.player_column()].yPosition);
                }

                player1.displayText("Player Column (x,y)", "(" + tempX + "," + tempY + ")");

                {
                    tempX = player1.numberToString((int)player1._sprite.GetPosition().x);
                    tempY = player1.numberToString((int)player1._sprite.GetPosition().y);
                }

                player1.displayText("Player (x,y)", "(" + tempX + "," + tempY + ")");
                player1.displayText("Player Y Velocity", player1.yVelocity);
                player1.displayText("Player X Velocity", (double)player1.xVelocity);
                player1.displayText("wallOnLeft", player1.leftWall);
                player1.displayText("wallOnRight", player1.rightWall);
                player1.displayText("wallOnBottom", player1.bottomWall);
                player1.displayText("MaxFrameNumber", (double)player1.maxFrameNumber);
                player1.displayText("CurrentFrameNumber", (double)player1.currentFrameNumber);
                player1.displayText("PausedFrameCount", (double)player1.pausedFrameCount);
                player1.displayText("Collision with barrier", player1.collisionDirection(world1.barrier._sprite));
                player1.displayText("Score", (double)(int)player1.playerScore);
                player1.displayText("Health", (double)(int)player1.playerHealth);
                player1.displayText("Time", Time);

                _mainWindow.Display();  //Don't delete

                handle_event(currentEvent);

                player1.updatePlayer(currentEvent);
                world1.updateWorld();

                if (player1.playerHealth == 0 and player1.playerState == Player::DFalling and player1.currentFrameNumber == 8)
                {
                    _mainWindow.Display();  //Don't delete
                    Sounds::PlayingGame=false;
                    play_time=gameClock.GetElapsedTime();
                    _gameState = ShowingPostGame;
                }
                break;
            }
            case Game::Exiting:
            {
                return;
            }
            case Game::ShowingPostGame:
            {
                Image Screen = _mainWindow.Capture();
                Screen.SaveToFile("gameScreen.jpg");
                displayGameOverMessage();
                Highscore::saveScore(static_cast<int>(player1.playerScore),static_cast<int>(play_time));
                Highscore::displayScore();
                _gameState = ShowingMenu;
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void Game::loadFonts(void)
{
    if (!HUDFont.LoadFromFile("data/fonts/HUDFont.ttf")
            or
            !messageFont.LoadFromFile("data/fonts/messageFont.ttf")
            or
            !highScoreFont.LoadFromFile("data/fonts/highScoreFont.ttf")
            or
            !infoFont.LoadFromFile("data/fonts/infoFont.ttf")
            or
            !debugFont.LoadFromFile("data/fonts/debugFont.ttf"))
    {
        exit(0);
    }
}
