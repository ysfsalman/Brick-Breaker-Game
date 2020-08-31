#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "racket.h"
#include "ball.h"

#include <vector>


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;  
 private:
  Racket racket;
  std::vector<SDL_Point> wall;
  std::vector<SDL_Point*> brick;
  Ball ball;
  int grid_width, grid_height;
  int score{0};
  void Update();
  void MakeWall();
  void MakeBrick();
  void UpdateBrick();
  int brick_start ;  
};

#endif