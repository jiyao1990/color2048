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
            
            MapData[i][j] = -1;
            
        }
    }
}

void GameMap::changeMapByCoord(int row, int col, int level)
{
    MapData[row][col] = level;
}

void GameMap::changeMapByDirection(GridDirection dir)
{
    switch (dir) {
        case GridUp:
            for (int col = 0 ; col < MapMaxLength; col ++) {
                
                std::vector<int> vec;
                for (int row = MapMaxLength - 1; row >= 0 ; row --) {
                    if (MapData[row][col] != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                for (int row = MapMaxLength - 1; row >= 0; row --) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col] = -1;
                    }
                }
                
            }

            break;
        case GridDown:
            for (int col = 0 ; col < MapMaxLength; col ++) {
                
                std::vector<int> vec;
                for (int row = 0; row < MapMaxLength ; row ++) {
                    if (MapData[row][col] != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                for (int row = 0; row < MapMaxLength ; row ++) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col] = -1;
                    }
                }
                
            }
            break;
        case GridLeft:
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                std::vector<int> vec;
                for (int col = 0; col < MapMaxLength ; col ++) {
                    if (MapData[row][col] != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                for (int col = 0; col < MapMaxLength ; col ++) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col] = -1;
                    }
                }
                
            }
            break;
        case GridRight:
            for (int row = 0 ; row < MapMaxLength; row ++) {
                
                std::vector<int> vec;
                for (int col = MapMaxLength - 1; col >= 0; col --) {
                    if (MapData[row][col] != -1) {
                        vec.push_back(MapData[row][col]);
                    }
                }
                
                for (int col = MapMaxLength - 1; col >= 0; col --) {
                    if (!vec.empty()) {
                        MapData[row][col] = vec.front();
                        vec.erase(vec.begin());
                    }else{
                        MapData[row][col] = -1;
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
            for (int i = row; i < MapMaxLength ; i ++) {
                if (MapData[i][col] == -1) {
                    count ++;
                }
            }
            break;
        case GridDown:
            for (int i = row; i >= 0 ; i --) {
                if (MapData[i][col] == -1) {
                    count ++;
                }
            }
            break;
        case GridLeft:
            for (int i = col; i >= 0 ; i --) {
                if (MapData[row][i] == -1) {
                    count ++;
                }
            }
            break;
        case GridRight:
            for (int i = col; i < MapMaxLength ; i ++) {
                if (MapData[row][i] == -1) {
                    count ++;
                }
            }
            break;
    }
    
    return count;
}


