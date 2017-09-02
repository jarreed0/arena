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

#define WIDTH 800
#define HEIGHT 400
#define BLOCK_SIZE 50

class Game {
public:
  Game();
  ~Game();
  void loop();
  void update() {}
  void input();
  void render();
  void draw(Object o);
  void draw(const char* msg, int x, int y, int r, int g, int b, int size);
  void drawMap();
  void drawHUD();
  void loadMap(const char* filename);
private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int frameCount, timerFPS, lastFrame;
  Object block;
  vector<Object> map;
};

#endif //GAME_H
