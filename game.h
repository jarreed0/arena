#ifndef GAME_H
#define GAME_H

#include ".gitignore/header.h"
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>*/

#include <iostream>
using namespace std;
#include <fstream>
#include <vector>

#include "object.h"
#include "audio.h"
#include "entity.h"

#define WIDTH 800
#define HEIGHT 400
#define BLOCK_SIZE 50
#define SPEED 5

class Game {
public:
  Game();
  ~Game();
  void loop();
  void update();
  void input();
  void render();
  void draw(Object o);
  void draw(const char* msg, int x, int y, int r, int g, int b);
  void drawMap();
  void drawHUD();
  void drawFilter();
  void loadMap(const char* filename);
private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running, enablefilter = false, fnine = false;
  int frameCount, timerFPS, lastFrame;
  Object block, arcadebars;
  vector<Object> map;
  Entity player;
  bool left=0, right=0;
};

#endif //GAME_H
