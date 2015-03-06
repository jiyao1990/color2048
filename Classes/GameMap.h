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

struct UnitData {
    
    int ID;
    int level;
    
};

class GameMap {
    
    
public:

    
    static GameMap* getInstance();
    void resetMapData();
    int  changeMapByDirection(GridDirection dir);
    void changeMapByCoord(int row, int col, int level, int ID);
    
    int getGridCountByDirection(GridDirection dir, int row, int col);
    
    bool isExist(int row , int col);
    
    bool isFull();
    bool isFail();
    
    bool isWin;
    
    int getDataLevel(int row, int col);
    int getDataId(int row, int col);
    
private:
    
    GameMap();
    ~GameMap();
    
    UnitData MapData[MapMaxLength][MapMaxLength];
    
//    int MapData[MapMaxLength][MapMaxLength];
    
    static GameMap* _Instance;
    
};

#endif /* defined(__MyCppGame__GameMap__) */
