//
//  Interface_ios.m
//  MyCppGame
//
//  Created by Jiyao on 15/3/4.
//
//

#include "Interface.h"
#import "AppController.h"

string Interface::callPlatformFunction(string functionName, string jsonContent)
{
    if (INTERFACE_CALL_FUNCNAME_ShowAd == functionName)
    {
        [AppController showInterstitial];
    }else if(INTERFACE_CALL_FUNCNAME_Share == functionName){
        CCLOG("%s",jsonContent.c_str());
        Json::Value root = getJsonRoot(jsonContent);
        string path = root["imagePath"].asString();
        string text = root["shareText"].asString();
        NSString* nsStr1 = [NSString stringWithUTF8String:path.c_str()];
        NSString* nsStr2 = [NSString stringWithUTF8String:text.c_str()];
        [AppController share:nsStr1 ShareText:nsStr2];
        
    }else if(INTERFACE_CALL_FUNCNAME_ScreenShot == functionName){
        [AppController screenShot];
    }else if(INTERFACE_CALL_FUNCNAME_SaveScore == functionName){
        NSString* nsStr = [NSString stringWithUTF8String:jsonContent.c_str()];
        [AppController saveScore:nsStr];
        
    }else if(INTERFACE_CALL_FUNCNAME_ReadScore == functionName){
        NSString* nsStr = [AppController readScore];
        if (nsStr != nil) {
            string str = [nsStr UTF8String];
            return str;
        }
        return "0";
    }
    return "";
}

Json::Value Interface::getJsonRoot(string jsonContent)
{
    Json::Value root;
    Json::Reader reader;
    
    bool isParseOK = reader.parse(jsonContent, root, false);
    
    CCAssert(isParseOK, "Interface::getJsonRoot error!!");
    
    return root;
}