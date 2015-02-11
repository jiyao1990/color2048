//
//  Lump.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/2/9.
//
//

#include "Lump.h"

Lump::Lump(const colorType colorType, const int level, const int row, const int col)
{
    m_ColorType = colorType;
    m_Level = level;
    m_Row = row;
    m_Col = col;
    
}
Lump::~Lump()
{
    
}
Lump* Lump::createLump(const colorType colorType, const int level, const int row, const int col, Node* pr)
{

    Lump* lump = new Lump(colorType,level,row,col);
    if (lump && lump->init())
    {
        lump->autorelease();
    }else{
        CC_SAFE_DELETE(lump);
    }
    Size size = pr->getContentSize() / MapMaxLength;
    lump->setContentSize(size);
    lump->setAnchorPoint(Vec2(0.5, 0.5));
    
    if (level != -1) {
        LayerColor* tile = LayerColor::create(gGlobal->colorMap[colorType][level], size.width - 10, size.height - 10);
        lump->addChild(tile);
    }else{
        LayerColor* tile = LayerColor::create(Color4B(255, 180, 190, 255), size.width - 5, size.height - 5);
        lump->addChild(tile);
    }

    lump->setPosition(Vec2(lump->getContentSize().width * (0.5 + col), lump->getContentSize().height * (0.5 + row)));
    pr->addChild(lump);
    
    //更改地图数据
    gGameMap->changeMapByCoord(row, col, level);
    
    return lump;
}

bool Lump::init()
{

    return true;
}

void Lump::move(GridDirection direction)
{
    int count = gGameMap->getGridCountByDirection(direction, this->m_Row, this->m_Col);
    switch (direction) {
            
        case GridUp:
        {
            if (this->m_Level != -1) {
                this->runAction(MoveTo::create(0.2f,Vec2(this->getContentSize().width * (0.5 + m_Col), this->getContentSize().height * (0.5 + m_Row + count))));
                m_Row += count;
                
            }
        }
            break;
        case GridDown:
        {
            if (this->m_Level != -1) {
                this->runAction(MoveTo::create(0.2f,Vec2(this->getContentSize().width * (0.5 + m_Col), this->getContentSize().height * (0.5 + m_Row - count))));
                m_Row -= count;
            }
        }
            break;
        case GridLeft:
        {
            if (this->m_Level != -1) {
                this->runAction(MoveTo::create(0.2f,Vec2(this->getContentSize().width * (0.5 + m_Col - count), this->getContentSize().height * (0.5 + m_Row))));
                m_Col -= count;
            }
        }
            break;
        case GridRight:
        {
            if (this->m_Level != -1) {
                this->runAction(MoveTo::create(0.2f,Vec2(this->getContentSize().width * (0.5 + m_Col + count), this->getContentSize().height * (0.5 + m_Row))));
                m_Col += count;
            }
        }
            break;
    }
}