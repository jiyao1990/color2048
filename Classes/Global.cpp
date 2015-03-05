//
//  Global.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#include "Global.h"
#include "Interface.h"
#include "jsons.h"

#pragma mark -
#pragma mark SGJsonPair

JsonPair::JsonPair(string key, string value)
{
    m_key = key;
    m_value = value;
}

JsonPair::JsonPair()
{
    
}

JsonPair* JsonPair::create(string key, string value)
{
    JsonPair* pRet = new JsonPair(key, value);
    if (pRet)
    {
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return NULL;
}


#pragma mark -
#pragma mark Global

Global* Global::_instance = NULL;

Color4B Global::colorMap[colorType_Size][maxLevel] ={
    
    {
        Color4B(240, 255, 200, 255),
        Color4B(180, 245, 180, 255),
        Color4B(150, 220, 120, 255),
        Color4B(110, 200, 100, 255),
        Color4B(80,  175, 70,  255),
        Color4B(40,  145, 50,  255),
        Color4B(25,  115, 25,  255),
        Color4B(15,  90,  15,  255),
        Color4B(10,  60,  10,  255),
        Color4B(0,   30,  0,   255),
        Color4B(0,   0,   0,   255),
    },
    {
        Color4B(143, 244, 255, 255),
        Color4B(100, 205, 225, 255),
        Color4B(75,  172, 205, 255),
        Color4B(65,  150, 175, 255),
        Color4B(55,  130, 155, 255),
        Color4B(46,  106, 125, 255),
        Color4B(25,  80,  105, 255),
        Color4B(27,  60,  74,  255),
        Color4B(10,  40,  55,  255),
        Color4B(0,   10,  30,  255),
        Color4B(0,   0,   0,   255)
    },
    {
        Color4B(254, 190, 191, 255),
        Color4B(252, 119, 142, 255),
        Color4B(240, 80,  100, 255),
        Color4B(220, 60,  70,  255),
        Color4B(200, 40,  50,  255),
        Color4B(187, 17,  24,  255),
        Color4B(155, 15,  20,  255),
        Color4B(113, 12,  15,  255),
        Color4B(55,  10,  10,  255),
        Color4B(30,  0,   0,   255),
        Color4B(0,   0,   0,   255)},
};

Global::Global()
{
    _colorType = colorType_green;
    currentID = 0;
    score = 0;
    highScore = gInterface->callPlatformFunction(INTERFACE_CALL_FUNCNAME_ReadScore, "");
    isHomeAdSwitch = false;
    lumpMap.clear();
}

Global::~Global()
{
    
}

Global* Global::getInstance()
{
    
    if (!_instance) {
        _instance = new Global();
    }
    
    return _instance;
}

void Global::saveScreenshot(Node* node,const std::string& fileName,const std::function<void(const std::string&)>& callback)

{
    
    Image::Format format;
    
    //进行后缀判断
    
    if(std::string::npos != fileName.find_last_of(".")){
        
        auto extension = fileName.substr(fileName.find_last_of("."),fileName.length());
        
        if (!extension.compare(".png")) {
            
            format = Image::Format::PNG;
            
        } else if(!extension.compare(".jpg")) {
            
            format = Image::Format::JPG;
            
        } else{
            
            CCLOG("cocos2d: the image can only be saved as JPG or PNG format");
            
            return;
            
        }
        
    } else {
        
        CCLOG("cocos2d: the image can only be saved as JPG or PNG format");
        
        return ;
        
    }
    
    //获取屏幕尺寸，初始化一个空的渲染纹理对象
    
    auto renderTexture = RenderTexture::create(gWinSize.width, gWinSize.height, Texture2D::PixelFormat::RGBA8888);
    
    //清空并开始获取
    
    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    
    //遍历场景节点对象，填充纹理到RenderTexture中
    
    node->visit();
    
    //结束获取
    
    renderTexture->end();
    
    //保存文件
    
    renderTexture->saveToFile(fileName , format);
    
    //使用schedule在下一帧中调用callback函数
    
    auto fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
    
    auto scheduleCallback = [&,fullPath,callback](float dt){
        
        callback(fullPath);  
        
    };  
    
    auto _schedule = node->getScheduler();
    
    _schedule->schedule(scheduleCallback, this, 0.0f,0,0.0f, false, "screenshot");  
    
}

string Global::getJsonStr(JsonPair* jsonPair, ...)
{
    Json::Value root;
    
    va_list args;
    va_start(args, jsonPair);
    
    if (jsonPair)
    {
        root[jsonPair->getKey()] = jsonPair->getValue();
        JsonPair *i = va_arg(args, JsonPair*);
        while (i)
        {
            root[i->getKey()] = i->getValue();
            i = va_arg(args, JsonPair*);
        }
    }
    
    va_end(args);
    
    string sRet = root.toStyledString();
    sRet = trim(sRet);
    
    return sRet;
}

std::string Global::trim(std::string str, std::string::size_type pos/* = 0*/)
{
    std::string delim = " \n\r\t";
    pos = str.find_first_of(delim, pos);
    if (pos == std::string::npos)
        return str;
    return trim(str.erase(pos, 1));
}
