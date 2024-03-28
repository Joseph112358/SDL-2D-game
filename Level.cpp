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
Level::Level(int width, int height, std::vector<int> floorMap,std::vector<int> itemMap){
   this->width = width;
   this->height = height;
   this->floorMap = floorMap;
   this->itemMap = itemMap;
}

int Level::getMapX(){
   return width;
}
 void Level::test(){
            std::cout << "test for level" << std::endl;
        }
