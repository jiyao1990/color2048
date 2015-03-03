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
#include "Interface.h"

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
    
    startBg = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][2], gWinSize.width * 2 / 3, gWinSize.width * 2 / 3);
    this->addChild(startBg);
    startBg->setPosition(Vec2(gWinSize.width / 2 - startBg->getContentSize().width / 2, (gWinSize.height - startBg->getContentSize().height) / 2 + (gWinSize.height - startBg->getContentSize().height) / 5));
    
    auto startTTF = Label::createWithSystemFont("开始", "黑体", startBg->getContentSize().width / 7);
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
    
    
    auto menuDownBg = LayerColor::create(Color4B(44, 44, 44, 255), gWinSize.width, (gWinSize.height - startBg->getContentSize().height) / 5);
    this->addChild(menuDownBg);
    
    colorTTF = Label::createWithSystemFont("更换颜色", "Arial", menuDownBg->getContentSize().height * 2 / 5);
//    colorTTF->enableOutline(gGlobal->colorMap[gGlobal->_colorType][2]);
    colorTTF->setTextColor(gGlobal->colorMap[gGlobal->_colorType][0]);
    menuDownBg->addChild(colorTTF);
    colorTTF->setPosition(Vec2(menuDownBg->getContentSize().width / 2, menuDownBg->getContentSize().height / 2));
    
    auto colorItem = MenuItem::create(CC_CALLBACK_1(MainMenuScene::colorItemCallBack, this));
    colorItem->setContentSize(menuDownBg->getContentSize());
    colorItem->setPosition(menuDownBg->getContentSize() / 2);
    
    auto menuDown = Menu::create(colorItem, NULL);
    menuDown->setPosition(Vec2(0, 0));
    menuDownBg->addChild(menuDown);
    
    
    
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
    
    gameBg->runAction(Sequence::create(DelayTime::create(0.4f),Show::create(),MoveTo::create(0.4f, Vec2(gameBg->getPositionX(), (gWinSize.height - gameBg->getContentSize().height) / 2 + (gWinSize.height - gameBg->getContentSize().height) / 5) ), NULL));

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
            
            setLumpPosition();
            setLumpColor();
            createNewLump(gGameMap->changeMapByDirection(GridUp));
            
            
            
        }
        //下
        else if(difference.y < -20 && abs(difference.x) < abs(difference.y)){
            setLumpPosition();
            setLumpColor();
            createNewLump(gGameMap->changeMapByDirection(GridDown));
            
        }
        //左
        else if(difference.x < -20 && abs(difference.y) < abs(difference.x)){
            setLumpPosition();
            setLumpColor();
            createNewLump(gGameMap->changeMapByDirection(GridLeft));
            
            
        }
        //右
        else if(difference.x > 20 && abs(difference.y) < abs(difference.x)){
            setLumpPosition();
            setLumpColor();
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
        while (!gGameMap->isFull()) {
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
    
    if (gGameMap->isFail()) {
        
//        resetGame();
        log("fail");
        
    }

    
}

void MainMenuScene::colorItemCallBack(Ref* pSender)
{
//    gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ShowAd, "");
    if (gGlobal->_colorType < colorType_Size - 1) {
        gGlobal->_colorType = (colorType)(gGlobal->_colorType + 1);
    }else{
        gGlobal->_colorType = colorType_green;
    }
    
    startBg->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][2]));
    colorTTF->setTextColor(gGlobal->colorMap[gGlobal->_colorType][0]);

    setLumpColor();
}


void MainMenuScene::setLumpPosition()
{
    
    for (map< int, Node* >::iterator it = gGlobal->lumpMap.begin(); it != gGlobal->lumpMap.end(); it ++) {
        Lump* lump = (Lump *)it->second;
        lump->stopAllActions();
        lump->setScale(1.f);
        lump->setPosition(Vec2(lump->getContentSize().width * (0.5 + lump->getCol()), lump->getContentSize().height * (0.5 + lump->getRow())));
        
    }
}

void MainMenuScene::setLumpColor()
{
    
    for (map< int, Node* >::iterator it = gGlobal->lumpMap.begin(); it != gGlobal->lumpMap.end(); it ++) {
        Lump* lump = (Lump *)it->second;
        lump->stopAllActions();
        lump->getChildByTag(Tag_Tile)->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][lump->getLevel() - 1]));
        
    }
}

void MainMenuScene::resetGame()
{
    gGameMap->resetMapData();
    for (map< int, Node* >::iterator it = gGlobal->lumpMap.begin(); it != gGlobal->lumpMap.end(); it ++) {
        Lump* lump = (Lump *)it->second;
        lump->stopAllActions();
        lump->removeFromParent();
    }
    gGlobal->lumpMap.clear();
    createNewLump(2);
}



