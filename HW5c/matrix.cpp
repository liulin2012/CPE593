#include <fstream>
#include <random>
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

  friend matrix  operator -(const matrix&  a,const matrix& b){
    if (a.rows != b.rows || a.cols != b.cols)
      throw BadSize(__LINE__);
    matrix c(a.rows, a.cols);
    for (int i=0;i<a.rows;i++)
      for (int j=0;j<a.cols;j++) {
	      c.m[i*a.cols+j] = a.m[i*a.cols+j] - b.m[i*a.cols+j];
	    }
    return c;
  }

  friend matrix  operator *(const matrix&  a,const matrix& b){
    
    if (a.cols != b.rows)
      throw BadSize(__LINE__);
    //if (1) {
    if (a.rows <= 16) {
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
    else {
      int line = a.rows / 2;
      matrix a11(line, line);
      matrix a12(line, line);
      matrix a21(line, line);
      matrix a22(line, line);
      matrix b11(line, line);
      matrix b12(line, line);
      matrix b21(line, line);
      matrix b22(line, line);

      int x = 0;
      for (int i = 0; i < line; i++) 
        for (int j = 0; j < line; j++) {
          a11.m[x] = a.m[i*a.cols + j];
          b11.m[x++] = b.m[i*b.cols + j];
        }
      x = 0;
      for (int i = 0; i < line; i++) 
        for (int j = line; j < line*2; j++) {
          a12.m[x] = a.m[i*a.cols + j];
          b12.m[x++] = b.m[i*b.cols + j];
        }
      x = 0;
      for (int i = line; i < line*2; i++) 
        for (int j = 0; j < line; j++) {
          a21.m[x] = a.m[i*a.cols + j];
          b21.m[x++] = b.m[i*b.cols + j];
        }
      x = 0;
      for (int i = line; i < line*2; i++) 
        for (int j = line; j < line*2; j++) {
          a22.m[x] = a.m[i*a.cols + j];
          b22.m[x++] = b.m[i*b.cols + j];
        }
      matrix m1 = (a11 + a22) * (b11 + b22);
      matrix m2 = (a21 + a22) * b11;
      matrix m3 = a11 * (b12 - b22);
      matrix m4 = a22 * (b21 - b11);
      matrix m5 = (a11 + a12) * b22;
      matrix m6 = (a21 - a11) * (b11 + b12);
      matrix m7 = (a12 - a22) * (b21 + b22);

      matrix c11 = m1 + m4 - m5 + m7;
      matrix c12 = m3 + m5;
      matrix c21 = m2 + m4;
      matrix c22 = m1 - m2 + m3 + m6;

      matrix c(a.rows, b.cols);

      for (int i = 0; i < line; i++) 
        for (int j = 0; j < line; j++) {
          c.m[i*c.cols + j] = c11.m[i*line + j];
        }
      for (int i = 0; i < line; i++) 
        for (int j = 0; j < line; j++) {
          c.m[i*c.cols + line + j] = c12.m[i*line + j];
        }
      for (int i = 0; i < line; i++) 
        for (int j = 0; j < line; j++) {
          c.m[(line + i)*c.cols + j] = c21.m[i*line + j];
        }
      for (int i = 0; i < line; i++) 
        for (int j = 0; j < line; j++) {
          c.m[(line + i)*c.cols + line + j] = c22.m[i*line + j];
        }

      return c;
    }
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
	      s << fixed << m.m[c++]<<" ";
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

void generateNum(int x){
    random_device rd;
    mt19937 mt(rd());
    ofstream myfile;
    myfile.open("test.txt");
    myfile << "case 1:" << endl;
    myfile << x << " " << x << endl;
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < x; j++)
          myfile << mt()%100 << " ";
      myfile << endl;
    }
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < x; j++)
          myfile << mt()%100 << " ";
      myfile << endl;
    }
    myfile.close();
}


int main ()
{
  //generateNum(2048);
  //ifstream f("test.txt");
  ifstream f("HW5c.txt");
  string s;f >> s;
  string caseS; f >> caseS;
  int caseN = stoi(caseS);
  for (int i = 0; i < caseN; i++) {
    int row, col;
    f >> row >> col;
    matrix a(row, col);
    f >> a;
	  matrix b(row,col);
	  f >> b;
	  matrix d = a*b;
    cout << d;
  } 
}



