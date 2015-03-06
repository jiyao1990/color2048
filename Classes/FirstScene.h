//
//  FirstScene.h
//  MyCppGame
//
//  Created by Jiyao on 15/3/7.
//
//

#ifndef __MyCppGame__FirstScene__
#define __MyCppGame__FirstScene__

#include "cocos2d.h"
#include "Global.h"
#include "GameMap.h"

USING_NS_CC;
class FirstScene : public LayerGradient
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(FirstScene);
    
private:
    int page;
    
};

#endif /* defined(__MyCppGame__FirstScene__) */
