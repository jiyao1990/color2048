//
//  Lump.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/2/9.
//
//

#include "Lump.h"

Lump::Lump(const colorType colorType, const int level, const int row, const int col, const int ID)
{
    m_ColorType = colorType;
    m_Level = level;
    m_Row = row;
    m_Col = col;
    m_ID = ID;
}
Lump::~Lump()
{
    
}
Lump* Lump::createLump(const colorType colorType, const int level, const int row, const int col, const int ID, Node* pr)
{

    Lump* lump = new Lump(colorType,level,row,col,ID);
    if (lump && lump->init())
    {
        lump->autorelease();
    }else{
        CC_SAFE_DELETE(lump);
    }
    Size size = pr->getContentSize() / MapMaxLength;
    lump->setContentSize(size);
    lump->setAnchorPoint(Vec2(0.5, 0.5));

    LayerColor* tile = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][level - 1], size.width, size.height);
    lump->addChild(tile);
    tile->setTag(Tag_Tile);

    lump->setPosition(Vec2(lump->getContentSize().width * (0.5 + col), lump->getContentSize().height * (0.5 + row)));
    pr->addChild(lump);
    lump->setScale(0.f);
    lump->runAction(Sequence::create(CCDelayTime::create(0.2f), Spawn::create(EaseBackOut::create(ScaleTo::create(0.1f, 1)), FadeOut::create(0.1f), nullptr), nullptr));
    
    lump->setLocalZOrder(1);
    //更改地图数据
//    gGameMap->changeMapByCoord(row, col, level);
    
    return lump;
}

bool Lump::init()
{

    return true;
}

void Lump::move(GridDirection direction, int step, MyActionType actionType)
{
    ActionInterval* move = NULL;
    switch (direction) {
            
        case GridUp:
        {
            move = MoveTo::create(0.1f,Vec2(this->getContentSize().width * (0.5 + m_Col), this->getContentSize().height * (0.5 + m_Row + step)));
            m_Row += step;
        }
            break;
        case GridDown:
        {
            move = MoveTo::create(0.1f,Vec2(this->getContentSize().width * (0.5 + m_Col), this->getContentSize().height * (0.5 + m_Row - step)));
            m_Row -= step;
        }
            break;
        case GridLeft:
        {
            move = MoveTo::create(0.1f,Vec2(this->getContentSize().width * (0.5 + m_Col - step), this->getContentSize().height * (0.5 + m_Row)));
            m_Col -= step;
        }
            break;
        case GridRight:
        {
            move = MoveTo::create(0.1f,Vec2(this->getContentSize().width * (0.5 + m_Col + step), this->getContentSize().height * (0.5 + m_Row)));
            m_Col += step;
        }
            break;
    }

    doAction(move, actionType);
    
}

void Lump::changeColor(int level)
{
    if (m_Level != level) {
        m_Level = level;
    }else{
        return;
    }
    this->getChildByTag(Tag_Tile)->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][m_Level - 1].r, gGlobal->colorMap[gGlobal->_colorType][m_Level - 1].g, gGlobal->colorMap[gGlobal->_colorType][m_Level - 1].b));
    
}

void Lump::doAction(ActionInterval *action , MyActionType actionType)
{
    switch (actionType) {
        case MyActionType_Null:
            this->runAction(action);
            break;
            
        case MyActionType_Fade:
            this->setLocalZOrder(0);
            this->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Lump::removeSelf, this)), nullptr));
            break;
            
        case MyActionType_LvUp:
            this->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Lump::changeColor, this, m_Level + 1)), nullptr));
            break;
    }
}

void Lump::removeSelf()
{
    this->removeFromParent();
}

int Lump::getCol()
{
    return m_Col;
}

int Lump::getRow()
{
    return m_Row;
}



