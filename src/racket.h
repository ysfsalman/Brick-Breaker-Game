#ifndef RACKET_H
#define RACKET_H

#include <vector>
#include "SDL.h"

class Racket{
    public:        
        Racket(int grid_width, int grid_height)
            :   grid_width(grid_width),
                pos_x(grid_width / 2),
                pos_y(grid_height - 5){}
        
        std::vector<SDL_Point> const body();
        float pos_x;         
        int const pos_y; //racket y-axis position won't change       
        // getter
        int GetRacketSize() { return racket_size;}
        int GetRacketSpeed() { return racket_speed;}
    private:
        float racket_speed{1.7};     
        int racket_size{5};                
        int grid_width;              
};


#endif