//
//  MainMenuScene.h
//  MyCppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#ifndef __MyCppGame__MainMenuScene__
#define __MyCppGame__MainMenuScene__

#include "cocos2d.h"
#include "Global.h"
#include "GameMap.h"

USING_NS_CC;
class MainMenuScene : public LayerGradient
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
    
    //产生新的方块
    void createNewLump(int num);
    
    //重新开始游戏
    void resetGame();
    
private:
    void startGame(Ref* pSender);
    void colorItemCallBack(Ref* pSender);
    void setLumpPosition();
    void setLumpColor();
    
    //menu
    LayerColor* startBg;
    MenuItem* startItem;
    Label* colorTTF;
    
    //game
    LayerColor* gameBg;
    Vector<LayerColor*> vec;
};

#endif /* defined(__MyCppGame__MainMenuScene__) */
