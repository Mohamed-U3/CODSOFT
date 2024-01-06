#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "properties.h"
#include "Edit_Note.h"

void EditExistNote() //like main function in this file
{
    ///////////////////////////////////////////////////////////////////////////////
    // getting Note ID part
    printf("Note's ID Mark as Done: ");
    //Edit a Note by ID from the array and CSV/text file
    EditNote((int)GetNoteID());
}

/*******************************************      Edit Note Function   ***********************/
// Function to delete a Note by ID from the array
void EditNote(int NoteID)
{
    if (NoteID <= 0 || NoteID > MAX_Notes)
    {
        printf("Invalid Note ID.\n");
        return;
    }

    if (!NoteArray[NoteID - 1].isEmpty)
    {
        if(NoteArray[NoteID - 1].Done_notDone == 'D')
        {
            printf("Note with ID %d Is already Done Before.\n", NoteID);
            Again:
            printf("Do You Wanna Mark it as Not Done ? [Y] for yes - [N] for No.\n >>");
            char choise;
            cin>>choise;
            if(choise == 'Y' || choise == 'y')
            {
                NoteArray[NoteID - 1].Done_notDone = 'N';
                printf("Note with ID:%d is now marked as Not Done.\n", NoteID);
            }
            else if (choise == 'N' || choise == 'n')
            {
                NoteArray[NoteID - 1].Done_notDone = 'D';
                printf("Note with ID:%d is marked as Done.\n", NoteID);
            }
            else
            {
                printf("Wrong Choice .. Try again..\n");
                goto Again;
            }
        }
        else
        {
            NoteArray[NoteID - 1].Done_notDone = 'D';
            printf("Note with ID:%d is now marked As Done.\n", NoteID);
        }
        // Save to CSV/text file
        saveToCSV(File_Name);
    }
    else printf("No Note with ID %d found.\n", NoteID);
}


/*******************************************      Note's ID Function   ***********************/
char GetNoteID()
{
    char ID;
    char isValid = 0;

    do {
        scanf("%d", &ID);

        // Check if the input is within the valid range
        if (ID >= 1 && ID <= 100) isValid = 1;
        else printf("Invalid input! Please enter an ID between 1 and 100.\n");

        // Clear input buffer
        while (getchar() != '\n'); // Clearing the input buffer

    } while (!isValid);

    return ID;
}
