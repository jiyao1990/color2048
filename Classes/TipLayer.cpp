//
//  TipLayer.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/3/4.
//
//

#include "TipLayer.h"
#include "GameMap.h"


LayerColor* TipLayer::createLayer(TipType type, MainMenuScene* mainMenu)
{
    TipLayer *pRet = new TipLayer();
    if (pRet && pRet->init(type, mainMenu))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool TipLayer::init(TipType type, MainMenuScene* mainMenu)
{
    if (!LayerColor::init()) {
        return false;
    }
    shareText = "";
    m_Type = type;
    m_MainMenu = mainMenu;
    
    this->initWithColor(Color4B(0, 0, 0, 0), gWinSize.width, gWinSize.height);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch,Event* event)
    {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    bg = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][8], gWinSize.width * 3 / 4, gWinSize.height / 2);
    this->addChild(bg);
    bg->setPosition(Vec2((gWinSize.width - bg->getContentSize().width)/ 2, gWinSize.height));
    
    auto contentTTF = Label::createWithSystemFont("是否结束当前游戏?", "黑体", bg->getContentSize().width / 13.56);
    contentTTF->setPosition(Vec2(bg->getContentSize().width / 2 , bg->getContentSize().height * 3 / 4));
    bg->addChild(contentTTF);
    contentTTF->enableShadow();
    
    auto btnBg1 = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][5], bg->getContentSize().width, bg->getContentSize().height / 6);
    btnBg1->setPosition(Vec2(0,0));
    bg->addChild(btnBg1);
    auto btnTTF1 = Label::createWithSystemFont("否", "黑体", btnBg1->getContentSize().height / 3);
    btnTTF1->setPosition(Vec2(btnBg1->getContentSize().width / 2 , btnBg1->getContentSize().height / 2));
    btnBg1->addChild(btnTTF1);
    btnTTF1->enableShadow();
    
    auto btnBg2 = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][2], bg->getContentSize().width, bg->getContentSize().height / 6);
    btnBg2->setPosition(Vec2(0,btnBg1->getContentSize().height));
    bg->addChild(btnBg2);
    auto btnTTF2 = Label::createWithSystemFont("是", "黑体", btnBg2->getContentSize().height / 3);
    btnTTF2->setPosition(Vec2(btnBg2->getContentSize().width / 2 , btnBg2->getContentSize().height / 2));
    btnBg2->addChild(btnTTF2);
    btnTTF2->enableShadow();
    
    auto menu = Menu::create();
    bg->addChild(menu);
    menu->setPosition(Vec2(0,0));
    
    auto btn1 = MenuItem::create(CC_CALLBACK_1(TipLayer::removeSelf, this));
    btn1->setContentSize(btnBg1->getContentSize());
    btn1->setAnchorPoint(Vec2(0,0));
    btn1->setPosition(btnBg1->getPosition());
    menu->addChild(btn1);
    
    auto btn2 = MenuItem::create(CC_CALLBACK_1(TipLayer::okCallBack, this));
    btn2->setContentSize(btnBg2->getContentSize());
    btn2->setAnchorPoint(Vec2(0,0));
    btn2->setPosition(btnBg2->getPosition());
    menu->addChild(btn2);
    
    switch (type) {
        case TipType_BackToHome:
        {
            
            this->runAction(FadeTo::create(0.1f, 200));
            bg->runAction(EaseBounceOut::create(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/ 2 , (gWinSize.height - bg->getContentSize().height)/ 2))));
            contentTTF->setString("是否结束当前游戏?");
            btnTTF1->setString("否");
            btnTTF2->setString("是");
        }
            break;
            
        case TipType_GameOver:
        {
            
            this->runAction(FadeTo::create(0.1f, 200));
            bg->runAction(EaseBounceOut::create(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/ 2 , (gWinSize.height - bg->getContentSize().height)/ 2))));
            char buffer[64];
            sprintf(buffer,"本次得分:%d",gGlobal->score);
            auto scoreTTF = Label::createWithSystemFont(buffer, "黑体", bg->getContentSize().width / 13.56);
            scoreTTF->setPosition(Vec2(bg->getContentSize().width / 2 , contentTTF->getPositionY() - contentTTF->getContentSize().height - scoreTTF->getContentSize().height));
            bg->addChild(scoreTTF);
            scoreTTF->enableShadow();
            contentTTF->setString("游戏结束");
            contentTTF->setSystemFontSize(bg->getContentSize().width / 18.75);
            btnTTF1->setString("炫耀一下");
            btnTTF2->setString("重新开始");
        }
            break;
        case TipType_GameWin:
        {
            this->runAction(FadeTo::create(0.1f, 200));
            bg->runAction(EaseBounceOut::create(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/ 2 , (gWinSize.height - bg->getContentSize().height)/ 2))));
            char buffer[64];
            sprintf(buffer,"本次得分:%d",gGlobal->score);
            auto scoreTTF = Label::createWithSystemFont(buffer, "黑体", bg->getContentSize().width / 13.56);
            scoreTTF->setPosition(Vec2(bg->getContentSize().width / 2 , contentTTF->getPositionY() - contentTTF->getContentSize().height - scoreTTF->getContentSize().height));
            bg->addChild(scoreTTF);
            scoreTTF->enableShadow();
            contentTTF->setString("厉害!完成!佩服!");
            contentTTF->setSystemFontSize(bg->getContentSize().width / 9.375);
            btnTTF1->setString("炫耀一下");
            btnTTF2->setString("重新开始");
        }
            break;
        case TipType_Tips:
        {
            this->runAction(FadeTo::create(0.1f, 100));
            
            shareText.append("今天");
            for (int row = 0; row < MapMaxLength; row ++) {
                for (int col = 0; col < MapMaxLength ; col ++) {
                    
                    int id = 0 ;
                    if (gGameMap->getDataLevel(row, col) == 0) {
                        id =  random(0, 4);
                    }else{
                        id = gGameMap->getDataId(row, col) % TextCount;
                    }
                    
                    shareText.append(gGlobal->shareText[col][gGameMap->getDataLevel(row, col)][id]);
                }
                switch (row) {
                    case 0:
                        shareText.append(",然后");
                        break;
                    case 1:
                        shareText.append(",之后");
                        break;
                    case 2:
                        shareText.append(",最后");
                        break;
                    case 3:
                        
                        break;
                }
            }
            shareText.append("。真是有意义的一天啊!");
            
            contentTTF->setString("你得到的方块秘密:\n\n" + shareText + "\n\n点击炫耀一下可以分享到微博哦~");
            contentTTF->setSystemFontSize(bg->getContentSize().width / 18.75);
            contentTTF->setDimensions(bg->getContentSize().width - 50, 0);
            btnTTF1->setString("知道了");
            btnBg2->setVisible(false);
            bg->setContentSize(Size(gWinSize.width * 3 / 4, gWinSize.width * 3 / 4));
            bg->setPosition(Vec2((gWinSize.width - bg->getContentSize().width)/ 2, (gWinSize.height - bg->getContentSize().height)/ 2));
            contentTTF->setPosition(Vec2(bg->getContentSize().width / 2 , bg->getContentSize().height / 2 + btnBg1->getContentSize().height / 2));
            
        }
            break;
    }
    
    return true;
}

