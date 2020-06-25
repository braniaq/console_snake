//
//  Snake.hpp
//  ojp
//
//  Created by Jakub Branicki on 23/06/2020.
//  Copyright © 2020 BRNQ. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include <vector>
#include <random>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <ncurses.h>

#define BOARD_SIZE_Y 20
#define BOARD_SIZE_X 40
#define HEAD_UP '^'
#define HEAD_DOWN 'v'
#define HEAD_LEFT '<'
#define HEAD_RIGHT '>'
#define BODY_POINT 'x'
#define FOOD_OBJECT 'o'
#define BORDER_CHAR 'X'
#define SPACE ' '

class Snake
{
private:
    enum direction {UP, DOWN, RIGHT, LEFT};
    struct body_coords
    {
        body_coords(int coord_x, int coord_y, direction dir)
        {
            this -> coord_x = coord_x;
            this -> coord_y = coord_y;
            this -> dir = dir;
        }
        char symbol;
        int coord_x;
        int coord_y;
        int prev_x;
        int prev_y;
        direction dir;
    };
    int score;
    bool collision_detected = false;
    std::vector<body_coords> coords;
    std::vector<std::vector<char> > board;
    
    void print_board(std::vector<std::vector<char> >);
    void fill_board();
    void place_player();
    void spawn_food();
    void eat_and_grow(int, int, direction);
    bool is_direction_right(char);
    bool check_collision(int, int);
    void move_player();
    void move_head(char, int, int);
    void change_direction(char);
public:
    void play();
    Snake();
};
#endif /* Snake_hpp */
