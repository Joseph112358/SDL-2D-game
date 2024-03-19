#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <SDL.h>
#include <stdarg.h>
#include <SDL_image.h>
#include <memory>


const int WIDTH = 512, HEIGHT = 512, middleOfScreen = 192;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool running = true;
int playerX = 0 ,  playerY = 0;
std::string playerDirection = "right";
int cakeLocation = 5;
int score = 0;
SDL_Surface* tmpSurface = nullptr;
SDL_Texture* atlasTex = nullptr;
SDL_Texture* playerTex = nullptr;
SDL_Texture* cakeTex = nullptr;
SDL_Texture* scoreTex = nullptr;

// length of x is important for rendering maths.
// x = 16 
int mapX = 8;
int mapY = 8;
int fullMap[64] ={0,0,0,0,0,0,0,0,
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

int map[64];

void populateMap(){
    std::memcpy(map,fullMap, sizeof(map));
}

void handleKeyboardInput(SDL_Event e);
void drawMap();
void drawPlayer();
void drawCakes();
void checkCakeCollision();
void newCake();
void drawScore();


int main(int argc, char** args) {
  populateMap(); // Easiest way to switch maps for testing
  SDL_Event e;
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_CreateWindowAndRenderer(448,448,0, &window,&renderer);

  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  while(running){

    frameStart = SDL_GetTicks();

    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        running = false;
      }
      else if(e.type == SDL_KEYDOWN){
        handleKeyboardInput(e);
      }
    }


  SDL_SetRenderDrawColor(renderer,0,0,0,255); // set background color to black
  SDL_RenderClear(renderer);

  drawMap();
  // drawCakes();
  checkCakeCollision();
  drawCakes();
  drawPlayer();
  drawScore();
  
  SDL_RenderPresent(renderer);

  frameTime = SDL_GetTicks() - frameStart;

  if(frameDelay > frameTime){
    SDL_Delay(frameDelay - frameTime);
  }
  }
  return 0;
}

// Handle user input
void handleKeyboardInput(SDL_Event e){
   int nextCoords;
  switch(e.key.keysym.sym){
    case SDLK_RIGHT:
              nextCoords = playerY*mapX+playerX+1;
              if(map[nextCoords]==0 && playerX < mapX -1){
                    playerX += 1;
                    playerDirection = "right";
              }
             break;
    case SDLK_LEFT:
              nextCoords = playerY*mapX+playerX-1;
              if(map[nextCoords]==0 && playerX > 0){
                    playerX -= 1;
                    playerDirection = "left";
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

// Rendering

void drawPlayer(){
  tmpSurface = IMG_Load("kid-with-balloon-2.png");
  playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  SDL_Rect playerSpriteCoords;
  if(playerDirection == "right"){
    playerSpriteCoords = {0, 0, 64, 64};
  } else {
    playerSpriteCoords = {64, 0, 64, 64};
  }

  // int middleOfScreen = 192; // player should always be at middle of screen
  SDL_Rect player {middleOfScreen,middleOfScreen,64,64}; // not deprected (yet)
  SDL_Rect playerAtlasCoords {0, 256,256,256};

  // Need to manipulate player coords
  player.x = middleOfScreen;
  player.y = middleOfScreen;
  SDL_RenderCopy(renderer,playerTex, &playerSpriteCoords,&player);
  SDL_DestroyTexture(playerTex);
  SDL_FreeSurface(tmpSurface);
}


// Work out where to draw, then what to draw.
void drawMap(){
  tmpSurface = IMG_Load("Atlas3.png");
  for(int i = -2; i <3; i++){
    for(int j = -2; j <3;j++){
      atlasTex = SDL_CreateTextureFromSurface(renderer, tmpSurface); // try to move?
        // int middleOfScreen = 192;
        int currentSquareX = middleOfScreen + (i *64); // change var name, maybe tileScreenCoords?
        int currentSquareY = middleOfScreen + (j *64);

        // Code for working out tile
        int currentTileX = playerX +i;
        int currentTileY = (playerY +j);
        int currentTile = currentTileY*mapX+currentTileX;

        
        bool inMap = true;
        if(currentTileX > 7 || currentTileX < 0 || currentTileY > 7 || currentTileY < 0) inMap = false;
       

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
  SDL_FreeSurface(tmpSurface);
}

void drawCakes(){
  tmpSurface = IMG_Load("cake-candle-sprite.png");
  // Where is the cake?
  int cakeX = (cakeLocation % mapX);
  int cakeY = (cakeLocation / mapY);
  int differenceX = cakeX - playerX;
  int differenceY = cakeY - playerY;
  // Is it in range / site ? (should it be drawn)
  if(abs(differenceX) < 3 && abs(differenceY) < 3){
  cakeTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);

  // Add 3 to both becasue map is always 3 * 3 tiles in from screen.
  SDL_Rect cakeDimensions {(3 + differenceX) * 64 ,( 3 + differenceY) * 64,64,64};
  SDL_RenderCopy(renderer,cakeTex,NULL,&cakeDimensions);
  SDL_DestroyTexture(cakeTex);
  }
  SDL_FreeSurface(tmpSurface);
}

void checkCakeCollision(){
  if(cakeLocation == playerX + mapX*playerY){
    score ++;
    std::cout << score << std::endl;
    newCake();
  }
}

void newCake(){
    int newCakelocation = rand() %64;
    while(map[newCakelocation] != 0){
      newCakelocation = rand() %64;
    }
    cakeLocation = newCakelocation;
}

// The score atlas is wrong -> start at 0
void drawScore(){
  if(score > 10) return;
  tmpSurface = IMG_Load("numbers-sprite-01.png");
  scoreTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  int atlasX = score % 5;
  int atlasY = score / 5;
  SDL_Rect numberAtlasCoords {atlasX *32, atlasY * 32,32,32};
  SDL_Rect scoreLocation {384, 384,64,64};
  SDL_RenderCopy(renderer,scoreTex,&numberAtlasCoords,&scoreLocation);
  //  SDL_RenderCopy(renderer,playerTex, &playerSpriteCoords,&player);

  SDL_DestroyTexture(scoreTex);
  SDL_FreeSurface(tmpSurface);
  
}

// command to compile
// g++ main.cpp -IC:\Dev\SDL2-2.30.0\i686-w64-mingw32\include\SDL2 -LC:\Dev\SDL2-2.30.0\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -o 01_hello_SDL
