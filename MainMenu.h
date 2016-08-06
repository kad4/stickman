#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

class MainMenu
{

public:
    enum MenuResult { Nothing, Exit, Play };

    struct MenuItem
    {
public:
        Rect<int> rect;
        MenuResult action;
    };
    MenuResult Show(RenderWindow& window);

private:
    MenuResult GetMenuResponse(RenderWindow& window);
    MenuResult HandleClick(int x, int y);

    list<MenuItem> _menuItems;
};

