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
    
    
    
//    for (int i = 0; i < 4;  i ++) {
//        int level;
//        int row;
//        int col;
//        while (true) {
//            level =  random(0, 1);
//            row =  random(0, 3);
//            col = random(0, 3);
//            log("%d,%d,%d",level,row,col);
//            if (!gGameMap->isExist(row, col)) {
//                break;
//            }
//            
//        }
//        
//        Lump* m_lump = Lump::createLump(gGlobal->_colorType, level, row, col, gameBg);
//        gGlobal->lumpVec.pushBack(m_lump);
//    }
    
    createNewLump(2);

    return true;
}

void MainMenuScene::startGame(Ref* pSender)
{
//    startBg->runAction(TintTo::create(0.5f, startBg->getColor().r / 1.5, startBg->getColor().g / 1.5, startBg->getColor().b / 1.5));
    startItem->setEnabled(false);
    startBg->runAction(MoveTo::create(0.4f, Vec2(startBg->getPositionX() , gWinSize.height)));
    
    gameBg->runAction(Sequence::create(DelayTime::create(0.4f),Show::create(),MoveTo::create(0.4f, Vec2(gameBg->getPositionX(),gWinSize.height / 2 - gameBg->getContentSize().height * 0.35  )), NULL));

    auto dispatcher = Director::getInstance()->getEventDispatcher();
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
        
        //上
        if (difference.y > 20 && abs(difference.x) < abs(difference.y)) {
//            for (int i = 0; i < gGlobal->lumpVec.size(); i++) {
//                ((Lump*)gGlobal->lumpVec.at(i))->move(GridUp);
//            }
            //地图数据变化
//            gGameMap->changeMapByDirection(GridUp);
            createNewLump(gGameMap->changeMapByDirection(GridUp));
            
            
            
        }
        //下
        else if(difference.y < -20 && abs(difference.x) < abs(difference.y)){
//            for (int i = 0; i < gGlobal->lumpVec.size(); i++) {
//                ((Lump*)gGlobal->lumpVec.at(i))->move(GridDown);
//            }
//            gGameMap->changeMapByDirection(GridDown);
            createNewLump(gGameMap->changeMapByDirection(GridDown));
            
        }
        //左
        else if(difference.x < -20 && abs(difference.y) < abs(difference.x)){
//            for (int i = 0; i < gGlobal->lumpVec.size(); i++) {
//                ((Lump*)gGlobal->lumpVec.at(i))->move(GridLeft);
//            }
            
//            gGameMap->changeMapByDirection(GridLeft);
            createNewLump(gGameMap->changeMapByDirection(GridLeft));
            
            
        }
        //右
        else if(difference.x > 20 && abs(difference.y) < abs(difference.x)){
//            for (int i = 0; i < gGlobal->lumpVec.size(); i++) {
//                ((Lump*)gGlobal->lumpVec.at(i))->move(GridRight);
//            }
//            gGameMap->changeMapByDirection(GridRight);
            createNewLump(gGameMap->changeMapByDirection(GridRight));
            
        }
    };
    
    dispatcher->addEventListenerWithSceneGraphPriority(myListener,this);
}

void MainMenuScene::createNewLump(int num)
{
    int level;
    int row;
    int col;
    //一次出现num个
    for (int i = 0 ; i < num ; i ++) {
        while (true) {
            level =  random(1, 2);
            row =  random(0, 3);
            col = random(0, 3);
            log("%d,%d,%d",level,row,col);
            if (!gGameMap->isExist(row, col)) {
                gGlobal->currentID += 1;
                gGameMap->changeMapByCoord(row, col, level, gGlobal->currentID);
                Lump* m_lump = Lump::createLump(gGlobal->_colorType, level, row, col, gGlobal->currentID, gameBg);
                gGlobal->lumpMap.insert(make_pair(gGlobal->currentID, m_lump));
                break;
                
            }
            
        }
    }

    
}




