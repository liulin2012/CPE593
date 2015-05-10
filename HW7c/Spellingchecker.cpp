#include <cstdint> // C++11 Required
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <map>
#include <cctype>
using namespace std;

class HashMap {
private:
  uint32_t size;
  uint32_t used;
  struct Node {
    string key;
    int    val;
    Node* next;
    //    Node() : key() {}
  };
  Node* table;
  void grow() {
    HashMap* tmp = new HashMap(size * 2); 
    HashMap::Iterator i(*this);
    while (i.hasNext()) {
      tmp->add(i.getKey(), i.getValue());
    }
    size *= 2;
    table = tmp->table;
    cout << "double size, the new size is " << size << endl;
  }
  size_t hash(const string& s) {
    uint32_t sum = 0;
    for (int i = 0; i < s.size(); i++)
      sum = sum + (sum << 13) + (sum >> 17) + s[i];
    return sum & (size-1);
  }
public:
  HashMap(size_t initialSize)
    : size(initialSize), used(0) {
    table = new Node[size];    
  }
  HashMap(const HashMap& orig);
  HashMap& operator =(const HashMap& orig);
  ~HashMap() {
    delete [] table;
  }

  // if key is already there replace the value
  void add(const string& key, int val) {
    uint32_t i = hash(key);
    Node* tmp = &table[i];
    while (tmp->key.length() != 0) {
      if (tmp->key == key) {
	     tmp->val = val;
	     return;
      }
      tmp = tmp->next;
    }
    tmp->key = key;
    tmp->val = val;
    tmp->next = new Node();

    used++;
    if (used >  size) grow();
  }
  int* get(const string& key) {
    uint32_t i = hash(key);
    Node* tmp = &table[i];
    while (tmp->key.length() != 0) {
      if (tmp->key == key) {
	      return &(tmp->val);
      }
      tmp = tmp->next;
    }
    return nullptr;
  }

  class Iterator {
  private:
    Node* current; // if the hashmap grows, this is GARBAGE
    Node* index;
    size_t used;
  public:
    Iterator(HashMap& m) {
      index = &m.table[-1];
      current = nullptr;
      used = m.used;
    }

    bool hasNext() {
      if (used == 0) return false;
      else used--;
      if (current == nullptr || current->next->key.length() == 0) {
        index++;
        while (index->key.length() == 0) index++;
        current = index;
      }
      else {
        current = current->next; 
      }

      return true;
    }

    string getKey() {
      return current->key;
    }
    int getValue() {
      return current->val;
    }
  };
  friend Iterator;

};

int main() {
  ifstream f("wordsEn.txt");
  string word;
  unordered_set<string> dictionary;
  while (f >> word) dictionary.insert(word);

  ifstream m("CompletWorksOfShakespeare.txt");
  HashMap mostWord(10000);
  string bookWord;
  while (m >> word) {
    word.erase(remove_if(word.begin(), 
                         word.end(),
                         [](char x){return !isalnum(x);}),
               word.end());
    if (word.length() == 0) continue;
    if (mostWord.get(word) != nullptr) {
      int* val = mostWord.get(word);
      (*val)++;
    }
    else mostWord.add(word, 1);
  }
  cout << endl;

  HashMap::Iterator i(mostWord);
  multimap<int, string> sortMap;
  
  while (i.hasNext()) {
    sortMap.insert({i.getValue(), i.getKey()});
  }

  cout << "Top 100 words" <<endl<<endl;
  auto iter = sortMap.rbegin();
  int n = 100;
  while (n--) {
    cout << iter->second << " : " << iter->first << endl;
    iter++;
  }
  cout << endl;

  HashMap::Iterator x(mostWord);
  int right = 0;
  int wrong = 0;
  while (x.hasNext()) {
    if (dictionary.find(x.getKey()) != dictionary.end()) right++;
    else wrong++;
  }

  cout << "Right spelling : " << right << endl;
  cout << "wrong spelling : " << wrong << endl;
  
  cout << endl;

  cout << "Top 10 wrong words" <<endl<<endl;
  auto iter2 = sortMap.rbegin();
  n = 10;
  while (n) {
    if (dictionary.find(iter2->second) == dictionary.end()) { 
      cout << iter2->second << " : " << iter2->first << endl;
      n--;
    }
    iter2++;
  }

  //HashMap m(2);
  //m.add("IBM", 106);
  //m.add("2IBM", 106);
  //m.add("I3BM", 106);
  //m.add("4IBM", 106);
  //m.add("5IBM", 106);
  //m.add("6IBM", 106);
  //m.add("BABA", 88);
  //int* val = m.get("IBM");
  //(*val)++;
  //int* x = m.get("IBM");
  //if (x != nullptr) {
  //  cout << *x <<endl;
  //}

  //HashMap::Iterator i(m);
  //while (i.hasNext()) {
  //  cout << i.getKey() << "==>" << i.getValue() << endl;
  //}
}  
  
