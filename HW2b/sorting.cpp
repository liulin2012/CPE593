#include <iostream>
#include <cstring>
#include <vector>
#include <fstream> 
#include <cstdlib>
using namespace std;

const int k=5;

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

int partition(vector<int>& numArray,int left,int right){
	int i=rand()%(right-left+1)+left;
	int pivot=numArray[i];
	swap(numArray[right],numArray[i]);
	int iniRight=right;	
	while(left!=right){
		while(left!=right&&numArray[left]<pivot){
			left++;	
		}

		while(left!=right&&numArray[right]>=pivot){
			right--;	
		}
		if(left!=right){
			swap(numArray[left],numArray[right]);
			left++;
		}
	}
	swap(numArray[iniRight],numArray[left]);
	return left;
}

void quickSort(vector<int>& numArray,int left,int right){
	if((right-left)>=k)
	{
		int q=partition(numArray,left,right);
		quickSort(numArray,left,q-1);
		quickSort(numArray,q+1,right);
	}
	else if(left<right){
		insertionSort(numArray,left,right);
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
	quickSort(numbers,0,numbers.size()-1);	
	vector<int>::iterator it=numbers.begin();
	for(;it!=numbers.end();it++)
	{
		cout<<*it<<",";
	}
	cout<<endl;
}

