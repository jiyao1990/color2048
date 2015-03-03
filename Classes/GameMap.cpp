//
//  GameMap.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/2/12.
//
//

#include "GameMap.h"
#include "Lump.h"

GameMap* GameMap::_Instance = NULL;

GameMap::GameMap()
{
    resetMapData();
}

GameMap::~GameMap()
{
    
}

GameMap* GameMap::getInstance()
{
    if (!_Instance) {
        _Instance = new GameMap();
        return _Instance;
    }
    
    return _Instance;
}

void GameMap::resetMapData()
{
    for (int i = 0; i < MapMaxLength; i++) {
        for (int j = 0; j < MapMaxLength; j++) {
            
            MapData[i][j].ID = 0;
            MapData[i][j].level = 0;
            
        }
    }
    
    printf("------------------------------\n");
    for (int i = MapMaxLength - 1; i >= 0; i--) {
        printf("|%d,%d,%d,%d|====|%d,%d,%d,%d|\n",MapData[i][0].level,MapData[i][1].level,MapData[i][2].level,MapData[i][3].level,MapData[i][0].ID,MapData[i][1].ID,MapData[i][2].ID,MapData[i][3].ID);
    }
}

void GameMap::changeMapByCoord(int row, int col, int level, int ID)
{
    MapData[row][col].level = level;
    MapData[row][col].ID = ID;
    printf("------------------------------\n");
    for (int i = MapMaxLength - 1; i >= 0; i--) {
        printf("|%d,%d,%d,%d|====|%d,%d,%d,%d|\n",MapData[i][0].level,MapData[i][1].level,MapData[i][2].level,MapData[i][3].level,MapData[i][0].ID,MapData[i][1].ID,MapData[i][2].ID,MapData[i][3].ID);
    }
}

