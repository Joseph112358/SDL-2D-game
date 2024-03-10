#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <SDL.h>
#include <stdarg.h>
#include <SDL_image.h>

// TODO
// Sort out Image dll
// Clean texturing code


const int WIDTH = 512, HEIGHT = 512;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool running;
int playerX = 0 ,  playerY = 0;
SDL_Texture* playerTex = nullptr;
SDL_Surface* tmpSurface = nullptr;
SDL_Texture* atlasTex = nullptr;

// length of x is important for rendering maths.
// x = 16 (formerly 8)
int mapX = 8;
int mapY = 8;
int fullMap[] ={0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,2,0,2,3,0,
                0,0,0,1,0,1,0,0,
                0,0,0,1,0,1,0,0,
                0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0
              };

int emptyMap[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int map[sizeof(fullMap)];

void populateMap(){
    std::memcpy(map,fullMap, sizeof(map));
}


void drawMap();
void drawPlayer();


int main(int argc, char** args) {
  populateMap(); // Easiest way to switch maps for testing
  playerX = 0, playerY = 0;
  SDL_Event e;
  SDL_Init(SDL_INIT_EVERYTHING);
  running = true;

  SDL_CreateWindowAndRenderer(448,448,0, &window,&renderer);

  while(running){
    // TODO: Move keyboard logic to its own function if possible
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        running = false;
      }
      else if(e.type == SDL_KEYDOWN){
      // Need to check out of bounds
        switch(e.key.keysym.sym){
          int nextCoords;
          case SDLK_RIGHT:
              nextCoords = playerY*mapX+playerX+1;
              if(map[nextCoords]==0 && playerX < mapX -1){
                    playerX += 1;
              }
             break;
          case SDLK_LEFT:
              nextCoords = playerY*mapX+playerX-1;
              if(map[nextCoords]==0 && playerX > 0){
                    playerX -= 1;
              }
              break;
          case SDLK_UP:
              nextCoords = (playerY-1)*mapX+playerX;
              if(map[nextCoords]==0 && playerY > 0){
                    playerY -= 1;
              }
              break;
           case SDLK_DOWN:
              nextCoords = (playerY+1)*mapX+playerX;
              if(map[nextCoords]==0 && playerY < mapY -1){
                    playerY += 1;
              } 
              break;
        }
      }
    }


  SDL_SetRenderDrawColor(renderer,0,0,0,255); // set background color to black
  SDL_RenderClear(renderer);
  tmpSurface = IMG_Load("Atlas3.png");

  // Maybe an initialise / load textures function
  drawMap();
  drawPlayer();
  // Then destroy textures function?


  SDL_RenderPresent(renderer);
  SDL_FreeSurface(tmpSurface);
  
  }
  return 0;
}


void drawPlayer(){
  playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);

  int middleOfScreen = 192; // player should always be at middle of screen
  SDL_Rect player {middleOfScreen,middleOfScreen,64,64}; // not deprected (yet)
  SDL_Rect playerAtlasCoords {0, 256,256,256};

  // Need to manipulate player coords
  player.x = middleOfScreen;
  player.y = middleOfScreen;
  SDL_RenderCopy(renderer,playerTex,&playerAtlasCoords,&player);
  SDL_DestroyTexture(playerTex);
}


// Work out where to draw, then what to draw.
void drawMap(){
  for(int i = -2; i <3; i++){
    for(int j = -2; j <3;j++){
      atlasTex = SDL_CreateTextureFromSurface(renderer, tmpSurface); // try to move?
      if(!(i == 0 && j == 0)){ // i.e. if not player position (middle of screen)
        int middleOfScreen = 192;
        int currentSquareX = middleOfScreen + (i *64); // change var name, maybe tileScreenCoords?
        int currentSquareY = middleOfScreen + (j *64);

        // Code for working out tile
        int currentTileX = playerX +i;
        int currentTileY = (playerY +j);
        int currentTile = currentTileY*mapX+currentTileX;


        bool inMap = true;
        if(currentTileY < 0) inMap = false;
        if(currentTileY > 7) inMap = false;
        if(currentTileX < 0) inMap = false;
        if(currentTileX > 7) inMap = false;
       

      SDL_Rect currentTileDimensions {currentSquareX, currentSquareY,64,64};

        // out of range -> brick
        // 0 -> background screen
        // 1 -> grass
        // 2 -> dirt

      if(inMap){
        if(map[currentTile]==1){
           SDL_Rect dirtAtlasCoords {0, 256,256,256};
           SDL_RenderCopy(renderer,atlasTex,&dirtAtlasCoords,&currentTileDimensions);
        }
        else if(map[currentTile] == 2){
           SDL_Rect grassAtlasCoords {0, 0,256,256};
           SDL_RenderCopy(renderer,atlasTex,&grassAtlasCoords,&currentTileDimensions);
        }
        else if(map[currentTile] == 3){
           SDL_Rect grassTopAtlasCoords {256, 0,256,256};
           SDL_RenderCopy(renderer,atlasTex,&grassTopAtlasCoords,&currentTileDimensions);
        }
        else {
       SDL_SetRenderDrawColor(renderer,65,90,90,255);
       SDL_Rect block {currentSquareX, currentSquareY,64,64};
       SDL_RenderFillRect(renderer, &block);
        }
      } 
      else { // Not in map, so draw brick
          SDL_Rect brickAtlasCoords {256, 256,256,256};
          SDL_RenderCopy(renderer,atlasTex,&brickAtlasCoords,&currentTileDimensions);
      }
      SDL_DestroyTexture(atlasTex);
    }
    }
  }
}

// command to compile
// g++ main.cpp -IC:\Dev\SDL2-2.30.0\i686-w64-mingw32\include\SDL2 -LC:\Dev\SDL2-2.30.0\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -o 01_hello_SDL
