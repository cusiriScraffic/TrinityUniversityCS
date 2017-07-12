#include <math.h>
#include <string.h>
#include <iostream>

int main()
{
   double N=200000000000, r=1.1, pr, theDifferenceBetweenRand1=(r-1)/2;
   while (pr=r, theDifferenceBetweenRand1 != 0)
   {
      double rx=1, rt=0;
      int i=0;
      while (++i<=5000)
      {
         rt-=(300-i)*rx, rx=rx*r;
      }
      if (rt>N)
      {
         r-=theDifferenceBetweenRand1, theDifferenceBetweenRand1=(pr-r)/2;
      }
      else if (rt<N)
      {
         r+=theDifferenceBetweenRand1, theDifferenceBetweenRand1=(r-pr)/2;
      }
   }
   std::cout << r <<std::endl;
   return 0;
};

/*Literally just brute force, manually then  adjust to fit*/