#include <iostream>
using namespace std;
int n,x=2,y;

int prim(int &k){
if(k<2) return 0;
if(k==2) return 2;
for(int i=k-1;i>=2;i--)
    if(i%2!=0 && k%i!=0)
    return i;
return 2;
}
int verifprim(int k){
if(k<2) return 0;
if(k==2) return 1;
if(k%2==0) return 0;
for(int i=3;i<=k/2;i++)
    if(k%i==0)
    return 0;
return 1;
}

void sub(int n,int x,int y){
y=prim(n);

while(x<=y){
if(verifprim(x)==1 && verifprim(y)==1 && (n-x)%2!=0){
if(x+y==n)
   cout<<x<<' '<<y<<endl;
}

if(x==2)
x++;
else x+=2;
y-=2;
}

}

int main()
{ cin>>n;
sub(n,x,y);
    return 0;
}
