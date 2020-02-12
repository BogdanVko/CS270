/* CS270 - R6
 *
 * Author: Your name here
 * Date:   2/12/2020
 */

#include "struct.h"
#include<stdio.h>
#include <stdlib.h>
/********** FUNCTION DEFINITIONS **********************************************/

void readStudentAndEnroll(Student** slot) {
  Student *s = (Student *) malloc(sizeof(Student));
  scanf("%s", s->firstName); //  == (*s).firstName
  scanf("%f", &s->qualityPoints);
  scanf("%d", &s->numCredits);
  *slot = s;
}


void displayStudent(Student s){

  float gpa = s.qualityPoints / s.numCredits;
  printf("%s, %.2f\n", s.firstName, gpa);


}