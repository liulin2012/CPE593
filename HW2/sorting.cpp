#include <iostream>
#include <cstring>
#include <vector>
#include <fstream> 
#include <cstdlib>
using namespace std;

const int k=2;
void fastSort(vector<int>& numArray,int left,int right){
	
}

void insertionSort(vector<int>& numArray,int left,int right){
	for(int i=left+1;i!=right+1;i++)	
	{
		int key=numArray[i];
		int j=i-1;
		while(key<numArray[j]&&j!=left-1)
		{
			numArray[j+1]=numArray[j];
			j--;
		}
		numArray[j+1]=key;
	}
}

int main(int argc, char *argv[]) {
	fstream sortFile("HW2.txt",ios::in);		 
	char num[256];
	char nums[256];
	sortFile.getline(num,256,'\n');
	int number=atoi(num);
	vector<int> numbers;
	sortFile.getline(nums,256,'\n');
	char *token=strtok(nums," ");
	while(token!=NULL){
		numbers.push_back(atoi(token));
		token=strtok(NULL," ");
	}
	insertionSort(numbers,0,numbers.size()-1);	
	vector<int>::iterator it=numbers.begin();
	for(;it!=numbers.end();it++)
	{
		cout<<*it<<",";
	}
}
