//
//  LogoScene.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/3/8.
//
//

#include "LogoScene.h"
#include "FirstScene.h"
#include "MainMenuScene.h"
#include "Interface.h"

cocos2d::Scene* LogoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LogoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool LogoScene::init()
{
    if (!LayerColor::init()) {
        return false;
    }
    this->initWithColor(Color4B(10, 6, 10, 255));
    auto bg = Sprite::create("res/loading.png");
    bg->setPosition(Vec2(gWinSize.width / 2, gWinSize.height / 2));
    float scaleX = gWinSize.width / bg->getContentSize().width;
    float scaleY = gWinSize.height / bg->getContentSize().width;
    if (scaleX < scaleY) {
        bg->setScale(scaleX);
    }else{
        bg->setScale(scaleY);
    }
    
    this->addChild(bg);
  
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(LogoScene::nextScene), 1.f);
    return true;
}

void LogoScene::nextScene(float dt)
{
    string loginCountStr = gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ReadData, Data_LoginCount);
    int loginCount;
    if (loginCountStr == "") {
        loginCount = 0;
    }else{
        loginCount = atoi(loginCountStr.c_str());
    }
    Scene* scene;
    if (loginCount == 0) {
        scene = FirstScene::createScene();
    }else{
        loginCount += 1;
        CCLOG("打开次数：%d",loginCount);
        string str = gGlobal->getJsonStr(JsonPair::create("name", Data_LoginCount),
                                         JsonPair::create("value", toString(loginCount)),
                                         nullptr);
        
        gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_SaveData, str);
        scene = MainMenuScene::createScene();
    }
    
    Director::getInstance()->replaceScene(TransitionFade::create(0.2f, scene));
}