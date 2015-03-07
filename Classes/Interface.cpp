//
//  Interface.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/3/4.
//
//

#include "Interface.h"

Interface* Interface::_instance = NULL;

Interface::Interface()
{
    
}

Interface::~Interface()
{
    
}

Interface* Interface::instance()
{
    if (!Interface::_instance)
    {
        Interface::_instance = new Interface();
    }
    return Interface::_instance;
}


Json::Value Interface::getJsonRoot(string jsonContent)
{
    Json::Value root;
    Json::Reader reader;
    
    bool isParseOK = reader.parse(jsonContent, root, false);
    
    CCAssert(isParseOK, "Interface::getJsonRoot error!!");
    
    return root;
}