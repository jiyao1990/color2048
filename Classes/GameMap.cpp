//
//  GameMap.cpp
//  MyCppGame
//
//  Created by Jiyao on 15/2/12.
//
//

#include "GameMap.h"

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
            
            MapData[i][j].ID = -1;
            MapData[i][j].level = -1;
            
        }
    }
}

void GameMap::changeMapByCoord(int row, int col, int level)
{
    MapData[row][col].level = level;
}

void GameMap::changeMapByDirection(GridDirection dir)
{
    switch (dir) {
        case GridUp:
            for (int col = 0 ; col < MapMaxLength; col ++) {
                
                //取出竖排
                std::vector<UnitData> vec;
                for (int row = MapMaxLength - 1; row >= 0 ; row --) {
                    if (MapData[row][col].level != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                //合成方块
                for (std::vector<UnitData>::iterator it = vec.end() - 1; it != vec.begin() - 1; it --) {

                    if ((*it).level == (*(it - 1)).level) {
                        printf("%d,",(*it).level);
                        (*it).level += 1;
                        vec.erase(it - 1);
                    }
                    
                    
                }
                
                //存放竖排方块
                for (int row = MapMaxLength - 1; row >= 0; row --) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col].level = -1;
                        MapData[row][col].ID = -1;
                    }
                }

                
            }

            break;
        case GridDown:
            for (int col = 0 ; col < MapMaxLength; col ++) {
                
                std::vector<UnitData> vec;
                for (int row = 0; row < MapMaxLength ; row ++) {
                    if (MapData[row][col].level != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                //合成方块
                for (std::vector<UnitData>::iterator it = vec.end() - 1; it != vec.begin() - 1; it --) {
                    
                    if ((*it).level == (*(it - 1)).level) {
                        printf("%d,",(*it).level);
                        (*it).level += 1;
                        vec.erase(it - 1);
                    }
                    
                    
                }
                
                for (int row = 0; row < MapMaxLength ; row ++) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col].level = -1;
                        MapData[row][col].ID = -1;
                    }
                }
                
            }
            break;
        case GridLeft:
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                std::vector<UnitData> vec;
                for (int col = 0; col < MapMaxLength ; col ++) {
                    if (MapData[row][col].level != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                //合成方块
                for (std::vector<UnitData>::iterator it = vec.end() - 1; it != vec.begin() - 1; it --) {
                    
                    if ((*it).level == (*(it - 1)).level) {
                        printf("%d,",(*it).level);
                        (*it).level += 1;
                        vec.erase(it - 1);
                    }
                    
                    
                }
                
                for (int col = 0; col < MapMaxLength ; col ++) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col].level = -1;
                        MapData[row][col].ID = -1;
                    }
                }
                
            }
            break;
        case GridRight:
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                std::vector<UnitData> vec;
                for (int col = MapMaxLength - 1; col >= 0; col --) {
                    if (MapData[row][col].level != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                //合成方块
                for (std::vector<UnitData>::iterator it = vec.end() - 1; it != vec.begin() - 1; it --) {
                    
                    if ((*it).level == (*(it - 1)).level) {
                        printf("%d,",(*it).level);
                        (*it).level += 1;
                        vec.erase(it - 1);
                    }
                    
                    
                }
                
                for (int col = MapMaxLength - 1; col >= 0; col --) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col].level = -1;
                        MapData[row][col].ID = -1;
                    }
                }
                
            }
            break;
    }
}

int GameMap::getGridCountByDirection(GridDirection dir, int row, int col)
{
    int count = 0 ;
    
    switch (dir) {
        case GridUp:
            for (int i = row + 1; i < MapMaxLength ; i ++) {
                if (MapData[i][col].level == -1) {
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
                if (MapData[i][col].level == -1) {
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
                if (MapData[row][i].level == -1) {
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
                if (MapData[row][i].level == -1) {
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
    return (MapData[row][col].level != -1);
}

