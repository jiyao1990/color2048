//
//  Interface.h
//  MyCppGame
//
//  Created by Jiyao on 15/3/4.
//
//

#ifndef __MyCppGame__Interface__
#define __MyCppGame__Interface__

#include <stdio.h>
#include "jsons.h"
#include "cocos2d.h"
#include "cocos-ext.h"

#define  gInterface Interface::instance()

#define INTERFACE_CALL_FUNCNAME_ShowAd       "showAd"
#define INTERFACE_CALL_FUNCNAME_Share        "share"
#define INTERFACE_CALL_FUNCNAME_ScreenShot   "screenShot"
#define INTERFACE_CALL_FUNCNAME_SaveData     "saveData"
#define INTERFACE_CALL_FUNCNAME_ReadData     "readData"


using namespace std;
using namespace cocos2d;
using namespace extension;

class Interface {
    
    
public:
    static Interface* instance();
    // 公共跨平台接口
    string callPlatformFunction(string functionName, string jsonContent);
    
     Json::Value getJsonRoot(string jsonContent);
    
private:
    Interface();
    ~Interface();
    static Interface* _instance;
};

#endif /* defined(__MyCppGame__Interface__) */
