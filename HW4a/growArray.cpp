#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  
  string name = "hw4ainp";
  freopen((name + ".dat").c_str(), "r", stdin);
  int n, m, p;
  cin >> n;
  cin >> m;
  cin >> p;
  cout << n << m << p << endl; 
  return 0;
}