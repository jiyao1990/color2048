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
#include "TipLayer.h"

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
    gameOverCount = 0;
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
    
    auto menu = Menu::create(startItem,nullptr);
    menu->setPosition(Vec2(0, 0));
    startBg->addChild(menu);
    
    gameBg = LayerColor::create(Color4B(255, 255, 255, 50), gWinSize.width * 9 / 10, gWinSize.width * 9 / 10);
    this->addChild(gameBg);
    gameBg->setPosition(Vec2(gWinSize.width / 2 - gameBg->getContentSize().width / 2, gWinSize.height));
    gameBg->setVisible(false);
    
    
    //分数
    char buffer[64];
    sprintf(buffer,"当前得分:%d",gGlobal->score);
    scoreTTF = Label::createWithSystemFont(buffer, "黑体", gameBg->getContentSize().width / 14);
    scoreTTF->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
    gameBg->addChild(scoreTTF);
    scoreTTF->setPosition(Vec2(gameBg->getContentSize().width / 2, gameBg->getContentSize().height + scoreTTF->getContentSize().height / 2 + gameBg->getContentSize().width / 12));
    scoreTTF->enableShadow();
    
    auto menuDownBg = LayerColor::create(Color4B(44, 44, 44, 255), gWinSize.width, (gWinSize.height - startBg->getContentSize().height) / 5);
    this->addChild(menuDownBg);
    
    btn_change = MenuItemImage::create("res/change.png", "res/change.png", CC_CALLBACK_1(MainMenuScene::colorItemCallBack, this));
    btn_change->setPosition(menuDownBg->getContentSize() / 2);
    btn_change->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
    
    btn_home = MenuItemImage::create("res/home.png", "res/home.png", CC_CALLBACK_1(MainMenuScene::homeCallBack, this));
    btn_home->setPosition(Vec2(menuDownBg->getContentSize().width  / 4, menuDownBg->getContentSize().height / 2));
    btn_home->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
    btn_home->setEnabled(false);
    btn_home->setOpacity(0);
    
    btn_weibo = MenuItemImage::create("res/weibo.png", "res/weibo.png", CC_CALLBACK_1(MainMenuScene::shareCallBack, this));
    btn_weibo->setPosition(Vec2(menuDownBg->getContentSize().width * 3 / 4, menuDownBg->getContentSize().height / 2));
    btn_weibo->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
    btn_weibo->setEnabled(false);
    btn_weibo->setOpacity(0);
    
    auto menuDown = Menu::create(btn_change, btn_home, btn_weibo,nullptr);
    menuDown->setPosition(Vec2(0, 0));
    menuDownBg->addChild(menuDown);
    
    auto highScoreBg = LayerColor::create(Color4B(44, 44, 44, 180), gWinSize.width, gameBg->getContentSize().width / 10);
    this->addChild(highScoreBg);
    highScoreBg->setPosition(Vec2(0, menuDownBg->getContentSize().height));
    
    
    highScoreTTF = Label::createWithSystemFont("您的最高得分:" + gGlobal->highScore, "黑体", gameBg->getContentSize().width / 15);
    highScoreTTF->setPosition(highScoreBg->getContentSize()/2);
    highScoreTTF->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
    highScoreBg->addChild(highScoreTTF);
    highScoreTTF->enableShadow();
    
    return true;
}

