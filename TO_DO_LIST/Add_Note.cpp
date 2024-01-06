#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "properties.h"
#include "Add_Note.h"

Student NoteArray[MAX_Notes];

char noteName[MAX_NAME_LENGTH];
char NoteState;
char NoteID;

/*******************************************     add new Note Function   *************************/
void addNewNote()  //like the main function in this file.
{
    system("cls");                          //clear the screen
    ///////////////////////////////////////////////////////////////////////////////
    // getting student name part
    printf("(maximum 50 characters)\nEnter a Task: ");
    note_name(noteName);
    printf("Task's note: %s\n", noteName);
    ///////////////////////////////////////////////////////////////////////////////
    // getting student Gender part
    printf("\n'D' for Done - 'N' for Not Done\nNote Status: ");
    NoteState = getNoteStatus();
    if(NoteState == 'D')
        printf("Note is Done\n");
    else
        printf("Note still in process\n");
    ///////////////////////////////////////////////////////////////////////////////
    //adding the student in the array of the students.
    NoteID = (char) addNote(noteName, NoteState);
    printf("\n\n >>Student with ID: %d  - is added to the system\n", NoteID);
    // Save to CSV file
    saveToCSV(File_Name);
}

/*******************************************      Note's content Function   *************************/
void note_name(char *name)
{
    fgets(name, MAX_NAME_LENGTH, stdin);

    // Remove the trailing newline character if present
    size_t length = strlen(name);
    if (length > 0 && name[length - 1] == '\n')
        name[length - 1] = '\0';
}

/*******************************************      Note's Status Function   ***********************/
char getNoteStatus()
{
    char Done_not;
    char isValid = 0;

    do {
        Done_not = getchar();

        // Check if the input is valid
        if (Done_not == 'D' || Done_not == 'N' || Done_not == 'd' || Done_not == 'n')
        {
            isValid = 1;
            if (Done_not == 'd')
            {
                Done_not = 'D';
            }
            if (Done_not == 'n')
            {
                Done_not = 'N';
            }
        }
        else printf("Invalid input! Please enter either 'D' for 'Done' or 'N' for 'Not Done'.\n");

        // Clear input buffer
        while (getchar() != '\n'); // Clearing the input buffer

    } while (!isValid);

    return Done_not;
}

/****************************************     add a Note to the array Functions   ***********************/
// Function to add a Note to the array
int addNote(char Note[], char Done_NotDone)
{
    for (int i = 0; i < MAX_Notes; ++i)
    {
        if (NoteArray[i].isEmpty)
        {
            strncpy(NoteArray[i].name, Note, MAX_NAME_LENGTH - 1);
            NoteArray[i].name[MAX_NAME_LENGTH - 1] = '\0';
            NoteArray[i].Done_notDone = Done_NotDone;
            NoteArray[i].NoteID = i + 1; // Assigning Note ID sequentially
            NoteArray[i].isEmpty = 0; // Set as filled
            return NoteArray[i].NoteID;
        }
    }
    printf("Cannot add more Notes. Array is full.\n");
    return -1; // Return -1 indicating failure
}
