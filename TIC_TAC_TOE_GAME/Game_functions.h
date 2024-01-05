#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

//array decliration
extern char grid[3][3];

//functions decliration
void init_grid();
void show_grid();
void X_player_turn();
void O_player_turn();
bool X_winning_check();
bool O_winning_check();

#endif // GAME_FUNCTIONS_H_INCLUDED
