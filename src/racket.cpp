#include "racket.h"
#include "SDL.h"

std::vector<SDL_Point> const Racket::body(){
    std::vector<SDL_Point> body;
    for (int i = 0; i < racket_size; i++){
        SDL_Point body_cell{static_cast<int>(pos_x) + i,
                            pos_y};
        body.push_back(body_cell);
    }
    return body;
}