void TipLayer::okCallBack(Ref* pSender)
{
    switch (m_Type) {
        case TipType_BackToHome:
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),CallFunc::create(CC_CALLBACK_0(MainMenuScene::backHome, m_MainMenu)),RemoveSelf::create(), NULL));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
            break;
            
        case TipType_GameOver:
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),CallFunc::create(CC_CALLBACK_0(MainMenuScene::resetGame, m_MainMenu)),RemoveSelf::create(), NULL));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
            break;
        case TipType_GameWin:
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),CallFunc::create(CC_CALLBACK_0(MainMenuScene::resetGame, m_MainMenu)),RemoveSelf::create(), NULL));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
            break;
        case TipType_Tips:
            break;
    }
}

void TipLayer::removeSelf(Ref* pSender)
{

    switch (m_Type) {
        case TipType_BackToHome:
        {
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),RemoveSelf::create(), NULL));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
        }
            break;
            
        case TipType_GameOver:
        {
            if (shareText == "") {
                shareText.append("今天");
                for (int row = 0; row < MapMaxLength; row ++) {
                    for (int col = 0; col < MapMaxLength ; col ++) {
                        
                        int id = 0 ;
                        if (gGameMap->getDataLevel(row, col) == 0) {
                            id =  random(0, 4);
                        }else{
                            id = gGameMap->getDataId(row, col) % TextCount;
                        }
                        
                        
                        shareText.append(gGlobal->shareText[col][gGameMap->getDataLevel(row, col)][id]);
                    }
                    switch (row) {
                        case 0:
                            shareText.append(",然后");
                            break;
                        case 1:
                            shareText.append(",之后");
                            break;
                        case 2:
                            shareText.append(",最后");
                            break;
                        case 3:
                            
                            break;
                    }
                }
                shareText.append("。真是有意义的一天啊!");
                
                shareText.append("————我的得分为" + toString(gGlobal->score) + "分，via 方块密码:2048");
                
                
            }
            m_MainMenu->share(shareText);
        }
            break;
            
        case TipType_GameWin:
        {
            if (shareText == "") {
                shareText.append("今天");
                for (int row = 0; row < MapMaxLength; row ++) {
                    for (int col = 0; col < MapMaxLength ; col ++) {
                        
                        int id = 0 ;
                        if (gGameMap->getDataLevel(row, col) == 0) {
                            id =  random(0, 4);
                        }else{
                            id = gGameMap->getDataId(row, col) % TextCount;
                        }
                        
                        
                        shareText.append(gGlobal->shareText[col][gGameMap->getDataLevel(row, col)][id]);
                    }
                    switch (row) {
                        case 0:
                            shareText.append(",然后");
                            break;
                        case 1:
                            shareText.append(",之后");
                            break;
                        case 2:
                            shareText.append(",最后");
                            break;
                        case 3:
                            
                            break;
                    }
                }
                shareText.append("。真是有意义的一天啊!");
                
                shareText.append("————小伙伴们颤抖吧！我已经成功黑化了！我的得分为" + toString(gGlobal->score) + "分！求超越！via 方块密码:2048");
            }
            m_MainMenu->share(shareText);
        }
            break;
        case TipType_Tips:
        {
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),RemoveSelf::create(), NULL));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
        }
            break;
    }
}

