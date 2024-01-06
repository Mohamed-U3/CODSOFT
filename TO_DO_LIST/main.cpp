#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

#include "properties.h"
#include "Add_Note.h"
#include "Delete_Note.h"
#include "Display_Note.h"
#include "Edit_Note.h"

int main()
{
    initializeStudentArray(); // Initialize the student array
    // Load from CSV file
    loadFromCSV(File_Name);

    bool firstLaunch = true; //flag to know if it is the first launch of the code or the Label started it again.
    start:; //label to start the code again
    char C = ' ';

    while(C == ' ')
    {
        system("cls");                          //clear the screen
        printf("1- Add new Note.\n");   //print the menu in the screen
        printf("2- Delete Note by ID.\n");
        printf("3- Display all Notes.\n");
        printf("4- Mark Done by ID.\n");
        printf("5- Exit Program.\n");
        printf("\n\nWrite your choice number: ");

/*
 *   if purpose of this if else statement is to get the function getch() to
 *   the initial state where the function waits for user to write new character
 *   otherwise the function going to write the same character user enter last time
 */
        if(firstLaunch == false) getch(); //Consume the characters in the buffer to get the initial state.
        else firstLaunch = 0;        //if it the first Launch of the code then the state change.

        C = getch();                //wait until user write the new character
    }
    system("cls");                  //clear the screen

    /******************************* Switch cases   ***************************/
    switch (C)
    {
        /******************************* case 1   *****************************/
        case '1':                   //in case A or a is pressed
        addNewNote();               //Add Student by to the array with name,gender,age,and study year.
        while(1)                    //wait until user press any key
        {
            if(kbhit())             //if any key is pressed
            goto start;             //start the code again from beginning
        }
        break;

        /******************************* case 2   *****************************/
        case '2':                   //in case B or b is pressed
        deleteExistNote();       //Delete Student by the ID from the array
        while(1)                    //wait until user press any key
        {
            if(kbhit())             //if any key is pressed
            goto start;             //start the code again from beginning
        }
        break;

        /******************************* case 3   *****************************/
        case '3':                   //in case C or c is pressed
        system("cls");              //clear the screen
        displayNotes();          //Display all students in the array
        while(1)                    //wait until user press any key
        {
            if(kbhit())             //if any key is pressed
            goto start;             //start the code again from beginning
        }
        break;
        /******************************* case 4   *****************************/
        case '4':                   //in case E or e is pressed
        EditExistNote();
        while(1)                    //wait until user press any key
        {
            if(kbhit())             //if any key is pressed
            goto start;         //start the code again from beginning
        }
        break;

        /******************************* case 5   *****************************/
        case '5':                   //in case E or e is pressed
        printf("Exit Program.");
        while(1)                    //wait until user press any key
        {
            if(kbhit())             //if any key is pressed
            break;                  //end the code and Exit
        }
        break;

        /******************************* default case  *************************/
        default:                    //in case anything else is pressed
        printf("Wrong choose .. try again.\n\n\n");
        while(1)                    //wait until user press any key
        {
            if(kbhit())             //if any key is pressed
                goto start;         //start the code again from beginning
        }
    }

    return 0;
}
