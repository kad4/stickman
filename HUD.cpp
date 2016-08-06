#include "class.h"
int HUD::hudOrder = 0;

HUD::HUD()
{
    hudOrder++;
}
HUD::~HUD()
{
    hudOrder--;
}

void HUD::displayHUDBackground()
{
    Shape hudBackground = Shape::Rectangle(-5, 685, 1029, 773, Color::Color(0,0,0,180), 2, Color::White);
    Game::_mainWindow.Draw(hudBackground);
}

Score::Score()
{
    hudType = "Score";
    hudValue = Game::player1.playerScore;
}

void Score::displayHUD()
{
    string tempString = "Score: " + Game::player1.numberToString((int)Game::player1.playerScore);
    sf::String hudString(tempString, Game::HUDFont, 35);
    hudString.SetPosition(100, 705);
    Game::_mainWindow.Draw(hudString);
}

Health::Health()
{
    hudType = "HealthMeter";
    hudValue = Game::player1.playerHealth;
    if (!_image.LoadFromFile("data/images/healthBar.png"))
    {
        exit(0);
    }
    _sprite.SetImage(_image);
}

void Health::displayHUD()
{
    int x1;
    x1 = hudOrder == 2 ? 750 : 100;

    Shape hudOutline = Shape::Rectangle(x1, 720, x1 + 200, 729, Color::Black, 2, Color::Black);

    _sprite.SetPosition( x1 + 1, 722);
    _sprite.SetScale (Game::player1.playerHealth / 100 , 1);

    Game::_mainWindow.Draw(hudOutline);

    if (Game::player1.playerHealth > 0)
    {
        Game::_mainWindow.Draw(_sprite);
    }

}
