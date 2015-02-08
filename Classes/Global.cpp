//
//  Global.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#include "Global.h"

Global* Global::_instance = NULL;

Color4B Global::colorMap[colorType_Size][maxLevel] ={
    
    {
        Color4B(240, 255, 200, 255),
        Color4B(180, 245, 180, 255),
        Color4B(150, 220, 120, 255),
        Color4B(110, 200, 100, 255),
        Color4B(80,  175, 70,  255),
        Color4B(40,  145, 50,  255),
        Color4B(20,  115, 20,  255),
        Color4B(12,  90,  14,  255),
        Color4B(6,   60,  7,   255),
        Color4B(0,   30,  0,   255),
        Color4B(0,   0,   0,   255),
    },
    {Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255)},
    {Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255),Color4B(0, 0, 0, 255)},
};

Global::Global()
{
    _colorType = colorType_green;
}

Global::~Global()
{
    
}

Global* Global::getInstance()
{
    
    if (!_instance) {
        _instance = new Global();
    }
    
    return _instance;
}