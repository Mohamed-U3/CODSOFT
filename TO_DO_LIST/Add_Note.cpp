#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "properties.h"
#include "addSudent.h"

char studentName[MAX_NAME_LENGTH];
char studentGender;
char studentAge;
char studentStudyYear;
char studentID;

/*******************************************     add new Student Function   *************************/
void addNewStudent()  //like the main function in this file.
{
    system("cls");                          //clear the screen
    ///////////////////////////////////////////////////////////////////////////////
    // getting student name part
    printf("student's name (maximum 50 characters): ");
    student_name(studentName);
    printf("Student's name: %s\n", studentName);
    ///////////////////////////////////////////////////////////////////////////////
    // getting student Gender part
    printf("Gender(M/F): ");
    studentGender = getStudentGender();
    if(studentGender == 'M')
        printf("Student's gender: Male\n");
    else
        printf("Student's gender: Female\n");
    ///////////////////////////////////////////////////////////////////////////////
    // getting student Age part
    printf("Age: ");
    studentAge = getStudentAge();
    printf("Student's age (1-30): %d\n", studentAge);
    ///////////////////////////////////////////////////////////////////////////////
    // getting student Study year part
    printf("Study year (1-5): ");
    studentStudyYear = getStudentStudyYear();
    printf("Student Study Year: %d\n", studentStudyYear);
    ///////////////////////////////////////////////////////////////////////////////
    //adding the student in the array of the students.
    studentID = (char) addStudent(studentName, studentGender, studentAge, studentStudyYear);
    printf("\n\n >>Student with ID: %d  - is added to the system\n", studentID);
    // Save to CSV file
    saveToCSV("students.txt");
}

/*******************************************      Student's Name Function   *************************/
void student_name(char *name)
{
    fgets(name, MAX_NAME_LENGTH, stdin);

    // Remove the trailing newline character if present
    size_t length = strlen(name);
    if (length > 0 && name[length - 1] == '\n')
        name[length - 1] = '\0';
}

/*******************************************      Student's Gender Function   ***********************/
char getStudentGender()
{
    char gender;
    char isValid = 0;

    do {
        gender = getchar();

        // Check if the input is valid
        if (gender == 'M' || gender == 'm' || gender == 'F' || gender == 'f')
        {
            isValid = 1;
            if (gender == 'm')
            {
                gender = 'M';
            }
            if (gender == 'f')
            {
                gender = 'F';
            }
        }
        else printf("Invalid input! Please enter either 'M' or 'F'.\n");

        // Clear input buffer
        while (getchar() != '\n'); // Clearing the input buffer

    } while (!isValid);

    return gender;
}

/*******************************************      Student's Age Function   ***********************/
char getStudentAge()
{
    char age;
    char isValid = 0;

    do {
        //printf("Enter student's age (1-30): ");
        scanf("%d", &age);

        // Check if the input is within the valid range
        if (age >= 1 && age <= 30) isValid = 1;
        else printf("Invalid input! Please enter an age between 1 and 30.\n");

        // Clear input buffer
        while (getchar() != '\n'); // Clearing the input buffer

    } while (!isValid);

    return age;
}

/*******************************************      Student's Study Year Function   ***********************/
char getStudentStudyYear()
{
    char study_year;
    char isValid = 0;

    do {
        //printf("Enter student's age (1-5): ");
        scanf("%d", &study_year);

        // Check if the input is within the valid range
        if (study_year >= 1 && study_year <= 5) isValid = 1;
        else printf("Invalid input! Please enter an study year between 1 and 5.\n");

        // Clear input buffer
        while (getchar() != '\n'); // Clearing the input buffer

    } while (!isValid);

    return study_year;
}

/****************************************     add a student to the array Functions   ***********************/
// Function to add a student to the array
int addStudent(char name[], char gender, char age, char studyYear)
{
    for (int i = 0; i < MAX_STUDENTS; ++i)
    {
        if (studentArray[i].isEmpty)
        {
            strncpy(studentArray[i].name, name, MAX_NAME_LENGTH - 1);
            studentArray[i].name[MAX_NAME_LENGTH - 1] = '\0';
            studentArray[i].gender = gender;
            studentArray[i].age = age;
            studentArray[i].studyYear = studyYear;
            studentArray[i].studentID = i + 1; // Assigning student ID sequentially
            studentArray[i].isEmpty = 0; // Set as filled
            return studentArray[i].studentID;
        }
    }
    printf("Cannot add more students. Array is full.\n");
    return -1; // Return -1 indicating failure
}
