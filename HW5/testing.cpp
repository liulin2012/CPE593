#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

class BadSize {
private:
	int line;
public:
	BadSize(int line): line(line){}
};

class matrix{
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
  ~matrix (){
	  delete [] m;
  }
  matrix (const matrix& orig):rows(orig.rows),cols(orig.cols){
	  m=new double[rows*cols];
	  for (int i=0;i<orig.rows*orig.cols;i++){
		  m[i]=orig.m[i];
	  }
  }
  friend matrix  operator +(const matrix&  a,const matrix& b){
	  if (a.rows != b.rows || a.cols != b.cols)
		  throw BadSize(__LINE__);
	  matrix c(a.rows, a.cols);
	  for (int i=0;i<a.rows;i++)
		  for (int j=0;j<a.cols;j++){
    	  c.m[i*a.cols+j] = a.m[i*a.cols+j] + b.m[i*a.cols+j];
		  }
	  return c;
  }

  friend matrix  operator *(const matrix&  a,const matrix& b){
	  if (a.cols != b.rows   )
		  throw BadSize(__LINE__);
	  matrix c(a.rows,b.cols);
	  for (int i=0;i<a.rows;i++)
		  for (int j=0;j<b.cols;j++){
			  int m =0;
			  for(int k=0; k<a.cols;k++){
				  m += a.m[i*a.cols+k]*b.m[k*b.cols+j];
			  }
			  c.m[i*c.cols+j] = m;
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
      for (int j=0; j<m.cols;j++){
    	  s << m.m[c++]<<" ";
      }
      s<<endl;
    }
    return s;
  }
  friend istream& operator >>(istream& s, matrix& m) {
    int c = 0;
    for (int i=0; i<m.rows;i++) {
    	for (int j=0; j<m.cols;j++) {
    		s >> m.m[c++];
 //   		cout<<m.m[c-1]<<" ";
      }
    }
//    cout<<endl;
    return s;
  }

  friend matrix operator *=(matrix a,matrix b){
	  matrix c(a.rows, a.cols+1);
	  for(int i=0; i<c.rows; i++)
		  for(int j=0; j<c.cols-1;j++)
			  c.m[i*c.cols+j] = a.m[i*a.cols+j];
	  for(int i=0; i<b.rows; i++)
		  c.m[i*c.cols+c.cols-1] = b.m[i];

	  for(int i=0;i<c.rows;i++){
		  double div = c.m[i*c.cols+i];
//		  cout<< "div = "<<div<<endl;
		  for(int j=0; j<c.cols; j++)	{
			  c.m[i*c.cols+j] /= div;
		  }

		  for(int n=i; n<c.rows-1; n++){
			  double mul = c.m[(n+1)*c.cols+i]/c.m[i*c.cols+i]*-1;
//			  cout<<"mul = "<<mul<<endl;
			  for(int m=0; m<c.cols;m++){
				  c.m[(n+1)*c.cols+m] +=  mul*c.m[i*c.cols+m];
			  }
		  }
	  }
	//  cout<<"z= "<<"\n"<<c<<endl;
	  for(int i=c.rows-1; i>0; i--){
		  for(int j=1; j<=i;j++){
			  double mul = c.m[(i-j)*c.cols+i]/c.m[i*c.cols+i]*-1;
	//		  cout<<"mul2 = "<<mul<<endl;
			  for(int m=i; m<c.cols;m++){
				  c.m[(i-j)*c.cols+m] +=  mul*c.m[i*c.cols+m];
			  }
		  }
	  }

	  matrix ans(a.rows,1);
	  for(int i=a.rows-1; i>=0; i--){
		  ans.m[i] = c.m[i*c.cols+c.cols-1];
	  }

	  return ans;
  }
};

int main ()
{
  ifstream f("hw5a");
  if(f.is_open()){
	  string cas;
	  f>>cas;
	  int numofcase;
	  f>>numofcase;
	  int rows,cols;
	  f>>rows>>cols;
	  matrix a(rows,cols);
	  f >> a;
	  cout<<"a= "<<"\n"<<a<<endl;
	  matrix b(rows,cols);
	  f >> b;
	  cout<<"b= "<<"\n"<<b<<endl;
	  try {
		  matrix c=a+b;
		  cout<<"c= "<<"\n"<<c<<endl;
	  } catch(const BadSize& e) {
		  cerr << "oops, matrix sizes don't match\n";
		  exit(2);
	  }
	  matrix d=a*b;
	  cout<<"d= "<<"\n"<<d<<endl;

	  matrix n(rows,1);
	  f>>n;
	  cout<<"n= "<<"\n"<<n<<endl;
	  matrix z= a*=n;
	  cout<<"z= "<<"\n"<<z<<endl;
  //matrix e=a.tran();
  }else{
  		cout<<"Error,can't open...\n";
  		exit(2);
  	}
}
