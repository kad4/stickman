#include "class.h"
void SplashScreen(void)
{
    sf::Image Image;
    sf::Image splashPlayer;

    splashPlayer.LoadFromFile("data/images/player/Spritesheet/spritesheet.png");
    Image.LoadFromFile("data/images/SplashScreen.jpg");

    sf::Sprite Sprite(Image);
    sf::Sprite splashPlayerSprite(splashPlayer);

    sf::Music splashMusic;
    splashMusic.OpenFromFile("data/Audio/Falling.ogg");

    Game::_mainWindow.Draw(Sprite);
    Game::_mainWindow.Display();
    Event event;


    int velocity = 0;

    int _x = 60, _y = 1080;

    splashPlayerSprite.SetSubRect(IntRect(_x, _y, _x + 60, _y + 120));
    splashPlayerSprite.SetPosition(512,-120);

    while (true)
    {
        splashPlayerSprite.SetPosition(512, splashPlayerSprite.GetPosition().y + velocity);

        Game::_mainWindow.Draw(Sprite);
        Game::_mainWindow.Draw(splashPlayerSprite);
        Game::_mainWindow.Display();

        if (splashPlayerSprite.GetPosition().y < 230)
        {
            velocity += 3;
        }
        else
        {
            velocity = 0;
            splashPlayerSprite.SetPosition(512, 270);
            Game::_mainWindow.Draw(Sprite);
            Game::_mainWindow.Draw(splashPlayerSprite);
            Game::_mainWindow.Display();
            break;
        }

    }
    Sounds::playRandomSounds(splashMusic);

    _y = 1560;
    for (int i=1; i < 7; i++)
    {
        splashPlayerSprite.SetSubRect(IntRect(_x * i, _y, _x * i + 60, _y + 120));
        Game::_mainWindow.Draw(Sprite);
        Game::_mainWindow.Draw(splashPlayerSprite);
        Game::_mainWindow.Display();

    }
    for (int i=0; i < Game::FPS; i++ )
    {
        splashPlayerSprite.SetSubRect(IntRect(360, _y, 420, _y + 120));
        Game::_mainWindow.Draw(Sprite);
        Game::_mainWindow.Draw(splashPlayerSprite);
        Game::_mainWindow.Display();
    }
    _y = 1920;
    for (int i=1; i < 7; i++)
    {
        splashPlayerSprite.SetSubRect(IntRect(_x * i, _y, _x * i + 60, _y + 120));
        Game::_mainWindow.Draw(Sprite);
        Game::_mainWindow.Draw(splashPlayerSprite);
        Game::_mainWindow.Display();

    }

    splashMusic.OpenFromFile("data/audio/footsteps.ogg");
    _y = 240;
    while (splashPlayerSprite.GetPosition().x < 1024)
    {
        for (int i=0; i < 8; i++)
        {
            if (i==1) Sounds::playRandomSounds(splashMusic);
            splashPlayerSprite.SetSubRect(IntRect(_x * i, _y, _x * i + 60, _y + 120));
            splashPlayerSprite.SetPosition(splashPlayerSprite.GetPosition().x + 8, splashPlayerSprite.GetPosition().y);
            Game::_mainWindow.Draw(Sprite);
            Game::_mainWindow.Draw(splashPlayerSprite);
            Game::_mainWindow.Display();

        }
    }
    Game::_gameState = Game::ShowingMenu;
}
