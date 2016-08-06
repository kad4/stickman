#include "Class.h"
Playerinfo Highscore::Scores[7];
const int xSpacing=400,ySpacing=100;
void Highscore::saveScore(float Score,float Time)
{
//    ifstream Scorefile_input("data/score.dat");
//    ofstream Scorefile_output("data/score_temp.dat");
//    char ch;
//    while(!Scorefile_input.eof())
//    {
//        Scorefile_input.get(ch);
//        ch=(~ch);
//        Scorefile_output.put(ch);
//    }
//    Scorefile_input.close();
//    Scorefile_output.close();
//    remove("data/score.dat");
//    rename("data/score_temp.dat","data/score.dat");

    ifstream Scorefile("data/score.dat");
    for(int i=0; i<7; i++)
    {
        char temp[50];
        Scorefile.getline(temp,50);
        Scores[i].Name=temp;
        Scorefile>>Scores[i].Score;
        Scorefile.ignore();
        Scorefile>>Scores[i].Time;
        Scorefile.ignore();
    }
    Scorefile.close();

    bool Got_Highscore=false;
    int i;
    for(i=0; i<7; i++)
    {
        if(Score/Time>Scores[i].Score/Scores[i].Time)
        {
            Got_Highscore=true;
            break;
        }
    }
    if(!Got_Highscore)
        return;

    string player_name=inputPlayer();

    if (player_name == "")
    {
        displayScore();
        return;
    }

    int j;
    for(j=5; j>=i; j--)
    {
        Scores[j+1].Name=Scores[j].Name;
        Scores[j+1].Score=Scores[j].Score;
        Scores[j+1].Name=Scores[j].Name;
    }
    j++;
    Scores[j].Name=player_name;
    Scores[j].Score=Score;
    Scores[j].Time=Time;

    ofstream scorefile("data/score.dat");
    for(int i=0; i<7; i++)
        scorefile<<Scores[i].Name<<"\n"<<Scores[i].Score<<"\n"<<Scores[i].Time<<"\n";
    scorefile.close();
}
char * Highscore::inputPlayer(void)
{
    static char name[50]="\0";
    sf::String text;
    text.SetFont(Game::highScoreFont);
    text.SetSize(30);

    Game::_mainWindow.Clear();
    Game::_mainWindow.Display();

    Event event;
    int j=0;
    while(true)
    {
        Game::_mainWindow.GetEvent(event);
        if(event.Type == Event::KeyPressed)
        {
            if(event.Key.Code==Key::Return && name[0]!='\0')
                break;
            if(event.Key.Code==Key::Back)
                name[--j]='\0';
            for (int i='A'; i<='Z'; i++)
            {
                if (event.Key.Code==Key::A+(i-'A'))
                {
                    name[j]=i;
                    name[++j]='\0';
                }
                if(event.Key.Code==Key::Space)
                {
                    name[j]=' ';
                    name[++j]='\0';
                }
            }
        }
        Game::_mainWindow.Clear();
        text.SetPosition(100,100);
        text.SetText("You Got A HighScore Enter your name");
        Game::_mainWindow.Draw(text);

        text.SetPosition(300,300);
        text.SetText(name);
        Game::_mainWindow.Draw(text);
        Game::_mainWindow.Display();
    }
    return (name);

}

void Highscore::displayScore(void)   //Displays the score
{
    ifstream scorefile("data/score.dat");
    char temp[50];

    sf::String text;
    text.SetFont(Game::highScoreFont);
    text.SetSize(40);

    Game::_mainWindow.Clear();
    Game::_mainWindow.Display();

    sf::Image Image;
    Image.LoadFromFile("data/images/Mainmenu.jpg");
    sf::Sprite Sprite(Image);
    Game::_mainWindow.Draw(Sprite);

    text.SetPosition(0*xSpacing,0*ySpacing);
    text.SetText("Name");
    Game::_mainWindow.Draw(text);

    text.SetPosition(1*xSpacing,0*ySpacing);
    text.SetText("Score");
    Game::_mainWindow.Draw(text);

    text.SetPosition(2*xSpacing,0*ySpacing);
    text.SetText("Time");
    Game::_mainWindow.Draw(text);

    for(int i=1; i<8; i++)
    {
        scorefile.getline(temp,50);
        text.SetPosition(0*xSpacing,i*ySpacing);
        text.SetText(temp);
        Game::_mainWindow.Draw(text);

        scorefile.getline(temp,50);
        text.SetPosition(1*xSpacing,i*ySpacing);
        text.SetText(temp);
        Game::_mainWindow.Draw(text);

        scorefile.getline(temp,50);
        text.SetPosition(2*xSpacing,i*ySpacing);

        text.SetText(temp);
        Game::_mainWindow.Draw(text);
    }
    Game::_mainWindow.Display();
    Event event;
    while(true)
    {
        Game::_mainWindow.GetEvent(event);
        if(event.Type == Event::KeyPressed or event.Type == Event::MouseButtonPressed)
        {
            Game::_gameState = Game::ShowingMenu;
            return;
        }
    }
}
