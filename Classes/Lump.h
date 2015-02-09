//
//  Lump.h
//  MyCppGame
//
//  Created by Jiyao on 15/2/9.
//
//

#ifndef __MyCppGame__Lump__
#define __MyCppGame__Lump__

#include "cocos2d.h"
#include "Global.h"

enum MoveDirection{
    
    MoveStop = 0,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    
};

USING_NS_CC;
class Lump : public Node {

    
public:
    
    static Lump* createLump(const colorType colorType, const int level, const int h, const int r, Node* pr);
    
    
    
private:
    Lump(const colorType colorType, const int level, const int h, const int r);
    ~Lump();
    virtual bool init();

    
    colorType m_ColorType;
    MoveDirection m_MoveDirection;
    int m_Level;
    int m_Hor;
    int m_Row;
    
    
};



#endif /* defined(__MyCppGame__Lump__) */
