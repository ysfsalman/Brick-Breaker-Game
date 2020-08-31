#ifndef BALL_H
#define BALL_H

#include "SDL.h"
#include <vector>

class Ball{
    public:
        Ball(float pos_x, float pos_y, float vec_x)
            :   pos_x(pos_x), pos_y(pos_y), vec_x(vec_x){
                SDL_Point side_x{static_cast<int>(pos_x + speed *vec_x) ,
                    static_cast<int>(pos_y)};
                SDL_Point side_y{static_cast<int>(pos_x),
                    static_cast<int>(pos_y + speed * vec_y) };
            }        
        void UpdatePosition(std::vector<SDL_Point> const obstacle);
        void UpdateSpeed();        
        float pos_x, pos_y;
        SDL_Point side_x, side_y;
    private:
        bool ObstacleExist(std::vector<SDL_Point> const obstacle);
        void UpdateDirection();
        float vec_x, vec_y{-1};
        float speed{0.2f};
        bool isObsX{false}; 
        bool over{false}; 
        

};


#endif