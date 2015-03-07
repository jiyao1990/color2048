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
    }else if(INTERFACE_CALL_FUNCNAME_SaveData == functionName){
        
        Json::Value root = getJsonRoot(jsonContent);
        string name = root["name"].asString();
        string value = root["value"].asString();
        NSString* nsStr1 = [NSString stringWithUTF8String:name.c_str()];
        NSString* nsStr2 = [NSString stringWithUTF8String:value.c_str()];
        [AppController saveData:nsStr1 value:nsStr2];
        
    }else if(INTERFACE_CALL_FUNCNAME_ReadData == functionName){
        NSString* nsStr1 = [NSString stringWithUTF8String:jsonContent.c_str()];
        NSString* nsStr = [AppController readData:nsStr1];
        if (nsStr != nil) {
            string str = [nsStr UTF8String];
            return str;
        }
        return "";
    }
    return "";
}
