 #include <iostream>
#include <cmath>
#include <valarray>
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
  unsigned long long int err , minerr, minj, min;
  //Base Case
  if (k == 1)
  {
    allowed[k-1] = 0;
    DP[0][0] = 0;
    minerr = error_function (0, rvalue, n, 1, d , k);
    for (int i=2; i<=d; i++)
    {
      minerr = error_function (0, rvalue, n, 1, i , k);
      //cout<<"error_function (0, rvalue, n, 1, "<<i<<" , k) = "<<err<<endl;
      for (int j=rvalue[0]; j<rvalue[d-1]; j++)
      {
        //cout<<i<<" "<<j<<"\n";
        allowed[k-1] = j;
        err = error_function(j, rvalue, n, 1, i, k);
        //cout<<"error_function ("<<j<<", rvalue, n, 1, "<<i<<" , k) = "<<err<<endl;
        if (err < minerr)
        {
          minerr = err;
          minj = j;
        }
        /*else
          break;*/
      }
      DP[i-1][k-1] = minerr;
      //cout<<"DP ["<<i<<"][0] = "<<DP[d-1][k-1]<<endl;
      allowed[k-1] = minj;
    }

    return DP[d-1][k-1] ;
  }

  //recursive call
  //for every i,
  //choose the m  s.t. DP[m][j-1]  + F(m+1, i) is smallest
  choose_allowed (DP, allowed, rvalue, n, d, k-1);

  for (int i=1; i<=d; i++)
  {
    for (int m=1; m<i; m++)
    {
      for (int u=0; u<m; u++)
      {
        minerr = DP[m-1-u][k-2]  + error_function(rvalue[i-m], rvalue, n, m+1-u, d, k);
        for (int w = rvalue[m-1]; w <= rvalue[i-1]; w++)
        {
          err = DP[m-1-u][k-2]  + error_function(w, rvalue, n, m+1-u, d, k);
          /*if (i == 4)
            cout<<w<<" "<<err<<"\n";*/
          if (err < minerr)
          {
            minerr = err;
            minj = w;
          }
        }
        /*else
          break;*/
      }
      //cout<<i<<" "<<m<<" "<<minerr<<endl;
    }
    //cout<<i<<" "<<minj<<" "<<min<<endl;
    DP[i-1][k-1] = minerr;
    //cout<<"i-1 = "<<i-1<<" k-1 = "<<k-1<<" DP = "<<DP[i-1][k-1]<<endl;

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


  cout<<choose_allowed(DP, allowed, rvalue, n, d, k)<<endl;


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
