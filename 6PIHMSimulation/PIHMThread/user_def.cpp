#include "user_def.h"

//http://codejourneys.blogspot.com/2008/06/qt-simple-example-of-use-of.html

void my_func(void)
{
// time-consuming code
   double sum;
//   for (int i=0; i<100000; i++)
//   {
//      for (int j=0; j<100000; j++)
//      {
//         sum = sum * i / j;
//      }
//   }
    for (int i=0; i<100000; i++)
   for (int j=0; j<100000; j++)
       sum = sum * i / j;

}
