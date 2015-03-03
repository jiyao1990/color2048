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
        Color4B(25,  115, 25,  255),
        Color4B(15,  90,  15,  255),
        Color4B(10,  60,  10,  255),
        Color4B(0,   30,  0,   255),
        Color4B(0,   0,   0,   255),
    },
    {
        Color4B(143, 244, 255, 255),
        Color4B(100, 205, 225, 255),
        Color4B(75,  172, 205, 255),
        Color4B(65,  150, 175, 255),
        Color4B(55,  130, 155, 255),
        Color4B(46,  106, 125, 255),
        Color4B(25,  80,  105, 255),
        Color4B(27,  60,  74,  255),
        Color4B(10,  40,  55,  255),
        Color4B(0,   10,  30,  255),
        Color4B(0,   0,   0,   255)
    },
    {
        Color4B(254, 190, 191, 255),
        Color4B(252, 119, 142, 255),
        Color4B(240, 80,  100, 255),
        Color4B(220, 60,  70,  255),
        Color4B(200, 40,  50,  255),
        Color4B(187, 17,  24,  255),
        Color4B(155, 15,  20,  255),
        Color4B(113, 12,  15,  255),
        Color4B(55,  10,  10,  255),
        Color4B(30,  0,   0,   255),
        Color4B(0,   0,   0,   255)},
};

Global::Global()
{
    _colorType = colorType_green;
    currentID = 0;
    lumpMap.clear();
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