#include <iostream>

using namespace std;

int main()
{   int a[101][101];
    int i,j,n;
    cin>>n;
    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
    {
        a[i][j] = i+j;
        a[i][2*n-j-1] = a[i][j];
        a[2*n-i-1][2*n-j-1] = a[i][j];
        a[2*n-i-1][j] = a[i][j];
    }
    for(int i = 0;i < 2*n;i++)
        {for(int j = 0;j < 2*n;j++)
        cout<<a[i][j]<<' ';
          cout<<endl;}
            return 0;
}
