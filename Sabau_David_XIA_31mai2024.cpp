#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
///in fisierul bac.txt se afla un sir de numere intregi. Sa se identifice in sir numerele naturale
///palindrom si sa se insereze ca vecin ai acestora cel mai apropiat palindrom mai mic si mai mare
///numar prim. In Cazul in care 2 numere palindrom sunt vecine se insereaza intre acestea
using namespace std;
bool palindrom(int n)
{
    string s = to_string(n);
    int left = 0;
    int right = s.size() - 1;
    while(left <= right)
    {
        if(s[left] != s[right]) return false;
        left++;right--;
    }
    return true;
}
bool prim(int n)
{
    for(int d = 2;d <= sqrt(n);d++)
        if(n % d == 0) return false;
    return true;
}
int main()
{   ifstream f("bac.txt");
    vector<int> nums;
    int x;
    while(f>>x)
    {   cout<<x<<' ';
        if(palindrom(x) == false) nums.push_back(x);
        else {
            int a = x - 1;
            int b = x + 1;
            while(prim(a) == false) a--;
            while(prim(b) == false) b++;
            nums.push_back(a);
            nums.push_back(x);
            nums.push_back(b);
        }
    }
    cout<<endl;
    for(int i : nums) cout<<i<<' ';
    return 0;













}
