#define MAX_NAME_LENGTH 51 // Maximum length of the name, including the null terminator
#define MAX_Notes    100
#define File_Name       "Note.txt"

#ifndef PROPERTIES_H_INCLUDED
#define PROPERTIES_H_INCLUDED

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char Done_notDone;
    int NoteID;
    int isEmpty; // Flag to indicate if the row is empty (0 = filled, 1 = empty)
} Student;
extern Student NoteArray[MAX_Notes];

//Function Declaration
void initializeStudentArray();
void saveToCSV(const char *filename);
void loadFromCSV(const char *filename);

#endif // PROPERTIES_H_INCLUDED
