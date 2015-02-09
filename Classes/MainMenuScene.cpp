//
//  MainMenuScene.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#include "MainMenuScene.h"
#include "Global.h"
#include "Lump.h"

USING_NS_CC;

// there's no 'id' in cpp, so we recommend returning the class instance pointer
cocos2d::Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool MainMenuScene::init()
{
    if (!LayerColor::init()) {
        return false;
    }
    
//    this->initWithColor(Color4B(66, 66, 66, 255), gWinSize.width, gWinSize.height);
    this->initWithColor(Color4B(45,45,45,255), Color4B(65,65,65,255));
    
    startBg = LayerColor::create(Color4B(163, 230, 125, 255), gWinSize.width * 2 / 3, gWinSize.width * 2 / 3);
    this->addChild(startBg);
    startBg->setPosition(Vec2(gWinSize.width / 2 - startBg->getContentSize().width / 2, gWinSize.height * 0.45));
    
    auto startTTF = Label::createWithSystemFont("玩", "黑体", startBg->getContentSize().width / 7);
    startTTF->setTextColor(Color4B(44, 44, 44, 255));
    startBg->addChild(startTTF);
    startTTF->setPosition(Vec2(startBg->getContentSize().width / 2, startBg->getContentSize().height / 2));
    
    
    startItem = MenuItem::create(CC_CALLBACK_1(MainMenuScene::startGame, this));
    startItem->setContentSize(startBg->getContentSize());
    startItem->setPosition(startBg->getContentSize() / 2);
    
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(0, 0));
    startBg->addChild(menu);
    
    gameBg = LayerColor::create(Color4B(255, 255, 255, 50), gWinSize.width * 9 / 10, gWinSize.width * 9 / 10);
    this->addChild(gameBg);
    gameBg->setPosition(Vec2(gWinSize.width / 2 - gameBg->getContentSize().width / 2, gWinSize.height));
    gameBg->setVisible(false);
    
    
//    for (int i = 0 ; i < TileNum * TileNum; i ++) {
//        
//        float rand = random(0, 4);
////        int index = (int) rand;
//        int index = i;
//        if (index >= maxLevel) {
//            index = i - maxLevel;
//        }
//        log("index:%d",index);
//        
//        LayerColor* tile = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][index], gameBg->getContentSize().width / (TileNum), gameBg->getContentSize().height / (TileNum));
//        int h = i / TileNum;
//        int r = i % TileNum;
//        
//        gameBg->addChild(tile);
////        float space = gameBg->getContentSize().width / (TileNum + 1) / (TileNum + 1);
//        float space = 0;
//        tile->setPosition(Vec2(space + (tile->getContentSize().width + space) * h, space + (tile->getContentSize().height + space) * r));
//        
//    }
    
    int level =  random(0, 4);
    int h =  random(0, 3);
    int r = random(0, 3);
    log("%d,%d,%d",level,h,r);
    Lump* m_lump = Lump::createLump(gGlobal->_colorType, level, h, r, gameBg);
    gGlobal->lumpVec.pushBack(m_lump);
    
    return true;
}

void MainMenuScene::startGame(Ref* pSender)
{
//    startBg->runAction(TintTo::create(0.5f, startBg->getColor().r / 1.5, startBg->getColor().g / 1.5, startBg->getColor().b / 1.5));
    startItem->setEnabled(false);
    startBg->runAction(MoveTo::create(0.4f, Vec2(startBg->getPositionX() , gWinSize.height)));
    
    gameBg->runAction(Sequence::create(DelayTime::create(0.4f),Show::create(),MoveTo::create(0.4f, Vec2(gameBg->getPositionX(),gWinSize.height / 2 - gameBg->getContentSize().height * 0.35  )), NULL));
}





