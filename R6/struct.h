/* CS270 - R6
 *
 * Author: Your name here
 * Date:   2/12/2020
 */
 
/********** STRUCTURE DEFINITION **********************************************/

// Structure that represents a student
typedef struct
{
  char firstName[80];
  float qualityPoints;
  int numCredits;
} Student;

// Structure that represents a class roster
// TODO: Declare this structure

typedef struct {
int numStudents;
Student** students;

} ClassRoster;
/********** FUNCTION PROTOTYPES ***********************************************/

void readStudentAndEnroll(Student **slot);

void displayStudent(Student s);