//
//  Snake.cpp
//  ojp
//
//  Created by Jakub Branicki on 23/06/2020.
//  Copyright © 2020 BRNQ. All rights reserved.
//

#include "Snake.hpp"

Snake::Snake(){fill_board(); place_player(); spawn_food();}

void Snake::place_player() //on board
{
    board[BOARD_SIZE_Y/2][BOARD_SIZE_X/2] = HEAD_UP;
    body_coords init(BOARD_SIZE_X/2, BOARD_SIZE_Y/2, UP);
    coords.push_back(init);
    body_coords n_item(BOARD_SIZE_X/2, BOARD_SIZE_Y/2 + 1, UP);
    coords.push_back(n_item);
}

void Snake::spawn_food() //spawn food in random,empty location
{
    srand(time(NULL));
    int rand_coord_x = 0;
    int rand_coord_y = 0;
    
    while(board[rand_coord_y][rand_coord_x] != SPACE)
    {
        rand_coord_x = rand() % BOARD_SIZE_X;
        rand_coord_y = rand() % BOARD_SIZE_Y;
    }
    
    board[rand_coord_y][rand_coord_x] = FOOD_OBJECT;
}

void Snake::fill_board() // fills vector 'board' with empty board of given size
{
    for(int i = 0; i < BOARD_SIZE_Y; i++)
    {
        std::vector<char> tmp;
        for(int j = 0; j < BOARD_SIZE_X; j++)
        {
            if(i == 0 || i == BOARD_SIZE_Y - 1)
                tmp.push_back(BORDER_CHAR);
            else
            {
                if(j == 0 || j == BOARD_SIZE_X - 1)
                    tmp.push_back(BORDER_CHAR);
                else
                    tmp.push_back(SPACE);
            }
        }
        board.push_back(tmp);
    }
    
}

void Snake::move_player() //moves player based on direction
{
    coords[0].prev_x = coords[0].coord_x;
    coords[0].prev_y = coords[0].coord_y;
    
    switch (coords[0].dir)
    {
        case UP:
            move_head(HEAD_UP, -1 , 0);
            break;
        case DOWN:
            move_head(HEAD_DOWN, 1 , 0);
            break;
        case RIGHT:
            move_head(HEAD_RIGHT, 0 , 1);
            break;
        case LEFT:
            move_head(HEAD_LEFT, 0 , -1);
            break;
    }
    for(int i = 1; i < (coords.size() - 1); i++ ) // following
    {
        coords[i].prev_x = coords[i].coord_x;
        coords[i].prev_y = coords[i].coord_y;
        board[coords[i].coord_y][coords[i].coord_x] = SPACE;
        
        coords[i].coord_x = coords[i-1].prev_x;
        coords[i].coord_y = coords[i-1].prev_y;
        board[coords[i].coord_y][coords[i].coord_x] = BODY_POINT;
    }

}

void Snake::move_head(char head_symbol, int y_change, int x_change)
{
    coords[0].coord_y += y_change;
    coords[0].coord_x += x_change;
    collision_detected = check_collision(coords[0].coord_x, coords[0].coord_y);
    eat_and_grow(coords[0].coord_x, coords[0].coord_y, coords[coords.size() - 1].dir);
    board[coords[0].prev_y][coords[0].prev_x] = SPACE;
    board[coords[0].coord_y][coords[0].coord_x] = head_symbol;
}

void Snake::eat_and_grow(int coord_x, int coord_y, direction last_item_dir)
{
    if(board[coord_y][coord_x] == FOOD_OBJECT)
    {
        int new_char_x;
        int new_char_y;
        switch(last_item_dir) {
            case UP:
                new_char_x = coords[coords.size()-1].coord_x;
                new_char_y = coords[coords.size()-1].coord_y + 1;
                break;
            case DOWN:
                new_char_x = coords[coords.size()-1].coord_x;
                new_char_y = coords[coords.size()-1].coord_y - 1;
                break;
            case LEFT:
                new_char_x = coords[coords.size()-1].coord_x + 1;
                new_char_y = coords[coords.size()-1].coord_y;
                break;
            case RIGHT:
                new_char_x = coords[coords.size()-1].coord_x - 1;
                new_char_y = coords[coords.size()-1].coord_y;
                break;
            default:
                break;
        }
        body_coords n_item(new_char_x, new_char_y, last_item_dir);
        coords.push_back(n_item);
        score += 1;
        spawn_food();
    }
}

bool Snake::check_collision(int c_x, int c_y)
{
    if(board[c_y][c_x] != SPACE && board[c_y][c_x] != FOOD_OBJECT)
    {
        std::cout << "YOU LOST!" << std::endl;
        return true;
    }
    return false;
}

void Snake::change_direction(char c) //player control
{
    switch(c)
    {
        case 'w':
            coords[0].dir = UP;
            break;
        case 'a':
            coords[0].dir = LEFT;
            break;
        case 's':
            coords[0].dir = DOWN;
            break;
        case 'd':
            coords[0].dir = RIGHT;
            break;
    }
}

void Snake::print_board(std::vector<std::vector<char> > board)
{
    clear();
    for (int i = 0; i < BOARD_SIZE_Y; i++)
    {
        for(int j = 0; j < BOARD_SIZE_X; j++)
        {
            addch(board[i][j]);
        }
        addch('\n');
    }
}

void Snake::play()
{
    char in;
    initscr();
    while(!collision_detected)
    {
        timeout(700 - score * 5);
        system("clear");
        if((in = char(getch())))
            change_direction(in);
        //sleep(1);
        print_board(board);
        move_player();
    }
    std::cin>>in;
    endwin();
}
