#include "class.h"
void MainMenu::SetMenu(void)
{
    //Play button
    playButton.Load("data/images/button1.png");
    playButton.SetPosition(320,366);
    playButton.SetScale(.5,.5);
    playButton.rect.Left = playButton._sprite.GetPosition().x;
    playButton.rect.Right = playButton._sprite.GetPosition().x+playButton._sprite.GetSize().x;
    playButton.rect.Top= playButton._sprite.GetPosition().y;
    playButton.rect.Bottom = playButton._sprite.GetPosition().y+playButton._sprite.GetSize().y;
    playButton.action = Play;

    //Score button
    scoreButton.Load("data/images/button2.png");
    scoreButton.SetScale(.5,.5);
    scoreButton.SetPosition(320,500);
    scoreButton.rect.Left = scoreButton._sprite.GetPosition().x;
    scoreButton.rect.Right = scoreButton._sprite.GetPosition().x+scoreButton._sprite.GetSize().x;;
    scoreButton.rect.Top = scoreButton._sprite.GetPosition().y;
    scoreButton.rect.Bottom = scoreButton._sprite.GetPosition().y+scoreButton._sprite.GetSize().y;
    scoreButton.action = Score;

    //Exit button
    exitButton.Load("data/images/button3.png");
    exitButton.SetScale(.5,.5);
    exitButton.SetPosition(320,634);
    exitButton.rect.Left = exitButton._sprite.GetPosition().x;
    exitButton.rect.Right = exitButton._sprite.GetPosition().x+exitButton._sprite.GetSize().x;;
    exitButton.rect.Top = exitButton._sprite.GetPosition().y;
    exitButton.rect.Bottom = exitButton._sprite.GetPosition().y+exitButton._sprite.GetSize().y;
    exitButton.action = Exit;

    _menuItems.push_back(playButton);
    _menuItems.push_back(scoreButton);
    _menuItems.push_back(exitButton);
}
MainMenu::MenuResult MainMenu::Show(void)
{

    //Load menu image from file
    Image image;
    image.LoadFromFile("data/images/mainmenu.jpg");
    Sprite sprite(image);

    Game::_mainWindow.Draw(sprite);
    playButton.Draw(Game::_mainWindow);
    scoreButton.Draw(Game::_mainWindow);
    exitButton.Draw(Game::_mainWindow);
    Game::_mainWindow.Display();

    if (Game::cursorImage.LoadFromFile("data/images/cursor.png"))
    {
        Game::cursorSprite.SetImage(Game::cursorImage);
    }
    else
    {
        Game::_mainWindow.ShowMouseCursor(true);
    }

    Event menuEvent;
    bool flag1=false,flag2=false,flag3=false;
    while(true)
    {
        MenuResult temp=Nothing;
        Game::_mainWindow.GetEvent(menuEvent);

        Game::cursorSprite.SetPosition(menuEvent.MouseMove.X, menuEvent.MouseMove.Y);

        if(menuEvent.Type == Event::MouseButtonPressed)
        {
            temp=HandleMouse(menuEvent.MouseButton.X,menuEvent.MouseButton.Y);
            switch(temp)
            {
            case Play:
            {
                playButton.Load("data/images/button1_down.png");
                scoreButton.Load("data/images/button2.png");
                exitButton.Load("data/images/button3.png");
                break;
            }
            case Score:
            {
                playButton.Load("data/images/button1.png");
                scoreButton.Load("data/images/button2_down.png");
                exitButton.Load("data/images/button3.png");
                break;
            }
            case Exit:
            {
                playButton.Load("data/images/button1.png");
                scoreButton.Load("data/images/button2.png");
                exitButton.Load("data/images/button3_down.png");

                break;
            }
            default:
                break;
            }
        }
        if(HandleMouse(menuEvent.MouseMove.X,menuEvent.MouseMove.Y)==Play)
        {
            if (!flag1 )
            {
                Sounds::PlaySound(Sounds::MouseOverMenuItems);
                flag1 = true;
                flag2=false;
                flag3=false;
            }
            playButton.Load("data/images/button1_over.png");
            scoreButton.Load("data/images/button2.png");
            exitButton.Load("data/images/button3.png");
        }
        else if(HandleMouse(menuEvent.MouseMove.X,menuEvent.MouseMove.Y)==Score)
        {
            if (!flag2 )
            {
                Sounds::PlaySound(Sounds::MouseOverMenuItems);
                flag1 =false;
                flag2=true;
                flag3=false;
            }
            playButton.Load("data/images/button1.png");
            scoreButton.Load("data/images/button2_over.png");
            exitButton.Load("data/images/button3.png");
        }
        else if(HandleMouse(menuEvent.MouseMove.X,menuEvent.MouseMove.Y)==Exit)
        {
            if (!flag3 )
            {
                Sounds::PlaySound(Sounds::MouseOverMenuItems);
                flag1 =false;
                flag2=false;
                flag3=true;
            }
            playButton.Load("data/images/button1.png");
            scoreButton.Load("data/images/button2.png");
            exitButton.Load("data/images/button3_over.png");
        }
        else
        {
            playButton.Load("data/images/button1.png");
            scoreButton.Load("data/images/button2.png");
            exitButton.Load("data/images/button3.png");
            flag1 = false;
            flag2=false;
            flag3=false;
        }
        Game::_mainWindow.Draw(sprite);

        playButton.Draw(Game::_mainWindow);
        scoreButton.Draw(Game::_mainWindow);
        exitButton.Draw(Game::_mainWindow);

        Game::_mainWindow.Draw(Game::cursorSprite);

        Game::_mainWindow.Display();

        if(temp!=Nothing)
            return temp;
    } //While loop

}

MainMenu::MenuResult MainMenu::HandleMouse(int x, int y)
{
    list<MenuItem>::iterator it;
    for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        Rect<int> menuItemRect = (*it).rect;
        if( menuItemRect.Bottom > y and menuItemRect.Top < y and menuItemRect.Left < x and menuItemRect.Right > x)
        {
            return (*it).action;
        }
    }
    return Nothing;
}
