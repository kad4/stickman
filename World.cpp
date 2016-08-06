#include "class.h"
#include "world.h"
void World::SetWorld(void)        //Loading and resetting the world
{
    if(column1.empty())          //Load the images
    {
        column_image.LoadFromFile("data/images/column.png");
        ground_image.LoadFromFile("data/images/ground.png");
        ground_2d_image.LoadFromFile("data/images/ground_2d.png");

        empty_image.Create(138, 70, Color(255, 0, 0));

        sky1.Load("data/images/Sky.png");
        city1.Load("data/images/City.png");
        jungle1.Load("data/images/Jungle.png");
        barrier.Load("data/images/barrier.png");
    }
    else if(!column1.empty())
    {
        int x=column1.size();   //Don't place it in the for loop
        for(int i=0; i<x; i++)
            column1.pop_front();   //Makes deque empty
    }
    sky1.StorePosition(0,0);
    sky1.xVelocity=-sky_velocity*Game::player1.xVelocity;
    sky2=sky1;
    sky2.StorePosition(sky1._sprite.GetSize().x,0);

    city1.StorePosition(0,0);
    city1.xVelocity=city_velocity*Game::player1.xVelocity;
    city2=city1;
    city2.StorePosition(city1._sprite.GetSize().x,0);

    jungle1.StorePosition(0,0);
    jungle1.xVelocity=jungle_velocity*Game::player1.xVelocity;
    jungle2=jungle1;
    jungle2.StorePosition(jungle1._sprite.GetSize().x,0);

    for(int i=0; i<column_no; i++)      //For Creating the columns
    {
        Column temp;
        temp.height=rand_height(i);
        temp.rand_support(i);
        temp.Load(empty_image);
        temp.xVelocity=Game::player1.xVelocity*column_velocity;
        if(i==0)
        {
            temp.xPosition=0;
            temp.support=true;
        }
        else
        {
            temp.xPosition=column1[i-1].xPosition+291.0/345*(temp._sprite.GetSize().x);
        }
        temp.yPosition=SCREEN_HEIGHT-temp._sprite.GetSize().y-137.0/175*(temp._sprite.GetSize().y*temp.height);
        temp.SetPosition();
        column1.push_back(temp);
    }
    barrier.StorePosition(column1[1].xPosition+20,column1[1].yPosition-barrier._sprite.GetSize().y+20);
    barrier.xVelocity=column1[1].xVelocity;
}

void World::drawWorld(void)
{
    sky1.DrawPos(Game::_mainWindow);
    sky2.DrawPos(Game::_mainWindow);
    city1.DrawPos(Game::_mainWindow);
    city2.DrawPos(Game::_mainWindow);
    jungle1.DrawPos(Game::_mainWindow);
    jungle2.DrawPos(Game::_mainWindow);

    for(unsigned int i=0; i<column1.size(); i++)
    {
        //For skipping the columns outside of screen width
        if(column1[i].xPosition<0-column1[i]._sprite.GetSize().y-137.0/175*column1[i]._sprite.GetSize().y*2 or column1[i].xPosition>SCREEN_WIDTH+       column1[i]._sprite.GetSize().y+137.0/175*column1[i]._sprite.GetSize().y)
            continue;
        for(int j=0; j<=column1[i].height; j++)
        {
            column1[i].yPosition=SCREEN_HEIGHT-column1[i]._sprite.GetSize().y-137.0/175*(column1[i]._sprite.GetSize().y*j);
            //Support columns
            if(column1[i].support)
            {
                if(!((i!=0 and (j>=column1[i-1].height or j>=column1[i+1].height))or(i==0 and j>=column1[1].height)))
                {
                    column1[i].Load(column_image);
                    column1[i].DrawPos(Game::_mainWindow);
                }
            }
            //Places where support columns must be replaced by the ground blocks ; Replaces the top block as well
            if((i!=0 and (j>=column1[i-1].height or j>=column1[i+1].height))or(i==0 and j>=column1[1].height))
            {
                column1[i].Load(ground_image);
                column1[i].DrawPos(Game::_mainWindow);
            }
        }
        column1[i].Load(ground_image);
        column1[i].DrawPos(Game::_mainWindow);
    }
    barrier.DrawPos(Game::_mainWindow);
}

void World::drawWorldOverlay(void)
{
    for(unsigned int i=0; i<column1.size(); i++)
    {
        column1[i].Load(ground_2d_image);
        for(int j=0; j<=column1[i].height; j++)
        {
            column1[i].yPosition=SCREEN_HEIGHT-column1[i]._sprite.GetSize().y-137.0/175*(column1[i]._sprite.GetSize().y*j);
            if((i!=0 and (j>=column1[i-1].height or j>=column1[i+1].height)) or (i==0 and j>=column1[1].height))
            {
                column1[i].DrawPos(Game::_mainWindow);
            }
        }
        column1[i].DrawPos(Game::_mainWindow);
    }
}

int World::rand_height(int n)
{
    int x=9;
    if (n==0)
    {
        return x;
    }
    bool flag=true;
    while(flag)
    {
        x=Randomizer::Random(3,8);
        if(x-World::column1[n-1].height>=height_diff)
        {
            flag=true;
        }
        else
        {
            flag=false;
        }
    }
    return x;
}

