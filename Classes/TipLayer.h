//
//  TipLayer.h
//  MyCppGame
//
//  Created by Jiyao on 15/3/4.
//
//

#ifndef __MyCppGame__TipLayer__
#define __MyCppGame__TipLayer__

#include "cocos2d.h"
#include "Global.h"
#include "MainMenuScene.h"

USING_NS_CC;

enum TipType{
    
    TipType_BackToHome,
    TipType_GameOver,
    
};

class TipLayer : public LayerColor
{
public:
    static LayerColor* createLayer(TipType type, MainMenuScene* mainMenu);
private:
    void okCallBack(Ref* pSender);
    void removeSelf(Ref* pSender);
    bool init(TipType type, MainMenuScene* mainMenu);
    
    TipType m_Type;
    MainMenuScene* m_MainMenu;
    LayerColor* bg;
    
};

#endif /* defined(__MyCppGame__TipLayer__) */
