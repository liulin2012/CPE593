#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


double f1(double x) { return x*x; }
double f2(double x) { return x*x*x;}
double f3(double x) { return x*std::exp(-x);}
typedef double (*FuncOneVar)(double x);

void Gauss(FuncOneVar f, double a, double b, double eps){
  double slices = 0.5;
  double result = 0;
  double tmp = 0;
  double rang = b - a;
  do {
    slices *= 2;
    tmp = result;
    result = 0;
    int n = slices;
    double oneSlice = rang/n;
    double one = a;
    double two = a + oneSlice;
    double h = oneSlice/2;
    while (n--) {
       double mid = (one + two)/2;
       double m = 1/3.0;
       double x1 = mid + std::sqrt(m)*h;
       double x2 = mid - std::sqrt(m)*h;
       result += (f(x1) + f(x2)) * h;
       one = two;
       two += oneSlice;
    }
    //cout << result << endl;
  } while (abs(result - tmp) > eps);
  cout << result << " " << slices << " ";
}

void Gauss3(FuncOneVar f, double a, double b, double eps){
  double slices = 0.5;
  double result = 0;
  double tmp = 0;
  double rang = b - a;
  do {
    slices *= 2;
    tmp = result;
    result = 0;
    int n = slices;
    double oneSlice = rang/n;
    double one = a;
    double two = a + oneSlice;
    double h = oneSlice/2;
    while (n--) {
       double mid = (one + two)/2;
       double x1 = mid + h*sqrt(3/5.0);
       double x2 = mid - h*sqrt(3/5.0);
       result += (f(x1)*5/9 + f(x2)*5/9 + f(mid)*8/9) * h;
       one = two;
       two += oneSlice;
    }
    //cout << result << endl;
  } while (abs(result - tmp) > eps);
  cout << result << " " << slices << endl;
}

int main(int argc, char *argv[])
{
  string name = "test";
  string path = "";

  freopen((path + name + ".in").c_str(), "r", stdin);
  freopen((path + name + ".out").c_str(), "w", stdout);

  string a;
  cin >> a;
  int test_cases;
  cin >> test_cases;
  for (int test_case = 1; test_case <= test_cases; test_case++) {
    string functionT;
    cin >> functionT;

    double a, b, eps;
    cin >> a;
    cin >> b;
    cin >> eps;
    if (functionT == "fa") {
      Gauss(f1, a, b, eps);
      Gauss3(f1, a, b, eps);
    }
    else if (functionT == "fb") {
      Gauss(f2, a, b, eps);
      Gauss3(f2, a, b, eps);
    }else if (functionT == "fc") {
      Gauss(f3, a, b, eps);
      Gauss3(f3, a, b, eps);
    }
    else  cout << "wrong input" << endl;
    cout.flush();
  }
  fclose(stdout);
  fclose(stdin);
  return 0;
}
