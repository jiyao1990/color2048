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