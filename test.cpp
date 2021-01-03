#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

unsigned long long int error_function (int allowed, int* rvalue, int* n, int start, int end, int k)
{
 unsigned long long int err = 0;
 for (int i=start-1; i<end; i++)
 {
   err = err + round(pow((rvalue[i]-allowed), 2))*n[i];
 }
 /*if (start ==1 && end ==4)
 {
   cout<<"start=1 end=4 "<<err<<endl;
 }*/

 return err;
}

unsigned long long int choose_allowed (unsigned long long int** DP, int* allowed, int* rvalue, int* n, int d, int k)
// return the total error of chosen
// C(i, j) = k s.t. C(k, j-1) + F(k+1, i) is smallest
// build the dynamic programming table DP while calling recursively

{
 unsigned long long int err , minerr, minj, min, total;
 //Base Case

 if (k == 1)
 {
   allowed[k-1] = 0;
   DP[0][0] = 0;
   for (int i=2; i<=d; i++)
   {

     minj = 0;
     total = 0;
     //cout<<"error_function (0, rvalue, n, 1, "<<i<<" , k) = "<<err<<endl;
/*
     for (int j=0; j<i; j++ )
     {
       minj = minj + rvalue[j] * n[j];
       total = total + n[j];
     }
     minj = round(static_cast<double>(minj) / total);
     minerr = error_function (minj, rvalue, n, 1, i , k);
     err = error_function (minj+1, rvalue, n, 1, i , k);
     if (err < minerr)
      minerr = err;
     DP[i-1][k-1] = minerr;*/

     minerr = error_function (rvalue[0], rvalue, n, 1, i , k);
     for (int j=rvalue[0]+1; j<=rvalue[i-1]; j++)
     {
       allowed[k-1] = j;
       err = error_function(j, rvalue, n, 1, i, k);
       if (err < minerr)
       {
         minerr = err;
         minj = j;
       }
       else
         break;
     }
     DP[i-1][k-1] = minerr;


     cout<<minj<<endl;
   }

   return DP[d-1][k-1] ;
 }

 //recursive call
 //for every i,
 //choose the m  s.t. DP[m][j-1]  + F(m+1, i) is smallest
 choose_allowed (DP, allowed, rvalue, n, d, k-1);


 for (int i=1; i<d; i++)
 {
   for (int j=0; j<i; j++)
   {
     /*
     minj = 0;
     total = 0;

     for (int w=j+1; w<=i; w++ )
     {
       minj = minj + rvalue[w] * n[w];
       total = total + n[w];
     }

     minj = round(minj / total);
     minerr = DP[j][k-2] + error_function (minj, rvalue, n, j+2, i+1, k);
     err = DP[j][k-2] + error_function (minj + 1, rvalue, n, j+2, i+1, k);
     if (err < minerr)
      minerr = err;*/



     minerr = DP[j][k-2] + error_function (rvalue[j], rvalue, n, j+2, i+1, k);
     for (int w = rvalue[j]+1; w < rvalue[i]+1; w++)
     {
       err = DP[j][k-2] + error_function (w, rvalue, n, j+2, i+1, k);
       if (err < minerr)
       {
         minerr = err;
         minj = w;
       }
       else
       {
         break;
       }
     }
     //cout<<"minerr = "<<minerr<<" "<<j<<endl;


     if (j == 0)
     {
       min = minerr;
     }
     else if (minerr < min)
     {
       min = minerr;
     }
   }
   //cout<<"min = "<<min<<endl;
   DP [i][k-1] = min;
 }



 return DP[d-1][k-1] ;

}

int main()
{
 int d = 0; // number of distinct red values
 int k = 0; // number of red values allowed
 cin>>d>>k;
 int* allowed = new int [k];
 for (int i=0; i<k; i++)
 {
   allowed[i] = -1;
 }
 int* rvalue = new int [d];
 int* n = new int [d];
 for (int i=0; i<d; i++)
 {
   cin>>rvalue[i]>>n[i];
 }

 unsigned long long int** DP = new unsigned long long int* [d];
 for (int i=0; i<d; i++)
 {
   DP[i] = new unsigned long long int [k];
 }



 cout<<choose_allowed(DP, allowed, rvalue, n, d, k);

 cout<<"DP is : \n";
 for (int i=0; i<d; i++)
 {
   for (int j = 0; j < k; j++)
   {
     cout<<DP[i][j] <<" ";
   }
   cout<<endl;
 }



}