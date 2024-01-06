#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Delete_Note.h"
#include "properties.h"


void deleteExistNote() //like main function in this file
{
    system("cls");                          //clear the screen
    ///////////////////////////////////////////////////////////////////////////////
    // getting Note ID part
    printf("Note's ID to be deleted: ");
    //delete a Note by ID from the array and CSV/text file
    deleteNote((int)getNoteID());
}

// Function to delete a Note by ID from the array
void deleteNote(int NoteID)
{
    if (NoteID <= 0 || NoteID > MAX_Notes)
    {
        printf("Invalid Note ID.\n");
        return;
    }

    if (!NoteArray[NoteID - 1].isEmpty)
    {
        NoteArray[NoteID - 1].isEmpty = 1; // Set as empty
        printf("Note with ID %d deleted.\n", NoteID);
        // Save to CSV/text file
        saveToCSV(File_Name);
    }
    else printf("No Note with ID %d found.\n", NoteID);
}

/*******************************************      Note's ID Function   ***********************/
char getNoteID()
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
