#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
  : racket(grid_width, grid_height), ball(grid_width / 2 , grid_height-5 , 1),
  grid_width(grid_width), grid_height(grid_height) {
  MakeWall();
  MakeBrick();
}

void Game::MakeWall(){
  for (int i = 0; i < grid_width; i++) wall.push_back({i,0});  
  for (int i = 1; i < grid_height; i++) {
    wall.push_back({0,i});
    wall.push_back({grid_width -1 , i});
  }
}

void Game::MakeBrick(){
  int margin_x{5},  margin_y_top{5}, margin_y_bottom{15};
  for (int i = margin_x; i < grid_width - margin_x; i++){
    for (int j = margin_y_top; j < grid_height -margin_y_bottom; j++) {
      brick.push_back(new SDL_Point({i,j}));
    }
  }
  brick_start = brick.size(); 
}


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool start = false;
  while (running && ball.pos_y < grid_height) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, start, racket);
    // Update game based on game state, 
    // later can be enclosed in Update() instead if state is many
    if (start) Update();
    else {
      // ball will follow racket position
      ball.pos_x = racket.pos_x + racket.GetRacketSize() / 2;
      ball.pos_y = racket.pos_y - 1;
    }
    renderer.Render(racket, ball, wall, brick);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    
  }
}

void Game::Update() {
    //make a vector of points the ball should bounce to
    std::vector<SDL_Point> obstacle = wall; // initialize directly from the ball
    for (auto const &i : racket.body()) obstacle.push_back(i); // obstacle from racket
    for (auto const &i : brick) obstacle.push_back(*i); //obstacle from bricks
    ball.UpdatePosition(obstacle);
    // delete brick if the ball bounce to it
    UpdateBrick();
    // update score
    score = brick_start - brick.size();
}

void Game::UpdateBrick(){
  // delete brick which bumped by ball
  SDL_Point bumped[] = {ball.side_x, ball.side_y};
  for(auto it = brick.begin(); it!= brick.end(); it++){
    for (auto &i : bumped){
      auto *a = *it;
      if(a->x == i.x && a->y == i.y) {       
        delete *it;       // delete brick 
        brick.erase(it);  // erase pointer to brick
        return;
        }
    }
  }  
}

int Game::GetScore() const { return score;}


