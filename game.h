#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
private:
  bool block, release;
  SDL_Renderer* ren;
  SDL_Window* win;
  TTF_Font *font;
  bool running;
  int frameCount, timerFPS, lastFrame;
  SDL_GameController *pad;
  SDL_Joystick *joy;
  int instanceID;
};

#endif //GAME_H
