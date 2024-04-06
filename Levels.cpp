#include "Levels.h"
#include "Level.h"
#include <iostream>

Levels::Levels(){
    this->currentLevel = 0;
    generateLevelOne();
    generateLevelTwo();
}

void Levels::incrementLevel(){
    this->currentLevel++;
}

Level* Levels::getCurrentLevel(){
    return this->levels[currentLevel]; 
}

void Levels::generateLevelOne(){
    std::vector<int> floorMap = 
    {0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,2,0,2,3,0,
    0,0,0,1,0,1,0,0,
    0,0,0,1,0,1,0,0,
    0,0,0,0,0,0,0,0, 
    0,0,0,0,0,0,0,0};

    std::vector<int> itemMap = 
    {0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0};
    Level *  levelOne = new Level(8,8, floorMap, itemMap);
    this->levels[0] = levelOne;
}

void Levels::generateLevelTwo(){

    std::vector<int> floorMap = 
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

    std::vector<int> itemMap = 
    {0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0};
    Level *  levelTwo =  new Level(16,8, floorMap, itemMap);
    this->levels[1] = levelTwo;

}