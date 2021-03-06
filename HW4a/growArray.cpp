#include <iostream>
using namespace std;

template<typename T>
class GrowArray {
private:
  T* p;
  uint32_t size_;
  uint32_t used_; // This is the number of cells used so far
public:
  GrowArray() {
    size_ = 8;
    used_ = 0;
    p = new T[size_];    // OLD Way: NULL, less old way 0
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

  void grow() {
    T* temp = p;
    p = new T[size_*2];
    for (int i = 0; i < size_; i++) p[i] = temp[i];
    size_ *= 2;
    delete [] temp;
  }
  // O( 1  )
  void addEnd(const T& v) {
    if (size_ == used_)
      grow();
    //T* temp = p;
    p[used_] = v;
    used_++;
    //p = new T[size_];
    //for (int i = 0; i < size_-1; i++)
    //  p[i] = temp[i];
    //p[size_-1] = v;
    //delete [] temp;
  }
  // O(size)
  void addStart(const T& v) {
    if (size_ == used_) grow();
    for (int i = used_; i > 0; i--)
      p[i] = p[i-1];
    p[0] = v;
    used_++;
  }
  //O(size)
  void deleteEnd() {
    used_--;
  }

  //O(size)
  void deleteStart() {
    for (int i = 0; i < size_; i++)
      p[i] = p[i+1];
    used_--;
  }

  // readonly method size returns the size of the list
  uint32_t size() const {
    return size_;
  }

  uint32_t used() const {
    return used_;
  }

  T operator [](int i) const {
    return p[i];
  }

  T& operator [](int i) {
    return p[i];
  }

  friend ostream& operator <<(ostream& s, const GrowArray& a) {
    s << '[';
    for (int i = 0; i < a.used(); i++)
      s << a.p[i] << ' ';
    s << ']';
    return s;
  }
};

int main(int argc, char *argv[])
{
  
  string name = "hw4ainp";
  freopen((name + ".dat").c_str(), "r", stdin);
  int n, m, p;
  cin >> n;
  cin >> m;
  cin >> p;
  GrowArray<int> *test = new GrowArray<int>();
  int x = 1;
  while (n--) test->addEnd(x++);
  while (m--) test->deleteEnd();
  while (p--) test->deleteStart();
  cout << *test << endl;
  return 0;
}