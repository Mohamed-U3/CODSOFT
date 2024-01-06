#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "properties.h"

/***********************************      Initialize student array Functions   ***********************/
// Initialize student array
void initializeStudentArray()
{
    for (int i = 0; i < MAX_Notes; ++i)
        NoteArray[i].isEmpty = 1; // Initially, all rows are empty
}
/*******************************************      save the student Functions   ***********************/
// Function to save the student array to a CSV/text file
void saveToCSV(const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < MAX_Notes; ++i)
    {
        if (!NoteArray[i].isEmpty)
        {
            fprintf(file, "%d,%s,%c,%d,%d\n", NoteArray[i].NoteID, NoteArray[i].name,
                    NoteArray[i].Done_notDone);
        }
    }

    fclose(file);
}

/*******************************************      load the student Functions   ***********************/
// Function to load the student array from a CSV/text file
void loadFromCSV(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    initializeStudentArray(); // Clear the student array before loading

    int studentID, age, studyYear;
    char name[MAX_NAME_LENGTH], Done_notDone;

    while (fscanf(file, "%d,%[^,],%c,%d,%d\n", &studentID, name, &Done_notDone, &age, &studyYear) != EOF)
    {
        strncpy(NoteArray[studentID - 1].name, name, MAX_NAME_LENGTH - 1);
        NoteArray[studentID - 1].name[MAX_NAME_LENGTH - 1] = '\0';
        NoteArray[studentID - 1].Done_notDone = Done_notDone;
        NoteArray[studentID - 1].NoteID = studentID;
        NoteArray[studentID - 1].isEmpty = 0; // Set as filled
    }

    fclose(file);
}
