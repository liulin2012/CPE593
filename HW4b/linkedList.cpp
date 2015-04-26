#include <iostream>

using namespace std;

class linkedList2 {
	class  Node{
		public:
		int v;
		Node* next;
		Node* prev;
		Node(int v,Node* n, Node* p):v(v),next(n),prev(p){
		}
	};
	
	Node* head;
  Node* tail;
public:
	linkedList2(){
		head=nullptr;
	}
	~linkedList2(){
		Node* s,*n;
		for(s=head;s!=NULL;s=n){
			n=s->next;
			delete s;
		}
	}
	void addFirst(int v){
		head=new Node(v,head,nullptr);
		if (head->next == nullptr) tail = head;
    else head->next->prev = head;
	}
	void insert(int target,int v){
		for(Node* s=head;s!=NULL;s=s->next){
			if (s->v==target){
				Node* t=new Node(v,s,s->prev);
				if(s->prev!=NULL){	
				s->prev->next=t;
				}
				else
					head=t;
				s->prev=t;
				break;
			}
		}
	}
	void addLast(int v){
    if (head == nullptr) addFirst(v);
    else {
      tail->next = new Node(v, nullptr, tail);
      tail = tail->next;
    }
	}

  void deleteFirst() {
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
  }
  void deleteLast() {
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
  }
  friend ostream& operator <<(ostream& s, const linkedList2& a) {
    s << '[';
    Node* tmp = a.head;
    while (tmp != nullptr) {
      s << tmp->v << ' ';
      tmp = tmp->next;
    }
    s << ']';
    return s;
  }
};

int main(int argc, char *argv[])
{
  
  string name = "hw5ainp";
  freopen((name + ".dat").c_str(), "r", stdin);
  int n, m, p;
  cin >> n;
  cin >> m;
  cin >> p;
  linkedList2 *test = new linkedList2();
  int x = 1;
  while (n--) test->addLast(x++);
  while (m--) test->deleteFirst();
  while (p--) test->deleteLast();
  cout << *test << endl;
  return 0;
}

