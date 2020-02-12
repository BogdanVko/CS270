 /** @mainpage 
   *  \htmlinclude "R6.html"
   */
/* CS270 - R6
 *
 * Author: BV
 * Date:   2/12/2020
 */
#include<stdio.h>
#include <stdlib.h>
#include "struct.h"

int main(int argc, const char **argv)
{
  int number_of_students;
  // TODO: Complete the main function
  scanf("%d", &number_of_students);

  ClassRoster roster;
  roster.numStudents = number_of_students;
  roster.students = calloc(number_of_students, sizeof(Student*));

  for (int i = 0; i < number_of_students; i++){
    
    readStudentAndEnroll(&(roster.students[i]));
  }

  for(int i = 0; i < number_of_students; i++){
    displayStudent(*roster.students[i]);
    
    free(roster.students[i]);
  }

  free(roster.students);

  return 0;
}

