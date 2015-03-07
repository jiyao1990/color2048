#include "AppDelegate.h"
#include "MainMenuScene.h"
#include "Interface.h"
#include "FirstScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    Scene* scene;
    
    if (gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ReadData, Data_HighScore) == "") {
        gGlobal->highScore = "0";
    }else{
        gGlobal->highScore = gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ReadData, Data_HighScore);
    }

    string loginCountStr = gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ReadData, Data_LoginCount);
    int loginCount;
    if (loginCountStr == "") {
        loginCount = 0;
    }else{
        loginCount = atoi(loginCountStr.c_str());
    }
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
    
    //友盟广告开关
    if (gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_GetUMParams, "AdSwitch") == "open") {
        
        gGlobal->isHomeAdSwitch = true;
        
    }else{
        
        gGlobal->isHomeAdSwitch = false;
        
    }
    
    // run
    director->runWithScene(scene);
 
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
