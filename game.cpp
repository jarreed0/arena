#include "game.h"

Game::Game() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(800, 500, 0, &win, &ren);
  SDL_SetWindowTitle(win, "Arena");
  TTF_Init();
  running=true;
  font = TTF_OpenFont("Sans.ttf", 24);
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
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_Rect rect;
  rect.x=rect.y=0;
  rect.w=800;
  rect.h=500;
  SDL_RenderFillRect(ren, &rect);

  int fps = 6;
  string s = "FPS: " + to_string(fps);
  draw(s.c_str(), 5, 1, 0, 255, 0, 24);

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

void Game::AddController(int id) {
    if(SDL_IsGameController(id)) {
        SDL_GameController *pad = SDL_GameControllerOpen(id);

        if( pad ) {
            SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
            int instanceID = SDL_JoystickInstanceID(joy);

            // You can add to your own map of joystick IDs to controllers here.
            //YOUR_FUNCTION_THAT_CREATES_A_MAPPING( id, pad );
        }
    }
}

void Game::RemoveController(int id) {
    //SDL_GameController *pad = YOUR_FUNCTION_THAT_RETRIEVES_A_MAPPING( id );
    SDL_GameControllerClose(pad);
}

void Game::OnControllerButton(const SDL_ControllerButtonEvent sdlEvent) {
    // Button presses and axis movements both sent here as SDL_ControllerButtonEvent structures
}

void Game::OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent) {
    // Axis movements and button presses both sent here as SDL_ControllerAxisEvent structures
}

void Game::EventLoop() {
    SDL_Event sdlEvent;

    while( SDL_PollEvent( &sdlEvent ) ) {
        switch( sdlEvent.type ) {

        case SDL_CONTROLLERDEVICEADDED:
            //AddController(sdlEvent.cdevice);
            break;

        case SDL_CONTROLLERDEVICEREMOVED:
            //RemoveController(sdlEvent.cdevice);
            break;

        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            OnControllerButton(sdlEvent.cbutton);
            break;

        case SDL_CONTROLLERAXISMOTION:
            OnControllerAxis(sdlEvent.caxis);
            break;

        // YOUR OTHER EVENT HANDLING HERE

        }
    }
}
