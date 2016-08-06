#include "class.h"

VisibleGameObject::VisibleGameObject() : _isLoaded(false)
{
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(string filename)
{
    if(_image.LoadFromFile(filename) == false)
    {
        _filename = "";
        _isLoaded = false;
    }
    else
    {
        _filename = filename;
        _sprite.SetImage(_image);
        _isLoaded = true;
    }
}

void VisibleGameObject::Load(Image &load_image)
{
    _image=load_image;                //Must find a alternative for this
    _sprite.SetImage(load_image);
    _isLoaded=true;
}

void VisibleGameObject::Draw(RenderWindow & renderWindow)
{
    if(_isLoaded)
    {
        renderWindow.Draw(_sprite);
    }
}

void VisibleGameObject::SetPosition(float x, float y)
{
    if(_isLoaded)
    {
        _sprite.SetPosition(x,y);
    }
}

void VisibleGameObject::StorePosition(float x, float y)
{
    if(_isLoaded)
    {
        xPosition=x;
        yPosition=y;
    }
}

void VisibleGameObject::SetPosition(void)
{
    if(_isLoaded)
    {
        _sprite.SetPosition(xPosition,yPosition);
    }
}

void VisibleGameObject::SetCenter(float x, float y)
{
    if(_isLoaded)
    {
        _sprite.SetCenter(x, y);
    }
}

void VisibleGameObject::SetSubRect (float x1, float y1, float x2, float y2)
{
    if(_isLoaded)
    {
        _sprite.SetSubRect(IntRect(x1, y1, x2, y2));
    }

}

void VisibleGameObject::DrawPos(RenderWindow & renderWindow)
{
    if(_isLoaded)
    {
        SetPosition();
        renderWindow.Draw(_sprite);
    }
}

void VisibleGameObject::SetScale(float x,float y)
{
    if (_isLoaded)
    {
        _sprite.SetScaleX(x);
        _sprite.SetScaleY(y);
    }
}

void VisibleGameObject::SetRotation(float rad)
{
    if (_isLoaded)
    {
        _sprite.Rotate(rad);
    }
}
