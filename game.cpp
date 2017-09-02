#include "game.h"

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
  SDL_SetWindowTitle(win, "Arena");
  TTF_Init();
  running=true;
  font = TTF_OpenFont("res/font.ttf", 24);
  block.setSource(0, 0, 50, 50);
  block.setImage("res/block.png", ren);
  arcadebars.setImage("res/arcadebars.png", ren);
  arcadebars.setSource(0, 0, 2, 2);
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
  drawFilter();
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
 SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, o.getAngle(), NULL, SDL_FLIP_NONE);
}

void Game::draw(const char* msg, int x, int y, int r, int g, int b) {
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
   if(event.key.keysym.sym == SDLK_F9 && !fnine) {fnine = true;if(!enablefilter) {enablefilter = true;}else{enablefilter = false;}}
  }
  if(event.type == SDL_KEYUP) {
	  if(event.key.keysym.sym == SDLK_F9 && fnine) {fnine = false;}
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
  draw(s.c_str(), 5, 1, 0, 0, 0);
}

void Game::drawFilter() {
	if(enablefilter) {
		for(int i = 0; i < (HEIGHT/4); i++) {
			arcadebars.setDest(0, 4 * i, WIDTH, 1);
			draw(arcadebars);
		}
	}
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
                    block.setAngle(0);
                    if(current == 2) {
                      block.setAngle(90);
                    } else if(current == 3 || current == 4 || current == 5 || current == 6) {
                      block.setSource(50, 0, 50, 50);
                      block.setAngle((current-3)*90);
                    } else if(current == 7 || current == 8 || current == 9 || current == 10) {
                      block.setSource(100, 0, 50, 50);
                      block.setAngle((current-7)*90);
                    } else if(current == 11 || current == 12 || current == 13 || current == 14) {
                      block.setSource(150, 0, 50, 50);
                      block.setAngle((current-11)*90);
                    } else if(current == 15) {
                      block.setSource(200, 0, 50, 50);
                    } else {
                      block.setSource(0, 0, 50, 50);                
                    }
                    block.setDest(BLOCK_SIZE*j, BLOCK_SIZE*i, BLOCK_SIZE, BLOCK_SIZE);                                          
                    map.push_back(block);    
                    block.setSource(0, 0, 50, 50);                
                    block.setAngle(0);                    
                  }
          }
  }
  in.close();
}