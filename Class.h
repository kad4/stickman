#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#include "headers.h"

class Sounds:public Thread
{
    enum Actions {SplashtoMenu,MenuButton,Camera,EscapeToMenu,MouseOverMenuItems};
    static bool PlayingGame;
    static Music CricketSound1,CricketSound2,FootSound,RollingSound,RTurningSound,FallingSound,DFallingSound,JumpSound,Climbing;
public:
    void Run(void);
    static void PlaySound(Actions);
    static void playRandomSounds(Music &);

    friend class MainMenu;
    friend class Game;
    friend class Player;
    friend void SplashScreen(void);
};


class VisibleGameObject           // Main drawable base class
{
protected:
    float xPosition,yPosition;
    float xVelocity, yVelocity;
    Sprite  _sprite;
    Image _image;
    string _filename;
    bool _isLoaded;
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();
    virtual void Load(string);
    virtual void Load(Image &);
    virtual void Draw(RenderWindow &);
    virtual void SetPosition(float, float);
    virtual void StorePosition(float, float);
    virtual void SetPosition(void);
    virtual void DrawPos(RenderWindow &);
    virtual void SetScale(float, float);
    virtual void SetCenter(float , float );
    virtual void SetSubRect (float x1, float y1, float x2, float y2);
    virtual void SetRotation(float);

    friend class Player;
    friend class World;
    friend class Game;
    friend class MainMenu;
};

class HUD : public VisibleGameObject
{
public:
    HUD ();
    ~HUD();
    virtual void displayHUD () = 0;
    static void displayHUDBackground();

protected:
    string hudType;
    double hudValue;
    static int hudOrder;
};

class Score : public HUD
{
public:
    Score ();
    void displayHUD();
};

class Health : public HUD
{
public:
    Health ();
    void displayHUD();
};

class MainMenu
{
public:
    enum MenuResult { Nothing, Exit, Play, Score};
    class MenuItem:public VisibleGameObject
    {
    public:
        Rect<int> rect;
        MenuResult action;
    };
    MenuResult Show(void);
private:
    MenuItem playButton,scoreButton,exitButton;
    void SetMenu(void);
    MenuResult HandleMouse(int x, int y);
    list<MenuItem> _menuItems;

    friend class Game;
    friend class Sounds;

};

class Player:public VisibleGameObject
{
    enum State {Standing, Walking, Running, Jumping, RollingDown, Rolling, RollingUp, ClimbingUp,ClimbingDown, Falling, Turning, RTurning,                  JumpingDown, DFalling, HitNTurning, Climbing, GettingUp};
    enum Direction {Left, Right, Up, Down, UpLeft, UpRight, DownLeft, DownRight};
    static float height, position, playerScore, playerHealth;
    static State playerState, previousState,nextState;
    static Direction playerDirection;
    static bool wallOn[4];
    static bool isMovable;
    static bool isJumpable;
    static int currentFrameNumber, maxFrameNumber, pausedFrameCount;
    static int directionSign;
    static bool fallPending;
    static bool bottomWall, leftWall, rightWall;
    int xPaddingLeft, xPaddingRight, yPadding;
public:
    void getPlayerInstance (void);
    void getPlayerVelocity (void);
    void getPlayerPadding (void);
    void getPlayerScore (void);
    void getPlayerHealth (void);
    void updatePlayer(Event &);
    void Load(bool, int, int);
    void directionMovement(bool, bool);
    void initiatePlayer(void);
    void frameHandler(void);
    Direction collisionDirection(void);
    bool collisionDirection(Sprite &);

    string stateToString (State);
    string directionToString (Direction);
    string numberToString (double);
    string booleanToString(bool);

    void displayText(string, string);
    void displayText(string, double);
    void displayText(string, bool);
    void displayText(string, Direction);
    void displayText(string , State);

    friend class Game;
    friend class World;
    friend class Sounds;
    friend class Score;
    friend class Health;
};

class Column:public VisibleGameObject
{
    int height;
    bool support;
public:
    void rand_support(int);

    friend class World;
    friend class Player;
};

class World
{
    VisibleGameObject city1,city2,jungle1,jungle2,sky1,sky2,barrier;
    static Image column_image,ground_image,ground_2d_image,empty_image;
    void check(void);
    bool wallOnLeft, wallOnRight, wallOnBottom;
    deque<Column> column1;
public:
    void drawWorld(void);
    void drawWorldOverlay(void);
    void SetWorld(void);
    void updateWorld(void);
    int rand_height(int);
    int player_column(void);

    friend class Player;
    friend class Game;
};

class Game         // Every member is static so no need to create a object of class Game
{
    enum GameState {Uninitialized, ShowingSplash, ShowingPostGame, ShowingScores, ShowingMenu, Playing, Exiting};
    enum buttons {Key_Left,Key_Right,Key_Up,Key_Down};
    static bool IsExiting(void);
    static bool _button[4];      // Array to hold the buttons left,right,up and down
    static bool allKeyUp;
    static bool gamePaused;
    static void GameLoop(void);
    static void ShowSplashScreen(void);
    static void ShowMenu(void);
    static void displayGameOverMessage();
    static void pauseGame();
    static void loadFonts();
    static GameState _gameState;
    static RenderWindow _mainWindow;
    static Player player1;
    static World world1;
    static Health healthHUD;
    static Score scoreHUD;
    static Sounds sound1;
    static int itemsDisplayed;
    static Font HUDFont, messageFont, highScoreFont, infoFont, debugFont;
    static Clock gameClock;
    static float play_time;
    static sf::Image cursorImage;
    static sf::Sprite cursorSprite;
public:
    static const int FPS;
    static void Start(void);
    static void handle_event(Event &);

    friend class Sounds;
    friend class MainMenu;
    friend class Highscore;
    friend class Player;
    friend class World;
    friend class Score;
    friend class Health;
    friend class HUD;
    friend void SplashScreen(void);
};


struct Playerinfo
{
    string Name;
    float Score,Time;
};

class Highscore
{
    static Playerinfo Scores[7];
public:
    static char * inputPlayer(void);
    static void displayScore(void);
    static void saveScore(float,float);

    friend class Player;
};
#endif // CLASS_H_INCLUDED
