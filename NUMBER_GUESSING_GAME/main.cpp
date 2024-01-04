#include <iostream>
#include<windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand((unsigned) time(NULL));
    for(int x=0; x<30; x++)
    {
        int random = 1 + (rand() % 80); //Generating Random number from 0 to 79 then adding 1 to the result to shift the range from 1 to 80

        cout<<random<<"\n";

    }

    return 0;
}
