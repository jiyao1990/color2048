//
//  FirstScene.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/3/7.
//
//

#include "FirstScene.h"
#include "MainMenuScene.h"
#include "Global.h"
#include "Interface.h"

cocos2d::Scene* FirstScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FirstScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool FirstScene::init()
{
    if (!LayerColor::init()) {
        return false;
    }
    
    page = 0;
    //    this->initWithColor(Color4B(66, 66, 66, 255), gWinSize.width, gWinSize.height);
    this->initWithColor(Color4B(45,45,45,255), Color4B(65,65,65,255));
    
    
    Sprite* firstSp1;
    if (gGlobal->isChinese) {
        firstSp1 = Sprite::create("res/first_1.png");
    }else{
        firstSp1 = Sprite::create("res/first_1_en.png");
    }
    this->addChild(firstSp1);
    firstSp1->setPosition(Vec2(gWinSize.width / 2, gWinSize.height / 2));
    firstSp1->setScale(gWinSize.width * 0.9 / firstSp1->getContentSize().width);
    
    
    Sprite* firstSp2;
    if (gGlobal->isChinese) {
        firstSp2 = Sprite::create("res/first_2.png");
    }else{
        firstSp2 = Sprite::create("res/first_2_en.png");
    }
    this->addChild(firstSp2);
    firstSp2->setPosition(Vec2(gWinSize.width * 3 / 2, gWinSize.height / 2));
    firstSp2->setScale(gWinSize.width * 0.9 / firstSp2->getContentSize().width);
    
    
    Sprite* firstSp3;
    if (gGlobal->isChinese) {
        firstSp3 = Sprite::create("res/first_3.png");
    }else{
        firstSp3 = Sprite::create("res/first_3_en.png");
    }
    this->addChild(firstSp3);
    firstSp3->setPosition(Vec2(gWinSize.width * 5 / 2, gWinSize.height / 2));
    firstSp3->setScale(gWinSize.width * 0.9 / firstSp3->getContentSize().width);
    
    auto point1 = Sprite::create("res/first_point.png");
    this->addChild(point1);
    point1->setPosition(Vec2(gWinSize.width / 2 - gWinSize.width / 10, (gWinSize.height / 2 - firstSp2->getContentSize().height * firstSp2->getScaleY() / 2) / 2));
    point1->setScale(gWinSize.width * 0.9 / firstSp1->getContentSize().width);
    
    auto point2 = Sprite::create("res/first_point.png");
    this->addChild(point2);
    point2->setPosition(Vec2(gWinSize.width / 2, (gWinSize.height / 2 - firstSp2->getContentSize().height * firstSp2->getScaleY() / 2) / 2));
    point2->setScale(gWinSize.width * 0.9 / firstSp1->getContentSize().width);
    point2->setOpacity(130);
    
    auto point3 = Sprite::create("res/first_point.png");
    this->addChild(point3);
    point3->setPosition(Vec2(gWinSize.width / 2 + gWinSize.width / 10, (gWinSize.height / 2 - firstSp2->getContentSize().height * firstSp2->getScaleY() / 2) / 2));
    point3->setScale(gWinSize.width * 0.9 / firstSp1->getContentSize().width);
    point3->setOpacity(130);
    
    auto myListener = EventListenerTouchOneByOne::create();
    
    //如果不加入此句消息依旧会向下传递
    myListener->setSwallowTouches(true);
    
    myListener->onTouchBegan = [=](Touch* touch,Event* event)
    {
        return true;
    };
    
    myListener->onTouchMoved = [=](Touch* touch,Event* event)
    {
        //do something
    };
    
    myListener->onTouchEnded = [=](Touch* touch,Event* event)
    {
        Vec2 startPos = touch->getStartLocation();
        Vec2 endPos   = touch->getLocation();
        
        Vec2 difference = endPos - startPos;
        
        //左
        if(difference.x < -20 && abs(difference.y) < abs(difference.x)){
            
            if (page >2 || page < 0) {
                
            }else if(page == 2){
                
                string str = gGlobal->getJsonStr(JsonPair::create("name", Data_LoginCount),
                                                 JsonPair::create("value", "1"),
                                                 nullptr);
                
                gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_SaveData, str);
                //跳转
                Director::getInstance()->replaceScene(TransitionSlideInR::create(0.5f,MainMenuScene::createScene()));
                
            }else{
                page ++;
                firstSp1->runAction(MoveBy::create(0.3, Vec2(- gWinSize.width, 0)));
                firstSp2->runAction(MoveBy::create(0.3, Vec2(- gWinSize.width, 0)));
                firstSp3->runAction(MoveBy::create(0.3, Vec2(- gWinSize.width, 0)));
            }
            
            switch (page) {
                case 0:
                    
                    point1->setOpacity(255);
                    point2->setOpacity(130);
                    point3->setOpacity(130);
                    
                    
                    break;
                    
                case 1:
                    point1->setOpacity(130);
                    point2->setOpacity(255);
                    point3->setOpacity(130);
                    
                    break;
                case 2:
                    
                    point1->setOpacity(130);
                    point2->setOpacity(130);
                    point3->setOpacity(255);
                    
                    break;
            }
            
        }
        //右
        else if(difference.x > 20 && abs(difference.y) < abs(difference.x)){
            
            if (page >= 3 || page <= 0) {
                
            }else{
                page--;
                firstSp1->runAction(MoveBy::create(0.3, Vec2(gWinSize.width, 0)));
                firstSp2->runAction(MoveBy::create(0.3, Vec2(gWinSize.width, 0)));
                firstSp3->runAction(MoveBy::create(0.3, Vec2(gWinSize.width, 0)));
            }
            
            switch (page) {
                case 0:
                    
                    point1->setOpacity(255);
                    point2->setOpacity(130);
                    point3->setOpacity(130);
                    
                    break;
                    
                case 1:
                    point1->setOpacity(130);
                    point2->setOpacity(255);
                    point3->setOpacity(130);
                    
                    
                    break;
                case 2:
                    
                    point1->setOpacity(130);
                    point2->setOpacity(130);
                    point3->setOpacity(255);
                    
                    
                    break;
            }
        }
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(myListener,this);
    
    return true;
}