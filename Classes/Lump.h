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
#include "GameMap.h"

USING_NS_CC;
class Lump : public Node {

    
public:
    
    static Lump* createLump(const colorType colorType, const int level, const int h, const int v, Node* pr);
    void move(GridDirection direction);
    
    
private:
    Lump(const colorType colorType, const int level, const int h, const int v);
    ~Lump();
    virtual bool init();

    
    colorType m_ColorType;
    int m_Level;
    int m_Row;
    int m_Col;
    
    
};



#endif /* defined(__MyCppGame__Lump__) */