void MainMenuScene::startGame(Ref* pSender)
{
    
    resetData();
    
    btn_change->setEnabled(false);
    btn_change->runAction(Sequence::create(FadeOut::create(0.2),Hide::create(),nullptr));
    
    btn_weibo->setEnabled(true);
    btn_weibo->runAction(Sequence::create(Show::create(),FadeIn::create(0.2),nullptr));
    
    btn_home->setEnabled(true);
    btn_home->runAction(Sequence::create(Show::create(),FadeIn::create(0.2),nullptr));
    
    
    
    
    startItem->setEnabled(false);
    startBg->runAction(Sequence::create(MoveTo::create(0.4f, Vec2(startBg->getPositionX() , gWinSize.height)),Hide::create(),nullptr));
    
    gameBg->runAction(Sequence::create(DelayTime::create(0.4f),Show::create(),MoveTo::create(0.4f, Vec2(gameBg->getPositionX(), (gWinSize.height - gameBg->getContentSize().height) / 2 + gameBg->getContentSize().width / 12) ),nullptr));

    
    myListener = EventListenerTouchOneByOne::create();
    
    //如果不加入此句消息依旧会向下传递
    myListener->setSwallowTouches(true);
    
    myListener->onTouchBegan = [=](Touch* touch,Event* event)
    {
        if (gGameMap->isWin) {
            return false;
        }
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
        
        char buffer[64];
        sprintf(buffer,"当前得分:%d",gGlobal->score);
        scoreTTF->setString(buffer);
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(myListener,this);
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
    
    if (gGameMap->isFail() && !this->getActionByTag(1000)) {
        gGlobal->saveScreenshot(this, screenShotImageName);
        if (atoi(gGlobal->highScore.c_str()) < gGlobal->score) {
            gGlobal->highScore = toString(gGlobal->score);
            highScoreTTF->setString("您的最高得分:" + gGlobal->highScore);
            
            string str = gGlobal->getJsonStr(JsonPair::create("name", Data_HighScore),
                                             JsonPair::create("value", gGlobal->highScore),
                                             nullptr);
            
            gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_SaveData, str);
        }
        
        ActionInterval* action = Sequence::create(DelayTime::create(2.f),CallFunc::create(CC_CALLBACK_0(MainMenuScene::gameOver, this)),nullptr);
        action->setTag(1000);
        this->runAction(action);
        
        log("fail");
        
    }
    
    if (gGameMap->isWin && !this->getActionByTag(1000)) {
        gGlobal->saveScreenshot(this, screenShotImageName);
        if (atoi(gGlobal->highScore.c_str()) < gGlobal->score) {
            gGlobal->highScore = toString(gGlobal->score);
            highScoreTTF->setString("您的最高得分:" + gGlobal->highScore);
            
            string str = gGlobal->getJsonStr(JsonPair::create("name", Data_HighScore),
                                             JsonPair::create("value", gGlobal->highScore),
                                             nullptr);
            
            gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_SaveData, str);
        }
        
        ActionInterval* action = Sequence::create(DelayTime::create(2.f),CallFunc::create(CC_CALLBACK_0(MainMenuScene::gameWin, this)),nullptr);
        action->setTag(1000);
        this->runAction(action);
        
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
    startBg->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][2].r, gGlobal->colorMap[gGlobal->_colorType][2].g, gGlobal->colorMap[gGlobal->_colorType][2].b));
    btn_change->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][0].r, gGlobal->colorMap[gGlobal->_colorType][0].g, gGlobal->colorMap[gGlobal->_colorType][0].b));
    btn_home->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][0].r, gGlobal->colorMap[gGlobal->_colorType][0].g, gGlobal->colorMap[gGlobal->_colorType][0].b));
    btn_weibo->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][0].r, gGlobal->colorMap[gGlobal->_colorType][0].g, gGlobal->colorMap[gGlobal->_colorType][0].b));
    scoreTTF->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][0].r, gGlobal->colorMap[gGlobal->_colorType][0].g, gGlobal->colorMap[gGlobal->_colorType][0].b));
    highScoreTTF->runAction(TintTo::create(0.2f, gGlobal->colorMap[gGlobal->_colorType][0].r, gGlobal->colorMap[gGlobal->_colorType][0].g, gGlobal->colorMap[gGlobal->_colorType][0].b));
    
//    startBg->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][2]));
//    btn_change->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
//    btn_home->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
//    btn_weibo->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
//    scoreTTF->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
//    highScoreTTF->setColor(Color3B(gGlobal->colorMap[gGlobal->_colorType][0]));
    setLumpColor();
}

void MainMenuScene::homeCallBack(Ref* pSender)
{
    this->addChild(TipLayer::createLayer(TipType_BackToHome, this));
}

