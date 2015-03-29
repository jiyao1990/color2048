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
    
    string contentStr;
    if (gGlobal->isChinese) {
        contentStr = "是否结束当前游戏?";
    }else{
        contentStr = "Are you sure you would like to end the current game?";
    }
    auto contentTTF = Label::createWithSystemFont(contentStr, "黑体", bg->getContentSize().width / 13.56);
    contentTTF->setPosition(Vec2(bg->getContentSize().width / 2 , bg->getContentSize().height * 3 / 4));
    if (!gGlobal->isChinese) {
        
        contentTTF->setDimensions(bg->getContentSize().width, 0);
        contentTTF->setAlignment(TextHAlignment::CENTER);
    }
    bg->addChild(contentTTF);
    contentTTF->enableShadow();
    
    auto btnBg1 = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][5], bg->getContentSize().width, bg->getContentSize().height / 6);
    btnBg1->setPosition(Vec2(0,0));
    bg->addChild(btnBg1);
    
    string btn1Str;
    if (gGlobal->isChinese) {
        btn1Str = "否";
    }else{
        btn1Str = "Cancel";
    }
    auto btnTTF1 = Label::createWithSystemFont(btn1Str, "黑体", btnBg1->getContentSize().height / 3);
    btnTTF1->setPosition(Vec2(btnBg1->getContentSize().width / 2 , btnBg1->getContentSize().height / 2));
    btnBg1->addChild(btnTTF1);
    btnTTF1->enableShadow();
    
    auto btnBg2 = LayerColor::create(gGlobal->colorMap[gGlobal->_colorType][2], bg->getContentSize().width, bg->getContentSize().height / 6);
    btnBg2->setPosition(Vec2(0,btnBg1->getContentSize().height));
    bg->addChild(btnBg2);
    
    string btn2Str;
    if (gGlobal->isChinese) {
        btn2Str = "是";
    }else{
        btn2Str = "Yes";
    }
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
            if (gGlobal->isChinese) {
                contentTTF->setString("是否结束当前游戏?");
                btnTTF1->setString("否");
                btnTTF2->setString("是");
            }else{
                contentTTF->setString("Are you sure you would like to end the current game?");
                btnTTF1->setString("Cancel");
                btnTTF2->setString("Yes");
            }

        }
            break;
            
        case TipType_GameOver:
        {
            
            this->runAction(FadeTo::create(0.1f, 200));
            bg->runAction(EaseBounceOut::create(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/ 2 , (gWinSize.height - bg->getContentSize().height) * 2 / 3))));
            char buffer[64];
            if (gGlobal->isChinese) {
                sprintf(buffer,"本次得分:%d",gGlobal->score);
                contentTTF->setString("游戏结束");
                btnTTF1->setString("炫耀一下");
                btnTTF2->setString("重新开始");
            }else{
                sprintf(buffer,"Score:%d",gGlobal->score);
                contentTTF->setString("Game Over");
                btnTTF1->setString("Share It");
                btnTTF2->setString("Start over");
            }
            auto scoreTTF = Label::createWithSystemFont(buffer, "黑体", bg->getContentSize().width / 13.56);
            scoreTTF->setPosition(Vec2(bg->getContentSize().width / 2 , contentTTF->getPositionY() - contentTTF->getContentSize().height - scoreTTF->getContentSize().height));
            bg->addChild(scoreTTF);
            scoreTTF->enableShadow();
            contentTTF->setSystemFontSize(bg->getContentSize().width / 9.375);
            
        }
            break;
        case TipType_GameWin:
        {
            this->runAction(FadeTo::create(0.1f, 200));
            bg->runAction(EaseBounceOut::create(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/ 2 , (gWinSize.height - bg->getContentSize().height) * 2 / 3))));
            char buffer[64];
            if (gGlobal->isChinese) {
                sprintf(buffer,"本次得分:%d",gGlobal->score);
                contentTTF->setString("厉害!完成!佩服!");
                btnTTF1->setString("炫耀一下");
                btnTTF2->setString("继续");
            }else
            {
                sprintf(buffer,"Score:%d",gGlobal->score);
                contentTTF->setString("Congratulations to complete!You are best!");
                btnTTF1->setString("Share It");
                btnTTF2->setString("Continue current game");
             }
            auto scoreTTF = Label::createWithSystemFont(buffer, "黑体", bg->getContentSize().width / 13.56);
            scoreTTF->setPosition(Vec2(bg->getContentSize().width / 2 , contentTTF->getPositionY() - contentTTF->getContentSize().height - scoreTTF->getContentSize().height));
            bg->addChild(scoreTTF);
            scoreTTF->enableShadow();
            contentTTF->setSystemFontSize(bg->getContentSize().width / 9.375);
        }
            break;
        case TipType_Tips:
        {
            this->runAction(FadeTo::create(0.1f, 100));
            bg->runAction(EaseBounceOut::create(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/ 2, (gWinSize.height - bg->getContentSize().height) * 2 / 3))));
            shareText = gGlobal->getSecretText();
            
            if (gGlobal->isChinese) {
                contentTTF->setString("你得到的方块秘密:\n\n" + shareText + "\n\n点击炫耀一下可以分享到微博哦~");
                
                btnTTF1->setString("知道了");
            }else{
                contentTTF->setString("Your diary:\n\n" + shareText + "\n\nTouch the Share It button to publish your diary to Twitter.");
                
                btnTTF1->setString("OK");
            }
            contentTTF->setSystemFontSize(bg->getContentSize().width / 18.75);
            contentTTF->setDimensions(bg->getContentSize().width - 50, 0);
            btnBg2->setVisible(false);
            bg->setContentSize(Size(gWinSize.width * 3 / 4, gWinSize.width * 3 / 4));
