#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    start:
    double F_number;
    double S_number;
    char operation = 0;
    system("cls");
    cout << "\n\t\t\t SIMPLE CALCULATOR Program" << endl;

    cout << "Enter the First number: ";
    cin >> F_number;

    cout << "Enter the Second number: ";
    cin >> S_number;

    while(operation != '1' && operation != '2' && operation != '3' && operation != '4')
    {
        cout << "[1] for Addition" << endl;
        cout << "[2] for Subtraction" << endl;
        cout << "[3] for Multiplication" << endl;
        cout << "[4] for Division" << endl;
        cout << "Choose the Operation: ";
        cin >> operation;

        if(operation == '1' || operation == '2' || operation == '3' || operation == '4') break;
        else cout << "wrong Input!! .. Try again.. \n";
    }
    double answer = NULL;

    switch (operation)
    {
        case '1': answer = F_number + S_number; break;
        case '2': answer = F_number - S_number; break;
        case '3': answer = F_number * S_number; break;
        case '4': answer = F_number / S_number; break;
    }

    cout << "The answer: " << answer << endl;

    char des = 0;

    while(des != 'Y' && des != 'N' && des != 'y' && des != 'n')
    {
        cout << "\nDo U want to do another Operation ? -- [Y] for Yes / [N] for No" <<endl;
        cin >> des;
        if(des == 'Y' || des == 'N' || des == 'y' || des == 'n')
        {
            if(des == 'Y' || des == 'y') goto start;
            if(des == 'N' || des == 'n')
            {
                exit(0);
            }
        }
        else cout << "wrong Input!! .. Try again.. \n";

    return 0;
}
