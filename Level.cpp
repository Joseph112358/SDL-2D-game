#include "Level.h"
#include <iostream>
#include <vector>
 // Needs to store
    // Floor layout (layer 0)
    // Room layout (layer 1)
    // Wall layout
    // Objects in room
    // Aspirational: Room dimensions

// Possibly pass in a map signature then reference somewhere?
Level::Level(int mapX, int mapY, std::vector<int> floorMap,std::vector<int> itemMap){
   this->mapX = mapX;
   this->mapY = mapY;
   this->floorMap = floorMap;
   this->itemMap = itemMap;
}

int Level::getMapX(){
   return mapX;
}
 void Level::test(){
            std::cout << "test for level" << std::endl;
        }