void MainMenuScene::backHome()
{
    btn_change->setEnabled(true);
    btn_change->runAction(Sequence::create(Show::create(),FadeIn::create(0.2),nullptr));
    
    btn_weibo->setEnabled(false);
    btn_weibo->runAction(Sequence::create(FadeOut::create(0.2),Hide::create(),nullptr));
    
    btn_home->setEnabled(false);
    btn_home->runAction(Sequence::create(FadeOut::create(0.2),Hide::create(),nullptr));
    
    startItem->setEnabled(true);
    startBg->runAction(Sequence::create(DelayTime::create(0.4f),Show::create(),MoveTo::create(0.4f, Vec2(gWinSize.width / 2 - startBg->getContentSize().width / 2, (gWinSize.height - startBg->getContentSize().height) / 2 + (gWinSize.height - startBg->getContentSize().height) / 5)),nullptr));
    
    gameBg->runAction(Sequence::create(MoveTo::create(0.4f, Vec2(gWinSize.width / 2 - gameBg->getContentSize().width / 2, gWinSize.height)),Hide::create(),nullptr));
    
    Director::getInstance()->getEventDispatcher()->removeEventListener(myListener);
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
    gameBg->runAction(Sequence::create(
                                       MoveTo::create(0.2f, Vec2(gWinSize.width / 2 - gameBg->getContentSize().width / 2, gWinSize.height)),
                                       CallFunc::create(CC_CALLBACK_0(MainMenuScene::resetData, this)),
                                       MoveTo::create(0.2f, Vec2(gameBg->getPositionX(), (gWinSize.height - gameBg->getContentSize().height) / 2 + gameBg->getContentSize().width / 12)),
                                       nullptr));
    
 
}

void MainMenuScene::resetData()
{
    gGameMap->resetMapData();
    for (map< int, Node* >::iterator it = gGlobal->lumpMap.begin(); it != gGlobal->lumpMap.end(); it ++) {
        Lump* lump = (Lump *)it->second;
        lump->stopAllActions();
        lump->removeFromParent();
    }
    gGlobal->lumpMap.clear();
    createNewLump(2);
    
    gGlobal->score = 0;
    char buffer[64];
    sprintf(buffer,"当前得分:%d",gGlobal->score);
    scoreTTF->setString(buffer);
}

void MainMenuScene::gameOver()
{
    gameOverCount ++;
    this->addChild(TipLayer::createLayer(TipType_GameOver, this));
    this->addChild(TipLayer::createLayer(TipType_Tips, this));
    if (gameOverCount % 3 == 1) {
        gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ShowAd, "");
    }
}

void MainMenuScene::gameWin()
{
    this->addChild(TipLayer::createLayer(TipType_GameWin, this));
    this->addChild(TipLayer::createLayer(TipType_Tips, this));
}

void MainMenuScene::shareCallBack(Ref* pSender)
{
    btn_weibo->setEnabled(false);
    string text = "我的最高得分为" + gGlobal->highScore + "分,优雅的融合~可以获取到专属你玩到的秘密~快来一起玩吧~via 方块密码:2048";
    auto callback = [=](const std::string& fullPath){
        
        CCLOG("Image saved %s", fullPath.c_str());
        CCLOG("%s",text.c_str());
        
        string str = gGlobal->getJsonStr(JsonPair::create("imagePath", fullPath),
                                         JsonPair::create("shareText", text),
                                         nullptr);
        
        gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_Share, str);
        
        btn_weibo->setEnabled(true);
    };
    gGlobal->saveScreenshot(this, screenShotImageName, callback);
}

//分享
void MainMenuScene::share(string text)
{
    auto fullPath = FileUtils::getInstance()->getWritablePath() + screenShotImageName;
    
    CCLOG("Image saved %s", fullPath.c_str());
    CCLOG("%s",text.c_str());
    
    string str = gGlobal->getJsonStr(JsonPair::create("imagePath", fullPath),
                                     JsonPair::create("shareText", text),
                                     nullptr);
    
    gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_Share, str);
    
}

void MainMenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ShowDialog, "确定要退出游戏吗?");
    }
}