int GameMap::changeMapByDirection(GridDirection dir)
{
    bool isCombine = false;
    bool isMove = false;
    int step = 0;
    int tempLevel = 0;
    switch (dir) {
        case GridUp:
            for (int col = 0 ; col < MapMaxLength; col ++) {
                
                for (int row = MapMaxLength - 1; row >= 0; row --) {
                    
                    if (MapData[row][col].level != 0) {
                        tempLevel = MapData[row][col].level;
                        //合成
                        if (row > 0) {
                            int i = row - 1;
                            while (i != -1) {
                                if (tempLevel == MapData[i][col].level) {
                                    MapData[row][col].level = tempLevel + 1;
                                    
                                    int m = row + 1;
                                    while (m < MapMaxLength) {
                                        if (MapData[m][col].level == 0) {
                                            step++;
                                        }
                                        m ++;
                                    }
                                    
                                    //被消除的方块移动
                                    Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[i][col].ID)->second;
                                    lump->move(dir, abs(row - i) + step, MyActionType_Fade);
                                    gGlobal->lumpMap.erase(MapData[i][col].ID);
                                    //升级方块变色
                                    Lump* lump2 = (Lump *)gGlobal->lumpMap.find(MapData[row][col].ID)->second;
                                    lump2->changeColor(MapData[row][col].level);
                                    
                                    MapData[i][col].level = 0;
                                    MapData[i][col].ID = 0;
                                    isCombine = true;
                                    i --;
                                }else if (MapData[i][col].level != tempLevel && MapData[i][col].level != 0) {
                                    break;
                                }else{
                                    i --;
                                }
                            }
                        }
                        
                        
                        //移动
                        for (int i = MapMaxLength - 1; i > row; i --) {
                            
                            if (MapData[i][col].level == 0) {
                                
                                MapData[i][col] = MapData[row][col];
                                Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[i][col].ID)->second;
                                lump->move(dir, abs(row - i), MyActionType_Null);
                                
                                MapData[row][col].level = 0;
                                MapData[row][col].ID = 0;
                                isMove = true;
                                break;
                                
                            }
                            
                        }
                        
                    }
                    
                }
                
                
            }
            
            break;
        case GridDown:
            for (int col = 0 ; col < MapMaxLength; col ++) {
                
                //                std::vector<UnitData> vec;
                for (int row = 0; row < MapMaxLength ; row ++) {
                    
                    if (MapData[row][col].level != 0) {
                        tempLevel = MapData[row][col].level;
                        //合成
                        if (row < MapMaxLength - 1) {
                            int i = row + 1;
                            while (i != MapMaxLength) {
                                if (tempLevel == MapData[i][col].level) {
                                    MapData[row][col].level = tempLevel + 1;
                                    
                                    int m = row - 1;
                                    while (m >= 0) {
                                        if (MapData[m][col].level == 0) {
                                            step++;
                                        }
                                        m --;
                                    }
                                    
                                    //被消除的方块移动
                                    Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[i][col].ID)->second;
                                    lump->move(dir, abs(row - i) + step, MyActionType_Fade);
                                    gGlobal->lumpMap.erase(MapData[i][col].ID);
                                    //升级方块变色
                                    Lump* lump2 = (Lump *)gGlobal->lumpMap.find(MapData[row][col].ID)->second;
                                    lump2->changeColor(MapData[row][col].level);
                                    
                                    MapData[i][col].level = 0;
                                    MapData[i][col].ID = 0;
                                    isCombine = true;
                                    
                                    i ++;
                                }else if (MapData[i][col].level != tempLevel && MapData[i][col].level != 0) {
                                    break;
                                }else{
                                    i ++;
                                }
                            }
                        }
                        
                        //移动
                        for (int i = 0; i < row; i ++) {
                            
                            if (MapData[i][col].level == 0) {
                                
                                MapData[i][col] = MapData[row][col];
                                Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[i][col].ID)->second;
                                lump->move(dir, abs(row - i), MyActionType_Null);
                                MapData[row][col].level = 0;
                                MapData[row][col].ID = 0;
                                isMove = true;
                                break;
                                
                            }
                            
                        }
                        
                    }
                }
                
            }
            break;
        case GridLeft:
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                //                std::vector<UnitData> vec;
                for (int col = 0; col < MapMaxLength ; col ++) {
                    
                    if (MapData[row][col].level != 0) {
                        tempLevel = MapData[row][col].level;
                        //合成
                        if (col < MapMaxLength - 1) {
                            int i = col + 1;
                            while (i != MapMaxLength) {
                                if (tempLevel == MapData[row][i].level) {
                                    MapData[row][col].level = tempLevel + 1;
                                    
                                    int m = col - 1;
                                    while (m >= 0) {
                                        if (MapData[row][m].level == 0) {
                                            step++;
                                        }
                                        m --;
                                    }
                                    
                                    //被消除的方块移动
                                    Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[row][i].ID)->second;
                                    lump->move(dir, abs(col - i) + step, MyActionType_Fade);
                                    gGlobal->lumpMap.erase(MapData[row][i].ID);
                                    //升级方块变色
                                    Lump* lump2 = (Lump *)gGlobal->lumpMap.find(MapData[row][col].ID)->second;
                                    lump2->changeColor(MapData[row][col].level);
                                    
                                    MapData[row][i].level = 0;
                                    MapData[row][i].ID = 0;
                                    isCombine = true;
                                    
                                    i ++;
                                }else if (MapData[row][i].level != tempLevel && MapData[row][i].level != 0) {
                                    break;
                                }else{
                                    i ++;
                                }
                            }
                        }
                        
                        //移动
                        for (int i = 0; i < col; i ++) {
                            
                            if (MapData[row][i].level == 0) {
                                
                                MapData[row][i] = MapData[row][col];
                                Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[row][i].ID)->second;
                                lump->move(dir, abs(col - i), MyActionType_Null);
                                MapData[row][col].level = 0;
                                MapData[row][col].ID = 0;
                                isMove = true;
                                break;
                                
                            }
                            
                        }
                        
                    }
                }
                
            }
            break;
        case GridRight:
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                for (int col = MapMaxLength - 1; col >= 0; col --) {
                    
                    if (MapData[row][col].level != 0) {
                        tempLevel = MapData[row][col].level;
                        //合成
                        if (col > 0) {
                            int i = col - 1;
                            while (i != -1) {
                                if (tempLevel == MapData[row][i].level) {
                                    MapData[row][col].level = tempLevel + 1;
                                    
                                    int m = col + 1;
                                    while (m < MapMaxLength) {
                                        if (MapData[row][m].level == 0) {
                                            step++;
                                        }
                                        m ++;
                                    }
                                    
                                    //被消除的方块移动
                                    Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[row][i].ID)->second;
                                    lump->move(dir, abs(col - i) + step, MyActionType_Fade);
                                    gGlobal->lumpMap.erase(MapData[row][i].ID);
                                    //升级方块变色
                                    Lump* lump2 = (Lump *)gGlobal->lumpMap.find(MapData[row][col].ID)->second;
                                    lump2->changeColor(MapData[row][col].level);
                                    
                                    MapData[row][i].level = 0;
                                    MapData[row][i].ID = 0;
                                    isCombine = true;
                                    i --;
                                }else if (MapData[row][i].level != tempLevel && MapData[row][i].level != 0) {
                                    break;
                                }else{
                                    i --;
                                }
                            }
                        }
                        
                        //移动
                        for (int i = MapMaxLength - 1; i > col; i --) {
                            
                            if (MapData[row][i].level == 0) {
                                
                                MapData[row][i] = MapData[row][col];
                                Lump* lump = (Lump *)gGlobal->lumpMap.find(MapData[row][i].ID)->second;
                                lump->move(dir, abs(col - i), MyActionType_Null);
                                MapData[row][col].level = 0;
                                MapData[row][col].ID = 0;
                                isMove = true;
                                break;
                                
                            }
                            
                        }
                        
                    }
                }
               
            }
            break;
    }
    
    
    printf("------------------------------\n");
    for (int i = MapMaxLength - 1; i >= 0; i--) {
        printf("|%d,%d,%d,%d|====|%d,%d,%d,%d|\n",MapData[i][0].level,MapData[i][1].level,MapData[i][2].level,MapData[i][3].level,MapData[i][0].ID,MapData[i][1].ID,MapData[i][2].ID,MapData[i][3].ID);
    }
    
    if (isCombine) {
        return 1;
    }else if(!isMove){
        return 0;
    }else{
        return 2;
    }
    
}

