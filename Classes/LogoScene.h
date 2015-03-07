//
//  LogoScene.h
//  MyCppGame
//
//  Created by Jiyao on 15/3/8.
//
//

#ifndef __MyCppGame__LogoScene__
#define __MyCppGame__LogoScene__

#include "cocos2d.h"

USING_NS_CC;
class LogoScene : public LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LogoScene);
    
private:
    
    void nextScene(float dt);
    
};

#endif /* defined(__MyCppGame__LogoScene__) */
