#include <iostream>
#include <cstdint>
using namespace std;

template<typename T>
class GrowArray {
private:
  T* p;
  uint32_t size_;
  uint32_t used_; // This is the number of cells used so far
public:
  GrowArray() {
    size_ = 0;
    p = nullptr;    // OLD Way: NULL, less old way 0
  }

  GrowArray(uint32_t initialSize) {
    size_ = initialSize;
    used_ = 0;
    p = new T[initialSize];
  }
  ~GrowArray() {
    delete [] p;
  }
  // copy constructor
  GrowArray(const GrowArray& orig) {
  }

  // operator =
  GrowArray& operator =(const GrowArray& orig) {
    return *this;
  }

  // move constructor
  GrowArray(const GrowArray&& orig) {
  }
  // O( 1  )
  void addEnd(const T& v) {
    if (  )
      grow();
    T* temp = p;
    size_++;
    p = new T[size_];
    for (int i = 0; i < size_-1; i++)
      p[i] = temp[i];
    p[size_-1] = v;
    delete [] temp;
  }
  // O(size)
  void addStart(const T& v) {
    T* temp = p;
    size_++;
    p = new T[size_];
    p[0] = v;
    for (int i = 1; i < size_; i++)
      p[i] = temp[i-1];
    delete [] temp;
  }
  //O(size)
  void deleteEnd() {
    T* temp = p;
    p = new T[--size_];
    for (int i = 0; i < size_; i++)
      p[i] = temp[i];
    delete [] temp;
  }

  //O(size)
  void deleteStart() {
    T* temp = p;
    p = new T[--size_];
    for (int i = 0; i < size_; i++)
      p[i] = temp[i+1];
    delete [] temp;
  }

  // readonly method size returns the size of the list
  uint32_t size() const {
    return size_;
  }

  T operator [](int i) const {
    return p[i];
  }

  T& operator [](int i) {
    return p[i];
  }

  friend ostream& operator <<(ostream& s, const GrowArray& a) {
    s << '[';
    for (int i = 0; i < a.size(); i++)
      s << a.p[i] << ' ';
    s << ']';
    return s;
  }
};

int main() {
  GrowArray<double> a; // start with 10 element
  cout << a << '\n';
  
  // Should be O(n)
  const int n = 10000000;
  for (int i = 0; i < n; i++)
    a.addEnd(i);

  GrowArray<double> b;
  b.addEnd(5.2);
  b.addStart(3.1);
  b.addEnd(6.2);
  b.deleteStart();
  cout << b << '\n';
}