int GameMap::getGridCountByDirection(GridDirection dir, int row, int col)
{
    int count = 0 ;
    
    switch (dir) {
        case GridUp:
            for (int i = row + 1; i < MapMaxLength ; i ++) {
                if (MapData[i][col].level == 0) {
                    count ++;
                }else{
                    if (MapData[row][col].level == MapData[i][col].level) {
                        count ++;
                    }
                }
            }
            break;
        case GridDown:
            for (int i = row - 1; i >= 0 ; i --) {
                if (MapData[i][col].level == 0) {
                    count ++;
                }else{
                    if (MapData[row][col].level == MapData[i][col].level) {
                        count ++;
                    }
                }
            }
            break;
        case GridLeft:
            for (int i = col - 1; i >= 0 ; i --) {
                if (MapData[row][i].level == 0) {
                    count ++;
                }else{
                    if (MapData[row][col].level == MapData[row][i].level) {
                        count ++;
                    }
                }
            }
            break;
        case GridRight:
            for (int i = col + 1; i < MapMaxLength ; i ++) {
                if (MapData[row][i].level == 0) {
                    count ++;
                }else{
                    if (MapData[row][col].level == MapData[row][i].level) {
                        count ++;
                    }
                }
            }
            break;
    }
    
    return count;
}

bool GameMap::isExist(int row , int col)
{
    return (MapData[row][col].level != 0);
}

bool GameMap::isFull()
{
    for (int col = 0 ; col < MapMaxLength; col ++) {
        
        for (int row = 0 ; row < MapMaxLength; row ++) {
            
            if (MapData[row][col].ID == 0) {
                return  false;
            }
            
        }
    }
    
    return true;
}

bool GameMap::isFail()
{
    if (isFull()) {
        
        for (int col = 0 ; col < MapMaxLength; col ++) {
            
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                if (col > 0) {
                    
                    if (MapData[row][col].level == MapData[row][col - 1].level) {
                        return false;
                    }
                    
                }
                
                if (row > 0) {
                    
                    if (MapData[row][col].level == MapData[row - 1][col].level) {
                        return false;
                    }
                    
                }
                
            }
        }
        
        
        return true;
    }
    
    return false;
}

