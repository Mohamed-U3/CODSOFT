#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "properties.h"
#include "deleteStudent.h"


void deleteExistStudent() //like main function in this file
{
    system("cls");                          //clear the screen
    ///////////////////////////////////////////////////////////////////////////////
    // getting student ID part
    printf("student's ID to be deleted: ");
    //delete a student by ID from the array and CSV/text file
    deleteStudent((int)getStudentId());
}

// Function to delete a student by ID from the array
void deleteStudent(int studentID)
{
    if (studentID <= 0 || studentID > MAX_STUDENTS)
    {
        printf("Invalid student ID.\n");
        return;
    }

    if (!studentArray[studentID - 1].isEmpty)
    {
        studentArray[studentID - 1].isEmpty = 1; // Set as empty
        printf("Student with ID %d deleted.\n", studentID);
        // Save to CSV/text file
        saveToCSV("students.txt");
    }
    else printf("No student with ID %d found.\n", studentID);
}

/*******************************************      Student's ID Function   ***********************/
char getStudentId()
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
