#include "controller.h"


void Controller::HandleInput(bool &running, bool &start, Racket &racket) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_LEFT:
          racket.pos_x -= racket.GetRacketSpeed();
          break;
        case SDLK_RIGHT:
          racket.pos_x += racket.GetRacketSpeed();
          break;
        case SDLK_UP:
          start = (start == false ? true : false);
          break;
      }
    }
  }
}