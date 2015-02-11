//
//  GameMap.h
//  MyCppGame
//
//  Created by Jiyao on 15/2/12.
//
//

#ifndef __MyCppGame__GameMap__
#define __MyCppGame__GameMap__

#include <stdio.h>

#define gGameMap   GameMap::getInstance()

#define MapMaxLength  4

enum GridDirection{
    
    GridUp = 0,
    GridDown,
    GridLeft,
    GridRight,
    
};

class GameMap {
    
    
public:

    
    static GameMap* getInstance();
    void resetMapData();
    void changeMapByDirection(GridDirection dir);
    void changeMapByCoord(int row, int col, int level);
    
    int getGridCountByDirection(GridDirection dir, int row, int col);
    
    
private:
    
    GameMap();
    ~GameMap();
    
    int MapData[MapMaxLength][MapMaxLength];
    
    static GameMap* _Instance;
    
};

#endif /* defined(__MyCppGame__GameMap__) */
