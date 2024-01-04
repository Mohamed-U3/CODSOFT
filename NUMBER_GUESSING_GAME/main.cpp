#include <iostream>
#include<windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((unsigned) time(NULL));
    int random = 1 + (rand() % 80); //Generating Random number from 0 to 79 then adding 1 to the result to shift the range from 1 to 80
    int answer;
    int rounds = 0;


    // Output text
    cout << " \n\t\t\t Welcome to Guessing the Random Number Game\n";
    cout << "Now .. I Generated random number from 1 >> 80 try to guess the number as much as U want.\n";

    while (answer != random)
    {
        cout << "Please enter your guess: ";
        cin >> answer;
        rounds++;

        if (answer > random+10)
        {
            cout << "the answer is too high! Try again.\n";
        }
        else if (answer > random)
        {
            cout << "the answer is little higher then the random number! Try again.\n";
        }
        else if (answer+10 < random)
        {
            cout << "the answer is too low! Try again.\n";
        }
        else if (answer < random)
        {
            cout << "the answer is little lower then the random number! Try again.\n";
        }
        else
        {
            cout << "Congratulations! You guessed the number in " << rounds << " attempts!\n";
            break;
        }
    }
    return 0;
}
