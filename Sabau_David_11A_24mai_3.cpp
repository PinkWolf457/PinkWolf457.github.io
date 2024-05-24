#include <bits/stdc++.h>

using namespace std;

int main()
{
    int v[101] = {0};
    ifstream f("bac.txt");
    int i;
    while(f>>i) v[i]++;
    int maxx = -1;
    int maxx2 = -1;
    int s = 0;int k = 0;
    for(int i = 1;i <= 99;i++)
    {
        if(v[i] != 0)
        {
            s += i;k++;
        }
        if(v[i + 1] == 0)
        {
            if(maxx < s)
            {maxx2 = k;
            maxx = s;}
            k = 0;s = 0;
        }
    }
    cout<<maxx<<endl<<maxx2;
    return 0;
}
