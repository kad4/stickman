#include "class.h"
sf::Music Sounds::CricketSound1,Sounds::CricketSound2,Sounds::FootSound;
sf::Music Sounds::RTurningSound,Sounds::FallingSound,Sounds::JumpSound,Sounds::Climbing;
sf::Music Sounds::DFallingSound,Sounds::RollingSound;
bool Sounds::PlayingGame=false;

void Sounds::Run(void)                                  //Thread for the playing sounds
{
    sf::Clock Clock;

    RollingSound.OpenFromFile("data/Audio/rolling.ogg");
    RollingSound.SetVolume(24);

    FootSound.OpenFromFile("data/Audio/footsteps.ogg");
    FootSound.SetVolume(24);

    RTurningSound.OpenFromFile("data/Audio/sliding.ogg");
    RTurningSound.SetVolume(50);

    FallingSound.OpenFromFile("data/Audio/falling.ogg");
    FallingSound.SetVolume(15);

    DFallingSound.OpenFromFile("data/Audio/dfalling.ogg");
    DFallingSound.SetVolume(50);

    JumpSound.OpenFromFile("data/Audio/falling.ogg");
    JumpSound.SetVolume(6);

    Climbing.OpenFromFile("data/Audio/climbing.ogg");
    Climbing.SetVolume(24);

    CricketSound1.OpenFromFile("data/Audio/cricket1.ogg");
    CricketSound1.SetLoop(true);
    CricketSound1.SetVolume(10);
    CricketSound1.Play();

    CricketSound2.OpenFromFile("data/Audio/cricket2.ogg");
    CricketSound2.SetLoop(true);
    CricketSound2.SetVolume(10);
    CricketSound2.Play();

    float Change=Randomizer::Random(-5,5);
    while(PlayingGame)
    {
        float Time = Clock.GetElapsedTime();
        if(Time>=Change && CricketSound2.GetStatus()==sf::Music::Playing)
        {
            Change=Randomizer::Random(-5,5);
            CricketSound2.Stop();
            Clock.Reset();
        }
        else if (Time>=Change && CricketSound2.GetStatus()!=sf::Music::Playing)
        {
            Change=Randomizer::Random(-5,5);
            CricketSound2.Play();
            Clock.Reset();
        }
        if(Game::player1.playerState==Player::Rolling && Player::currentFrameNumber==2)
            RollingSound.Play();
        if(Game::player1.playerState==Player::Running && Player::currentFrameNumber==7)
            FootSound.Play();
        if(Game::player1.playerState==Player::Walking && Player::currentFrameNumber==7)
            FootSound.Play();
        if(Game::player1.playerState==Player::Falling and Player::currentFrameNumber == 4)
            if(FallingSound.GetStatus()!=Music::Playing)
                FallingSound.Play();
        if (((Game::player1.playerState==Player::Jumping and Player::currentFrameNumber == 9) or (Game::player1.playerState==Player::JumpingDown and Player::currentFrameNumber == 7)) and Player::bottomWall)
            if(JumpSound.GetStatus()!=Music::Playing)
                JumpSound.Play();
        if((Game::player1.playerState==Player::ClimbingUp or Game::player1.playerState==Player::ClimbingDown) and Player::currentFrameNumber ==5)
            if(Climbing.GetStatus()!=Music::Playing)
                Climbing.Play();
        if(Game::player1.playerState==Player::RTurning)
            if(RTurningSound.GetStatus()!=Music::Playing)
                RTurningSound.Play();

        if(Game::player1.playerState==Player::DFalling and Player::currentFrameNumber==5)
            DFallingSound.Play();
    }
    CricketSound1.Stop();
    CricketSound2.Stop();
    RollingSound.Stop();
    FootSound.Stop();
    FallingSound.Stop();
    DFallingSound.Stop();
    JumpSound.Stop();
    Climbing.Stop();
    RTurningSound.Stop();
}

void Sounds::PlaySound(Sounds::Actions _actions)
{
    static sf::Music Music;

    if (Music.GetStatus() == sf::Music::Playing)
    {
        return;
    }

    switch(_actions)
    {
    case Sounds::MouseOverMenuItems:
        Music.OpenFromFile("data/Audio/mousehover.ogg");
        break;
    case Sounds::SplashtoMenu:
        Music.OpenFromFile("data/Audio/splashtomenu.ogg");
        break;
    case Sounds::MenuButton:
        Music.OpenFromFile("data/Audio/menubutton.ogg");
        break;
    case Sounds::Camera:
        Music.OpenFromFile("data/Audio/camera.ogg");
        break;
    case Sounds::EscapeToMenu:
        Music.OpenFromFile("data/Audio/menubutton.ogg");
        break;
    default:
        return;
    }
    Music.Play();
    //while(Music.GetStatus() == sf::Music::Playing);
}

void Sounds::playRandomSounds (Music &tempMusic)
{
    tempMusic.Play();
}

