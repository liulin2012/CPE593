#include <fstream>
#include <iostream>
using namespace std;

class BadSize {
private:
  int line;
public:
  BadSize(int line): line(line){}
};

class matrix
{
private:
  int rows;
  int cols;
  double* m;
public:  
  matrix(int r,int c):rows(r),cols(c) {
    m=new double [rows*cols];
    for (int i=0;i<rows*cols;i++)
      m[i]=0;
  }
  ~matrix ()
  {delete [] m;
  }
  matrix (const matrix& orig):rows(orig.rows),cols(orig.cols) {
    m=new double[rows*cols];
    for (int i=0;i<orig.rows*orig.cols;i++) {
    	m[i]=orig.m[i];
    }
  }
  friend matrix  operator +(const matrix&  a,const matrix& b){
    if (a.rows != b.rows || a.cols != b.cols)
      throw BadSize(__LINE__);
    matrix c(a.rows, a.cols);
    for (int i=0;i<a.rows;i++)
      for (int j=0;j<a.cols;j++) {
	      c.m[i*a.cols+j] = a.m[i*a.cols+j] + b.m[i*a.cols+j];
	    }
    return c;
  }

  friend matrix  operator *(const matrix&  a,const matrix& b){
    if (a.cols != b.rows)
      throw BadSize(__LINE__);
    matrix c(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
      for (int j = 0; j < b.cols; j++) {
        double m = 0;
        for (int k = 0; k < a.cols; k++) 
          m += a.m[i*a.cols + k] * b.m[k*b.cols + j];
        c.m[i*c.cols + j] = m;
      }
    }
    return c;
  }


  friend matrix add(const matrix&  a,const matrix& b){
    matrix c(a.rows, a.cols);
    for (int i=0; i < a.rows*a.cols; i++) {
      c.m[i] = a.m[i] + b.m[i];
    }
    return c;
  }
  friend ostream& operator <<(ostream& s, const matrix& m) {
    int c = 0;
    for (int i=0; i<m.rows;i++) {
      for (int j=0; j<m.cols;j++)    
	      s << m.m[c++]<<" ";
      s<<endl;
    }
    return s;
  }
  friend istream& operator >>(istream& s, const matrix& m) {
    int c = 0;
    for (int i=0; i<m.rows;i++) {
      for (int j=0; j<m.cols;j++) {
	  s >> m.m[c++];
      }
    }
    return s;
  }
  friend matrix operator *=(matrix a, matrix b) {
	  matrix c(a.rows, a.cols+1);
	  for(int i = 0; i < c.rows; i++)
		  for(int j = 0; j < c.cols-1;j++)
			  c.m[i*c.cols + j] = a.m[i*a.cols + j];
	  for(int i = 0; i < b.rows; i++)
		  c.m[i*c.cols + c.cols-1] = b.m[i];

    for (int i = 0; i < c.rows ; i++) {
      double divPara = c.m[i*c.cols + i];
      for (int j = i; j < c.cols; j++)
        c.m[i*c.cols + j] /= divPara;
      for (int k = i + 1; k < c.rows; k++) {
        double para = (-1) * c.m[k*c.cols + i];
        for (int m = i; m < c.cols; m++)
				  c.m[k*c.cols + m] +=  para*c.m[i*c.cols+m];
      }
    }

    for (int i = c.rows - 1; i > 0; i--) {
      for (int j = i - 1; j >= 0; j--) {
        c.m[j*c.cols + c.cols -1] -= c.m[j*c.cols + i] * c.m[i*c.cols + c.cols -1]; 
      }
    }

    matrix result(1, a.rows);
    for (int i = 0; i < a.rows; i++) 
      result.m[i] = c.m[i*c.cols+c.cols-1];

    return result;
  }
};

int main ()
{
  ifstream f("HW5.txt");
  string s;f >> s;
  int caseN; f >> caseN;
  for (int i = 0; i < caseN; i++) {
    int row, col;
    f >> row >> col;
    matrix a(row, col);
    f >> a;
	  matrix b(row,col);
	  f >> b;
	  try {
		  matrix c = a + b;
		  cout << c ;
	  } catch(const BadSize& e) {
		  cerr << "oops, matrix sizes don't match\n";
		  exit(2);
	  }
	  matrix d = a*b;
    cout << d;
	  matrix n(row,1);
	  f >> n;
	  matrix z= a*=n;
	  cout << z;
  } 
}



