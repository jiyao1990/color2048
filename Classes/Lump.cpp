//
//  Lump.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/2/9.
//
//

#include "Lump.h"

Lump::Lump(const colorType colorType, const int level, const int h, const int r)
{
    m_ColorType = colorType;
    m_Level = level;
    m_Hor = h;
    m_Row = r;
    
    m_MoveDirection = MoveStop;
}
Lump::~Lump()
{
    
}
Lump* Lump::createLump(const colorType colorType, const int level, const int h, const int r, Node* pr)
{

    Lump* lump = new Lump(colorType,level,h,r);
    if (lump && lump->init())
    {
        lump->autorelease();
    }else{
        CC_SAFE_DELETE(lump);
    }
    Size size = pr->getContentSize() / TileNum;
    lump->setContentSize(size);
    lump->setAnchorPoint(Vec2(0.5, 0.5));
    
    LayerColor* tile = LayerColor::create(gGlobal->colorMap[colorType][level], size.width, size.height);
    lump->addChild(tile);
    
    lump->setPosition(Vec2(tile->getContentSize().width * (0.5 + h), tile->getContentSize().height * (0.5 + r)));
    
    pr->addChild(lump);
    
    return lump;
}

bool Lump::init()
{

    return true;
}