#pragma once
void SplashScreen(void);

int Game::itemsDisplayed = 0;
const int Game::FPS = 22;
float Game::play_time;
bool Game::_button[4];
bool Game::allKeyUp = true;
bool Game::gamePaused = false;
Game::GameState Game::_gameState = Uninitialized;
sf::Image Game::cursorImage;
sf::Sprite Game::cursorSprite;

RenderWindow Game::_mainWindow;
Player Game::player1;
World Game::world1;
Sounds Game::sound1;
Health Game::healthHUD;
Score Game::scoreHUD;

Clock Game::gameClock;

Font Game::HUDFont, Game::messageFont,
     Game::highScoreFont, Game::infoFont, Game::debugFont;

