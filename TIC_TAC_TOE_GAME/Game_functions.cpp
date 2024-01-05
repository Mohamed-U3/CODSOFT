#include <iostream>
#include <string.h>
using namespace std;
#include "Game_functions.h"

char grid[3][3];

void init_grid()
{
    memset(grid, ' ', sizeof(grid));
}

void show_grid()
{
    for(char i = 0; i < 3; i++)
    {
        for(char j = 0; j < 3 ; j++)
        {
            cout<<' '<<grid[i][j]<<' ';
            if(j<2) cout<<'|';
        }
        cout<<endl;
        if(i<2) cout<<"-----------"<<endl;
    }
}

void X_player_turn()
{
    int row,colm;
    inputROW:
    cout<<"\nPlayer (X)\nEnter Row num: ";
    cin>>row;
    if(row > 3 || row < 1)
    {
        cout<<" wrong input try again"<<endl;
        goto inputROW;
    }

    inputColumn:
    cout<<"Enter Column num: ";
    cin>>colm;
    if(colm > 3 || colm < 1)
    {
        cout<<" wrong input try again"<<endl;
        goto inputColumn;
    }
    if(grid[row-1][colm-1] == ' ')
    {
        grid[row-1][colm-1] = 'X';
    }
    else
    {
        cout<<"That place is used already!! .. try again"<<endl;
        goto inputROW;
    }
    show_grid();
}

void O_player_turn()
{
    int row,colm;
    inputROW:
    cout<<"\nPlayer (O)\nEnter Row num: ";
    cin>>row;
    if(row > 3 || row < 1)
    {
        cout<<" wrong input try again"<<endl;
        goto inputROW;
    }

    inputColumn:
    cout<<"Enter Column num: ";
    cin>>colm;
    if(colm > 3 || colm < 1)
    {
        cout<<" wrong input try again"<<endl;
        goto inputColumn;
    }
    if(grid[row-1][colm-1] == ' ')
    {
        grid[row-1][colm-1] = 'O';
    }
    else
    {
        cout<<"That place is used already!! .. try again"<<endl;
        goto inputROW;
    }
    show_grid();
}

bool X_winning_check()
{
    //for Row checking
    char winning_counter = 0;
    bool winner = 0;
    for(char i=0 ; i < 3 ; i++)
    {
        winning_counter = 0; //reset the counter
        for(char j=0 ; j < 3 ; j++)
        {
            if(grid[i][j] == 'X') winning_counter++;
        }
        if(winning_counter > 2) winner = 1;
    }
    if(winner) return winner;

    /////////////////////////////////////////////////////////////////////////////////
    //for column checking
    winning_counter = 0; //reset the counter
    for(char i=0 ; i < 3 ; i++)
    {
        winning_counter = 0; //reset the counter
        for(char j=0 ; j < 3 ; j++)
        {
            if(grid[j][i] == 'X') winning_counter++;
        }
        if(winning_counter > 2) winner = 1;
    }
    if(winner) return winner;

    /////////////////////////////////////////////////////////////////////////////////
    //for \ shape
    winning_counter = 0; //reset the counter
    for(char i=0 ; i < 3 ; i++)
    {
        if(grid[i][i] == 'X') winning_counter++;
    }
    if(winning_counter > 2) return 1;

    /////////////////////////////////////////////////////////////////////////////////
    //for / shape
    winning_counter = 0; //reset the counter
    if(grid[2][0] == 'X') winning_counter++;
    if(grid[1][1] == 'X') winning_counter++;
    if(grid[0][2] == 'X') winning_counter++;
    if(winning_counter > 2) return 1;

    return winner;
}

bool O_winning_check()
{
    //for Row checking
    char winning_counter = 0;
    bool winner = 0;
    for(char i=0 ; i < 3 ; i++)
    {
        winning_counter = 0; //reset the counter
        for(char j=0 ; j < 3 ; j++)
        {
            if(grid[i][j] == 'O') winning_counter++;
        }
        if(winning_counter > 2) winner = 1;
    }
    if(winner) return winner;

    /////////////////////////////////////////////////////////////////////////////////
    //for column checking
    winning_counter = 0; //reset the counter
    for(char i=0 ; i < 3 ; i++)
    {
        winning_counter = 0; //reset the counter
        for(char j=0 ; j < 3 ; j++)
        {
            if(grid[j][i] == 'O') winning_counter++;
        }
        if(winning_counter > 2) winner = 1;
    }
    if(winner) return winner;

    /////////////////////////////////////////////////////////////////////////////////
    //for \ shape
    winning_counter = 0; //reset the counter
    for(char i=0 ; i < 3 ; i++)
    {
        if(grid[i][i] == 'O') winning_counter++;
    }
    if(winning_counter > 2) return 1;

    /////////////////////////////////////////////////////////////////////////////////
    //for / shape
    winning_counter = 0; //reset the counter
    if(grid[2][0] == 'O') winning_counter++;
    if(grid[1][1] == 'O') winning_counter++;
    if(grid[0][2] == 'O') winning_counter++;
    if(winning_counter > 2) return 1;

    return winner;
}