void World::updateWorld(void)
{
    check();                //For checking and resetting the positions of background image
    sky1.xVelocity=-sky_velocity*Game::player1.xVelocity;
    sky2.xVelocity=-sky_velocity*Game::player1.xVelocity;
    city1.xVelocity=city_velocity*Game::player1.xVelocity;
    city2.xVelocity=city_velocity*Game::player1.xVelocity;
    jungle1.xVelocity=jungle_velocity*Game::player1.xVelocity;
    jungle2.xVelocity=jungle_velocity*Game::player1.xVelocity;
    barrier.xVelocity=column_velocity*Game::player1.xVelocity;

    sky2.xPosition=sky2.xPosition+sky2.xVelocity;
    city1.xPosition=city1.xPosition+city1.xVelocity;
    city2.xPosition=city2.xPosition+city2.xVelocity;
    jungle1.xPosition=jungle1.xPosition+jungle1.xVelocity;
    jungle2.xPosition=jungle2.xPosition+jungle2.xVelocity;
    barrier.xPosition=barrier.xPosition+barrier.xVelocity;

    for(unsigned int i=0; i<column1.size(); i++)
    {
        column1[i].xVelocity=column_velocity*Game::player1.xVelocity;
        column1[i].xPosition=column1[i].xPosition+column1[i].xVelocity;
    }
}

void World::check(void)
{
    //For going left
    if(sky1.xPosition>0 and sky2.xPosition>sky2._sprite.GetSize().x)
    {
        sky2.xPosition=-sky2._sprite.GetSize().x+4;
    }
    if(sky2.xPosition>0 and sky1.xPosition>sky1._sprite.GetSize().x)
    {
        sky1.xPosition=-sky1._sprite.GetSize().x+4;
    }
    if(city1.xPosition>0 and city2.xPosition>city2._sprite.GetSize().x)
    {
        city2.xPosition=-city2._sprite.GetSize().x+4;
    }
    if(city2.xPosition>0 and city1.xPosition>city1._sprite.GetSize().x)
    {
        city1.xPosition=-city1._sprite.GetSize().x+4;
    }
    if(jungle1.xPosition>0 and jungle2.xPosition>jungle2._sprite.GetSize().x)
    {
        jungle2.xPosition=-jungle2._sprite.GetSize().x+4;
    }
    if(jungle2.xPosition>0 and jungle1.xPosition>jungle1._sprite.GetSize().x)
    {
        jungle1.xPosition=-jungle1._sprite.GetSize().x+4;
    }

    //Fpr going right
    if(sky1.xPosition<0 and sky2.xPosition<-sky2._sprite.GetSize().x)
    {
        sky2.xPosition=sky2._sprite.GetSize().x-4;
    }
    if(sky2.xPosition<0 and sky1.xPosition<-sky1._sprite.GetSize().x)
    {
        sky1.xPosition=sky2._sprite.GetSize().x-4;
    }
    if(city1.xPosition<0 and city2.xPosition<-city2._sprite.GetSize().x)
    {
        city2.xPosition=city2._sprite.GetSize().x-4;
    }
    if(city2.xPosition<0 and city1.xPosition<-city1._sprite.GetSize().x)
    {
        city1.xPosition=city1._sprite.GetSize().x-4;
    }
    if(jungle1.xPosition<0 and jungle2.xPosition<-jungle2._sprite.GetSize().x)
    {
        jungle2.xPosition=jungle2._sprite.GetSize().x-4;
    }
    if(jungle2.xPosition<0 and jungle1.xPosition<-jungle1._sprite.GetSize().x)
    {
        jungle1.xPosition=jungle1._sprite.GetSize().x-4;
    }
    if(column1.back().xPosition<=SCREEN_WIDTH) //For going right
    {
        Column temp;
        temp.height=rand_height(column1.size());
        temp.rand_support(column1.size());
        temp.Load(World::ground_image);
        temp.xVelocity=column_velocity*Game::player1.xVelocity;
        temp.xPosition=column1[column1.size()-1].xPosition+291.0/345*(temp._sprite.GetSize().x);
        temp.yPosition=SCREEN_HEIGHT-temp._sprite.GetSize().y-137.0/175*(temp._sprite.GetSize().y*temp.height);
        temp.SetPosition();
        column1.push_back(temp);
    }
    //For checking and deleting the columns to the left
    bool flag=false;
    for(int i=column1.size()-2; i>=0; i--)
    {
        if(column1[i].height-column1[i+1].height>=2)
        {
            for(int j=i; j>=0; j--)
            {
                if(column1[j].height-column1[j+1].height>=2 and column1[j].xPosition<0-column1[j]._sprite.GetSize().y-137.0/175*column1[j]._sprite.GetSize().y*2)
                {
                    for(int k=0; k<j-3; k++)
                        column1.pop_front();
                    j=0;
                    i=0;
                    if(player_column()>4)
                        flag=true;
                }
            }
        }
    }
    if(flag)
    {
        barrier.StorePosition(column1[3].xPosition+20,column1[3].yPosition-barrier._sprite.GetSize().y+20);
        barrier.xVelocity=column1[3].xVelocity;
    }

}

void Column::rand_support(int n)
{
    int x=Randomizer::Random(0,1);
    n=n+x;
    if(n%3==0)
    {
        support=true;
    }
    else
    {
        support=false;
    }
}

int World::player_column(void)
{
    for(unsigned int i=0; i<column1.size(); i++)
    {
        if(Game::player1._sprite.GetPosition().x > column1[i].xPosition and
                Game::player1._sprite.GetPosition().x <= column1[i].xPosition+column1[i]._sprite.GetSize().x-27.0/345*column1[i]._sprite.GetSize().x)
        {
            return i;
        }
    }
    return 0;
}
