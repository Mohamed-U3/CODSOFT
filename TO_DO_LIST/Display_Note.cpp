#include <cstdio>
#include "properties.h"

void displayNotes()
{
    printf("Tasks/Notes List:\n");
    printf("-----------------------------------------------------------------------\n");
    printf("| %-3s | %-50s | %-8s |\n", "ID", "Name", "Done/Not");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_Notes; ++i) {
        if (!NoteArray[i].isEmpty) {
            printf("| %-3d | %-50s | %-8c |\n", NoteArray[i].NoteID, NoteArray[i].name,
                   NoteArray[i].Done_notDone);
        }
    }

    printf("-----------------------------------------------------------------------\n");

}