//            bg->setPosition(Vec2((gWinSize.width - bg->getContentSize().width)/ 2, (gWinSize.height - bg->getContentSize().height)/ 2));
            contentTTF->setPosition(Vec2(bg->getContentSize().width / 2 , bg->getContentSize().height / 2 + btnBg1->getContentSize().height / 2));
            
        }
            break;
            
        case TipType_Diary:
            
            this->setOpacity(200);
            shareText = gGlobal->getSecretText();
            
            if (gGlobal->isChinese) {
                contentTTF->setString("你得到的方块秘密:\n\n" + shareText + "\n\n点击炫耀一下可以分享到微博哦~");
            }else{
                string date = gGlobal->getDateNow();
                
                contentTTF->setString(date + "\n\n" + shareText );
            }
            contentTTF->setSystemFontSize(bg->getContentSize().width / 18.75);
            btnBg2->setVisible(false);
            btnBg1->setVisible(false);
            bg->setContentSize(Size(gWinSize.width * 3 / 4, gWinSize.width * 4 / 5));
            bg->setPosition(Vec2((gWinSize.width - bg->getContentSize().width)/ 2, (gWinSize.height - bg->getContentSize().height) * 2 / 3));
            contentTTF->setPosition(Vec2(bg->getContentSize().width / 2 , bg->getContentSize().height / 2 + btnBg1->getContentSize().height / 2));
            contentTTF->setDimensions(bg->getContentSize().width * 3 / 4, 0);
            contentTTF->setAlignment(TextHAlignment::LEFT);
            
            break;
    }
    
    return true;
}

void TipLayer::okCallBack(Ref* pSender)
{
    switch (m_Type) {
        case TipType_BackToHome:
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),CallFunc::create(CC_CALLBACK_0(MainMenuScene::backHome, m_MainMenu)),RemoveSelf::create(), nullptr));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
            break;
            
        case TipType_GameOver:
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),CallFunc::create(CC_CALLBACK_0(MainMenuScene::resetGame, m_MainMenu)),RemoveSelf::create(), nullptr));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
            break;
        case TipType_GameWin:
            gGlobal->isContinue = true;
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),RemoveSelf::create(), nullptr));
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
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),RemoveSelf::create(), nullptr));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
        }
            break;
            
        case TipType_GameOver:
        {
            if (shareText == "") {
                
                shareText = gGlobal->getSecretText();
                
                string text;
                if (gGlobal->channel == Channel_360) {
                    text = "————我的得分为" + toString(gGlobal->score) + "分,快来一起玩吧~IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RAZBRwC";
                }else if(gGlobal->channel == Channel_qq){
                    text = "————我的得分为" + toString(gGlobal->score) + "分,快来一起玩吧~IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RAZBRwS";
                }else if(gGlobal->channel == Channel_baidu){
                    text = "————我的得分为" + toString(gGlobal->score) + "分,快来一起玩吧~IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RA2F06m";
                }else{
                    if (gGlobal->isChinese) {
                        text = "————我的得分为" + toString(gGlobal->score) + "分,快来一起玩吧~IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RAZBRwS";
                    }else{
                        shareText.clear();
                        text = "My score:" + toString(gGlobal->score) + ".This is my today's diary:).Download:http://t.cn/RAZBRw9";
                    }
                }
                
                shareText.append(text);
                
            }
            m_MainMenu->share(shareText);
        }
            break;
            
        case TipType_GameWin:
        {
            if (shareText == "") {
                
                shareText = gGlobal->getSecretText();
                string text;
                if (gGlobal->channel == Channel_360) {
                    text = "————小伙伴们颤抖吧！我已经成功黑化了！我的得分为" + toString(gGlobal->score) + "分！求超越！IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RAZBRwC";
                }else if(gGlobal->channel == Channel_qq){
                    text = "————小伙伴们颤抖吧！我已经成功黑化了！我的得分为" + toString(gGlobal->score) + "分！求超越！IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RAZBRwS";
                }else if(gGlobal->channel == Channel_baidu){
                    text = "————小伙伴们颤抖吧！我已经成功黑化了！我的得分为" + toString(gGlobal->score) + "分！求超越！IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RA2F06m";
                }else{
                    if (gGlobal->isChinese) {
                        
                        text = "————小伙伴们颤抖吧！我已经成功黑化了！我的得分为" + toString(gGlobal->score) + "分！求超越！IOS:http://t.cn/RAZBRw9 安卓:http://t.cn/RAZBRwS";
                    }else{
                        shareText.clear();
                        text = "————HaHa!I complete this game!My score:" + toString(gGlobal->score) + "！Download:http://t.cn/RAZBRw9";
                    }
                }
                shareText.append(text);
            }
            m_MainMenu->share(shareText);
        }
            break;
        case TipType_Tips:
        {
            this->runAction(Sequence::create(FadeTo::create(0.2f, 0),RemoveSelf::create(), nullptr));
            bg->runAction(MoveTo::create(0.2f, Vec2((gWinSize.width - bg->getContentSize().width)/2, - bg->getContentSize().height)));
            if (m_MainMenu->isFail) {
                m_MainMenu->addChild(TipLayer::createLayer(TipType_GameOver, m_MainMenu));
            }else{
                m_MainMenu->addChild(TipLayer::createLayer(TipType_GameWin, m_MainMenu));
            }
        }
            break;
    }
}
