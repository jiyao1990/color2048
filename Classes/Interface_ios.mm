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
    }
    return "";
}