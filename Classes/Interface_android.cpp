//
//  Interface_android.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/3/7.
//
//

//
//  Interface_android.cpp
//  fish3
//
//  Created by Xiaowj on 13-12-5.
//
//

#include "Interface.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

string Interface::callPlatformFunction(string functionName, string jsonContent)
{
    JniMethodInfo callPlatformFunc;//定义Jni函数信息结构体
    
    //getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
    bool isHave1 = JniHelper::getStaticMethodInfo(callPlatformFunc,"com/sg/android/platform/Platform_android","callPlatformFunc", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    
    if (!isHave1)
    {
        cocos2d::log("jni:此函数不存在");
    }
    else
    {
        cocos2d::log("jni:此函数存在 %s", functionName.c_str());
        //调用此函数
        jstring StringArg1 = callPlatformFunc.env->NewStringUTF(functionName.c_str());
        jstring StringArg2 = callPlatformFunc.env->NewStringUTF(jsonContent.c_str());
        jobject jobj = callPlatformFunc.env->CallStaticObjectMethod(callPlatformFunc.classID, callPlatformFunc.methodID,StringArg1,StringArg2);
        
        jstring jstr = (jstring) jobj;
        
        std::string str = JniHelper::jstring2string(jstr);
        
        cocos2d::log("jni-java函数执行完毕");
        return  str;
    }
    
    return "{}";
}


#endif

