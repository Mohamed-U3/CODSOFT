
#include "properties.h"

void displayStudents()
{
    printf("Student List:\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-3s | %-50s | %-6s | %-4s | %-9s |\n", "ID", "Name", "Gender", "Age", "Study Year");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (!studentArray[i].isEmpty) {
            printf("| %-3d | %-50s | %-6c | %-4d | %-10d |\n", studentArray[i].studentID, studentArray[i].name,
                   studentArray[i].gender, studentArray[i].age, studentArray[i].studyYear);
        }
    }

    printf("-----------------------------------------------------------------------------------------\n");

}
