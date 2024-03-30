#pragma once
#include <vector>
class Level {
    // private:
    //     int floorMap[64];
    //     int floorDetails[64];
    public:
        Level(int mapX, int mapY, std::vector<int> floorMap, std::vector<int> itemMap);
        int mapX;
        int mapY;
        std::vector<int> floorMap;
        std::vector<int> itemMap;
        void test();
        int getMapX();
};