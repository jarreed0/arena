#ifndef GAME_H
#define GAME_H

#include ".gitignore/header.h"

#include <iostream>
using namespace std;

#include <vector>

#include "object.h"
#include "audio.h"

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
private:
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int frameCount, timerFPS, lastFrame;
  vector<Object> map;
};

#endif //GAME_H
