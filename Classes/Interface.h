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

#define  gInterface Interface::instance()

#define INTERFACE_CALL_FUNCNAME_ShowAd  "showAd"


using namespace std;
class Interface {
    
    
public:
    static Interface* instance();
    // 公共跨平台接口
    string callPlatformFunction(string functionName, string jsonContent);
private:
    Interface();
    ~Interface();
    static Interface* _instance;
};

#endif /* defined(__MyCppGame__Interface__) */
