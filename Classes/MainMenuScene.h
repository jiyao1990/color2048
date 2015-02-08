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

USING_NS_CC;
class MainMenuScene : public cocos2d::LayerGradient
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
    
private:
    void startGame(Ref* pSender);
    
    //menu
    LayerColor* startBg;
    MenuItem* startItem;
    
    //game
    LayerColor* gameBg;
    Vector<LayerColor*> vec;
};

#endif /* defined(__MyCppGame__MainMenuScene__) */
