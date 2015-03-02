//
//  Global.h
//  MyCppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#ifndef __MyCppGame__Global__
#define __MyCppGame__Global__

#include "cocos2d.h"
#include <iostream>

#define gWinSize     Director::getInstance()->getWinSize()
#define gGlobal      Global::getInstance()
#define maxLevel     11

USING_NS_CC;
using namespace std;

enum colorType{
    colorType_green = 0,
    colorType_blue,
    colorType_red,
    colorType_Size,
};

class Global : public Node{
    
    Global();
    ~Global();
    
public:

    static Global* getInstance();
    static Color4B colorMap[colorType_Size][maxLevel];
    
    colorType _colorType;
    map< int, Node* > lumpMap;
    
    int currentID;
    
private:
    
    
    //------variable----------
    static Global* _instance;
    
    
};

#endif /* defined(__MyCppGame__Global__) */
