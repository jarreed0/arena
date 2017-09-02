#ifndef GAME_H
#define GAME_H

#include ".gitignore/header.h"
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>*/

#include <iostream>
using namespace std;

#include <vector>

#include "object.h"
#include "audio.h"
#include "canvas.h"
#include "gamemech.h"

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
  void loadMap(int m);
  void drawMap();
  void drawHUD();
  Canvas c;
  GameMech gm;
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
