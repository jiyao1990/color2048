//
//  Global.h
//  MyCppGame
//
//  Created by Jiyao on 15/1/30.
//
//

#ifndef __MyCppGame__Global__
#define __MyCppGame__Global__

#include "cocos2d.h"
#include <iostream>
#include "cocos-ext.h"

#define gWinSize     Director::getInstance()->getWinSize()
#define gGlobal      Global::getInstance()
#define maxLevel     11
#define TextCount    5

#define screenShotImageName     "screenShot.jpg"

#define Data_HighScore          "score"
#define Data_LoginCount         "LoginCount"

#define INVALID_VALUE_STR       "-1"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace  rapidjson;
using namespace std;

/**
 *  转化字符类函数
 */
template <class T>
std::string toString(T _T){
    std::stringstream _ss;
    _ss << _T;
    return _ss.str();
}

enum colorType{
    colorType_green = 0,
    colorType_blue,
    colorType_red,
    colorType_Size,
};

class JsonPair : public Ref
{
public:
    static JsonPair* create(string key, string value);
    
    JsonPair();
    
    CC_SYNTHESIZE(string, m_key, Key);
    CC_SYNTHESIZE(string, m_value, Value);
    
private:
    JsonPair(string key, string value);
};

class Global : public Node{
    
    Global();
    ~Global();
    
public:

    static Global* getInstance();
    static Color4B colorMap[colorType_Size][maxLevel];
//    static string shareText[][maxLevel + 1][TextCount];
    static string shareText1[];
    static string shareText2[];
    static string shareText3[];
    static string shareText4[];
    
    colorType _colorType;
    map< int, Node* > lumpMap;
    
    int currentID;
    
    int score;
    
    string highScore;
    
    bool isHomeAdSwitch;
    
    void saveScreenshot(Node* node, const std::string& fileName,const std::function<void(const std::string&)>& callback = NULL);
    
    string getJsonStr(JsonPair* jsonPair, ...) CC_REQUIRES_NULL_TERMINATION;
    
    /**
     *  字符串去除非法字符 (" \n\r\t")空格 回车换行 制表符
     *
     *  @param str 待处理字符串
     *  @param 0   从第几位开始,默认从头开始
     *
     *  @return 返回处理好的串
     */
    string trim(string str, string::size_type pos = 0);
    
    string getSecretText();
    
    //读取文字内容
    void loadTextMap();
    
    //获取node的Rect
    cocos2d::Rect getNodeRect(Node* node);
    
private:

    
    void loadMap(string *str, int size, int count);
    map< int, vector<string> > textMap[4];
    
    //------variable----------
    static Global* _instance;
    
    
};

#endif /* defined(__MyCppGame__Global__) */
