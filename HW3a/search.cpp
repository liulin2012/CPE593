#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc, const char * argv[]) {
	string line;
	getline(cin, line);
	int caseNum = (int)(line[7 ]- '0');
	for (int i=0; i<caseNum; i++){
		getline(cin, line);
		int number = stoi(line);

		vector<int> allNum;
		string buf;
		getline(cin, line);
		stringstream ss(line);
		while(ss >> buf) 
			allNum.push_back(stoi(buf));

		getline(cin, line);
		int numFind=stoi(line);

		int left = 0;
		int right = number - 1;
		bool ifFind = true;
		int round = 0;
		while (ifFind) {
			round++;
			int mid = left + (right - left) / 2;
			if (numFind == allNum[mid]) {
				ifFind = false;
				cout << numFind << " " << round << endl;
			} else if (numFind < allNum[mid]) {
				right = mid - 1;
			} else if (numFind > allNum[mid]) {
				left = mid + 1;
			}
			if (left == right + 1){
				cout << "NOT FOUND " << round << endl;
				ifFind = false;
			}
		}
	}
	return 0;
}
