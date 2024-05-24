#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a[101][101];
    int m,n;
    int x;
    bool k = false;
    cin>>n>>m>>x;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
        cin>>a[i][j];

    for(int i = 1;i <= n;i++)
        {if(a[i][1] == x) k = true;
        if(a[i][m] == x) k = true;}
    for(int i = 1;i <= m;i++)
    {
        if(a[1][i] == x) k = true;
        if(a[n][i] == x) k = true;
    }
    if(k) cout<<"DA";
    else cout<<"NU";
    return 0;
}
