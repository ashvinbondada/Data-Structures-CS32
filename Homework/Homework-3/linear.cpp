//
//  main.cpp
//  Homework-3-Problem-2
//
//  Created by Ashvin Bondada on 2/7/22.
//

bool somePredicate(double x)
{
    return x < 0; // include <cmath> for std::sin, etc.
}


//The first four take an array of doubles and the number of doubles to examine in the array; the last takes two arrays of doubles and the number of doubles to examine in each:

// Return true if the somePredicate function returns false for at
     // least one of the array elements, false otherwise.
   bool anyFalse(const double a[], int n)
   {
       if (n <= 0) return false;
       if (!somePredicate(a[0]))
           return true;
       return anyFalse(a + 1, n - 1);
   }

     // Return the number of elements in the array for which the
     // somePredicate function returns false.
   int countFalse(const double a[], int n)
   {
       int p = 0;
       if (n <= 0) return p;
       if (!somePredicate(a[0])) p++;
       return p += countFalse(a + 1, n - 1);
   }

     // Return the subscript of the first element in the array for which
     // the somePredicate function returns true.  If there is no such
     // element, return -1.
   int firstTrue(const double a[], int n)
   {
       if (n <= 0) return -1;
       if (somePredicate(a[0]))
           return 0;
       else if (firstTrue(a + 1, n - 1) == -1)
           return -1;
       else
           return firstTrue(a + 1, n - 1) + 1;
       
   }

     // Return the subscript of the largest element in the array (i.e.,
     // return the smallest subscript m such that a[m] >= a[k] for all
     // k such that k >= 0 and k < n).  If there is no such subscript,
     // return -1.
   int locateMax(const double a[], int n)
   {
       if (n <= 0) return -1;
       if (n == 1) return 0;
       int currmax = locateMax(a + 1, n - 1) + 1;
       if (a[0] >= a[currmax]) {
           return 0;
       }
       else
           return currmax;
    }

     // If all n2 elements of a2 appear in the n1 element array a1, in
     // the same order (though not necessarily consecutively), then
     // return true; otherwise (i.e., if the array a1 does not contain
     // a2 as a not-necessarily-contiguous subsequence), return false.
     // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
     // For example, if a1 is the 7 element array
     //    10 50 40 20 50 40 30
     // then the function should return true if a2 is
     //    50 20 30
     // or
     //    50 40 40
     // and it should return false if a2 is
     //    50 30 20
     // or
     //    10 20 20
   bool contains(const double a1[], int n1, const double a2[], int n2)
   {
       if (n2 <= 0)   return true;
       if (n1 <= 0)   return false;
       if (n1 <= 0 && n2 > 0)   return false;
           if (a2[0] == a1[0]) {
               return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
           }
           else {
               return contains(a1 + 1, n1 - 1, a2, n2);
           }
   }
