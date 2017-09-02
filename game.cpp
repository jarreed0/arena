#include "game.h"

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
  SDL_SetWindowTitle(win, "Arena");
  TTF_Init();
  running=true;
  font = TTF_OpenFont("Sans.ttf", 24);
  block.setSource(0, 0, 50, 50);
  block.setImage("res/block.png", ren);
  loadMap("res/1.map");
  loop();
}

Game::~Game() {
  TTF_Quit();
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

void Game::loop() {
  static int anim;
  static bool up;
  while(running) {

    lastFrame=SDL_GetTicks();
    static int lastTime;
    if(lastFrame >= (lastTime+1000)) {
      lastTime=lastFrame;
      frameCount=0;
    }

    render();
    input();
    update();
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(ren, 135, 206, 250, 255);
  SDL_Rect rect;
  rect.x=rect.y=0;
  rect.w=800;
  rect.h=500;
  SDL_RenderFillRect(ren, &rect);

  drawMap();
  drawHUD();

  frameCount++;
  int timerFPS = SDL_GetTicks()-lastFrame;
  if(timerFPS<(1000/60)) {
    SDL_Delay((1000/60)-timerFPS);
  }

  SDL_RenderPresent(ren);
}


void Game::draw(Object o) {
 SDL_Rect dest = o.getDest();
 SDL_Rect src = o.getSource();
 SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void Game::draw(const char* msg, int x, int y, int r, int g, int b, int size) {
 SDL_Surface* surf;
 SDL_Texture* tex;
 SDL_Color color;
 color.r=r;
 color.g=g;
 color.b=b;
 color.a=255;
 SDL_Rect rect;
 surf = TTF_RenderText_Solid(font, msg, color);
 tex = SDL_CreateTextureFromSurface(ren, surf);
 rect.x=x;
 rect.y=y;
 rect.w=surf->w;
 rect.h=surf->h;
 SDL_FreeSurface(surf);
 SDL_RenderCopy(ren, tex, NULL, &rect);
 SDL_DestroyTexture(tex);
}

void Game::input() {
SDL_Event event;
while(SDL_PollEvent(&event)) {
  if(event.type == SDL_QUIT) {running=false;cout << "Quiting\n";}
if(event.type == SDL_KEYDOWN) {
  if(event.key.keysym.sym == SDLK_ESCAPE) {running=0;}
}
if(event.type == SDL_KEYUP) {
}
}
}


void Game::loadMap(int m) {
  map.clear();
  map.empty();
  if(m == 1) {
    for(int i=0; i<16; i++) {
      block.setDest(BLOCK_SIZE*i, 0, BLOCK_SIZE, BLOCK_SIZE);
      map.push_back(block);
      block.setDest(BLOCK_SIZE*i, 450, BLOCK_SIZE, BLOCK_SIZE);
      map.push_back(block);
    }
    for(int i=0; i<8; i++) {
      block.setDest(0, (i+BLOCK_SIZE)+BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
      map.push_back(block);
      block.setDest(750, (i*BLOCK_SIZE)+BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
      map.push_back(block);
    }
  }
}

void Game::drawMap() {
  for(int i=0; i<map.size(); i++) {
    draw(map[i]);
  }
}

void Game::drawHUD() {
  int fps = 6;
  string s = "FPS: " + to_string(fps);
  draw(s.c_str(), 5, 1, 0, 255, 0, 24);
}

void Game::loadMap(const char* filename) {
  map.clear();
  map.empty();
  ifstream in(filename);
  if(!in.is_open()) {
          std::cout << "Problem with loading the file" << std::endl;
          return;
  }
  int current;
  for(int i=0; i<(HEIGHT/BLOCK_SIZE); i++) {
          for(int j=0; j<(WIDTH/BLOCK_SIZE); j++) {
                  if(in.eof()) {
                          std::cout << "File end reached too soon" << std::endl;
                          return;                        
                  }
                  in >> current;
                  if(current != 0) {
                    block.setDest(BLOCK_SIZE*j, BLOCK_SIZE*i, BLOCK_SIZE, BLOCK_SIZE);
                    map.push_back(block);                    
                  }
          }
  }
  in.close();
}