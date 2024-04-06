#pragma once
#include "Level.h"
#include <iostream>

class Levels {
public:
    Levels();
    Level * levels[3];
    void incrementLevel();
    Level * getCurrentLevel();
private:
    int currentLevel;
    void generateLevelOne();
    void generateLevelTwo();
};