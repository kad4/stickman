
#pragma once

class VisibleGameObject
{
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();

    virtual void Load(string filename);
    virtual void Draw(RenderWindow & window);

    virtual void SetPosition(float x, float y);

private:
    Sprite  _sprite;
    Image _image;
    string _filename;
    bool _isLoaded;
};
