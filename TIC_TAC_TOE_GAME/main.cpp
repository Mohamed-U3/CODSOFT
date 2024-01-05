#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#include "Game_functions.h"

int main()
{
    init_grid();
    show_grid();

    int moves_counter = 0;
    bool won = 0;
    while(moves_counter < 9)
    {
        X_player_turn();
        moves_counter++;
        won = X_winning_check();
        if(X_winning_check()) cout<<"\nPlayer (X) has won !! \n\tCongratulation :D"<<endl;
        if(moves_counter >= 9 || won) break;

        O_player_turn();
        moves_counter++;
        won = O_winning_check();
        if(O_winning_check()) cout<<"\nPlayer (O) has won !! \n\tCongratulation :D"<<endl;
        if(won) break;
    }

    if(won) cout<<"The game Ended"<<endl;
    else cout<<"\nThe game Ended .. no one has won"<<endl;

    return 0;
}
