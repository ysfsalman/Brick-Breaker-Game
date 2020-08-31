#include "ball.h"
#include <cmath>
#include <algorithm>
#include <iostream>

bool Ball::ObstacleExist(std::vector<SDL_Point> const obstacle){    
    // check if any object exist at the side of the ball
    side_x = {static_cast<int>(pos_x + speed *vec_x) ,
                    static_cast<int>(pos_y)};
    side_y = {static_cast<int>(pos_x),
                    static_cast<int>(pos_y + speed * vec_y)};
    
    for (auto const&cell : obstacle){
        if (cell.x == side_y.x && cell.y == side_y.y) return true;
        else if (cell.x == side_x.x && cell.y == side_x.y) {
            isObsX = true;            
            return true;
        }          
    }    
    return false;
}

void Ball::UpdateDirection(){
    if (isObsX){
        vec_x *= -1;
        isObsX = false;
    }
    else vec_y *= -1;
}

void Ball::UpdatePosition(std::vector<SDL_Point> const obstacle){
    if (ObstacleExist(obstacle)) UpdateDirection();
    pos_x += speed * vec_x;
    pos_y += speed * vec_y;  
}

void Ball::UpdateSpeed(){
    speed += 0.2;
}
