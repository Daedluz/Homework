#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

long long int error_function (int allowed, int* rvalue, int* n, int start, int end)
{
 long long int err = 0;
 for (int i=start-1; i<end; i++)
 {
   err = err + roundl(pow((rvalue[i]-allowed), 2))*n[i];
 }
 return err;
}

long long int deltaErr (long long int** deltaE,  int* rvalue, int start, int end, int* n)
{
  if (deltaE[start][end] != -1)
  {
    return deltaE[start][end];
  }

  else
  {
    long long int min, err;
    min = error_function (rvalue[start], rvalue, n, start+1, end+1);
    for (int w=rvalue[start]+1; w<=rvalue[end]; w++)
    {
      err = error_function (w, rvalue, n, start+1, end+1);
      if (err < min)
      {
        min = err;
      }
      else
      {
        break;
      }
    }
    deltaE[start][end] = min;
    deltaE[end][start] = min;
    return deltaE[start][end];
  }

}


long long int choose_allowed (long long int** DP, long long int** deltaE, int* allowed, int* rvalue, int* n, int d, int k)
// return the total error of chosen
// C(i, j) = k s.t. C(k, j-1) + F(k+1, i) is smallest
// build the dynamic programming table DP while calling recursively

{
 long long int err , minerr, min, total, temp;
 long double minj;
 //Base Case

 if (k == 1)
 {
   DP[0][0] = 0;
   for (int i=2; i<=d; i++)
   {

     minj = 0;
     total = 0;
     //cout<<"error_function (0, rvalue, n, 1, "<<i<<" , k) = "<<err<<endl;
     DP[i-1][k-1] = deltaErr(deltaE, rvalue, 0, i-1, n);
   }

   return DP[d-1][k-1] ;
 }

 //recursive call
 //for every i,
 //choose the m  s.t. DP[m][j-1]  + F(m+1, i) is smallest
 choose_allowed (DP, deltaE, allowed, rvalue, n, d, k-1);


 for (int i=1; i<d; i++)
 {
   for (int j=0; j<i; j++)
   {
     minerr = DP[j][k-2] + deltaErr(deltaE, rvalue, j+1, i, n);

     if (j == 0)
     {
       min = minerr;
       //cout<<i<<" j == 0 , min = "<<min<<endl;
     }
     else if (minerr < min)
     {
       min = minerr;
       //cout<<i<<" "<<min<<endl;
     }
   }
   //cout<<"min = "<<min<<endl;
   DP [i][k-1] = min;
 }



 return DP[d-1][k-1] ;

}


long long int Compute (long long int** DP, long long int** deltaE, int* allowed, int* rvalue, int* n, int d, int k)
{
  long long int minerr , min;
  if (DP[d-1][k-1] != -1)
  {
    return DP[d-1][k-1];
  }

  if (k == 1)
  {
    DP[d-1][k-1] = deltaErr(deltaE,  rvalue, 1, d, n);
    return DP[d-1][k-1];
  }
  else
  {
    for (int j=k-2 ; j<d; j++)
    {
      minerr = Compute (DP, deltaE, allowed, rvalue, n, j+1, k-1) + deltaErr(deltaE, rvalue, j+2, d, n);

      if (j == 0)
      {
        min = minerr;
      }
      else if (minerr < min)
      {
        min = minerr;
      }
    }
    DP [d-1][k-1] = min;
    return DP[d-1][k-1];
  }


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

 long long int** DP = new long long int* [d];
 for (int i=0; i<d; i++)
 {
   DP[i] = new long long int [k];
 }

 long long int** deltaE = new long long int* [d];
 //start i ends j
 for (int i=0; i<d; i++)
 {
   deltaE[i] = new long long int [d];
 }

 for (int i=0; i<d; i++)
 {
   for (int j=0; j<d; j++)
   {
     deltaE[i][j] = -1;
   }
 }

 for (int i=0; i<d; i++)
 {
   for (int j=0; j<k; j++)
   {
     DP[i][j] = -1;
   }
 }

 long long int min, err;

/* cout<<"deltaE is : \n";
 for (int i=0; i<d; i++)
 {
   for (int j = 0; j < d; j++)
   {
     cout<<deltaE[i][j] <<" ";
   }
   cout<<endl;
 }*/

 cout<<choose_allowed(DP, deltaE, allowed, rvalue, n, d, k);

 /*cout<<"\nDP is : \n";
 for (int i=0; i<d; i++)
 {
   for (int j = 0; j < k; j++)
   {
     cout<<DP[i][j] <<" ";
   }
   cout<<endl;
 }*/



}
