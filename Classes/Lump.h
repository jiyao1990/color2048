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

#define Tag_Tile 1001

USING_NS_CC;
enum MyActionType {
    MyActionType_Null,
    MyActionType_LvUp,
    MyActionType_Fade,
};

class Lump : public Node {

    
public:
    
    static Lump* createLump(const colorType colorType, const int level, const int h, const int v, const int ID, Node* pr);
    //移动---参数:方向,步数,动作
    void move(GridDirection direction, int step, MyActionType actionType);
    //升级
    void changeColor(int level);
    
    CC_SYNTHESIZE(int , m_ID, ID);
private:
    Lump(const colorType colorType, const int level, const int h, const int v, const int ID);
    ~Lump();
    virtual bool init();
    void doAction(ActionInterval *action , MyActionType actionType);
    //消失
    void removeSelf();
    
    colorType m_ColorType;
    int m_Level;
    int m_Row;
    int m_Col;
    
    
};



#endif /* defined(__MyCppGame__Lump__) */
