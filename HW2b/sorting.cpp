#include <iostream>
#include <chrono>
#include <string>
#include <cmath>
#include <cstring>
#include <vector>
#include <fstream> 
#include <cstdlib>
using namespace std;


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

void quickSort(vector<int>& numArray,int left,int right,int k){
    if((right-left)>=k)
    {
        int q=partition(numArray,left,right);
        quickSort(numArray,left,q-1,k);
        quickSort(numArray,q+1,right,k);
    }
    else if(left<right){
        insertionSort(numArray,left,right);
    }
}

void generateNum(int x){
    int count=pow(10,x);
    string filename=to_string(x);
    ofstream myfile;
    myfile.open(filename+".txt");
    for(int i=0;i<count-1;i++)
    {
        myfile<<rand()<<" ";
    }
    myfile<<rand();
    myfile.close();
}

void goldenMeanSearch(int begin,int end,vector<int> numb,int interval){
    int intval=end-begin+1;
    double phi=0.618;
    while(intval>interval)  
    {
        vector<int> numbers(numb);
        int k=begin+intval*phi;
        auto t_start = std::chrono::high_resolution_clock::now();
        quickSort(numbers,0,numbers.size()-1,k);
        auto t_end = std::chrono::high_resolution_clock::now();
        double useTime1=chrono::duration<double, std::milli>(t_end-t_start).count()/1000;
        cout<<"K is "<<k<<" used time:"<<useTime1<<" Sec"<<endl;

        vector<int> numbers2(numb);
        k=end-intval*phi;
        t_start = std::chrono::high_resolution_clock::now();
        quickSort(numbers2,0,numbers2.size()-1,k);
        t_end = std::chrono::high_resolution_clock::now();
        double useTime2=chrono::duration<double, std::milli>(t_end-t_start).count()/1000;
        cout<<"K is "<<k<<" used time:"<<useTime2<<" Sec"<<endl;
        cout<<endl;
        if(useTime1>useTime2){
            end=begin+intval*phi;
            intval=end-begin+1;
            if(intval<=interval)
            cout<<"The best k is "<<begin<<endl;
        }else{
            begin=end-intval*phi;
            intval=end-begin+1;
            if(intval<=interval)
            cout<<"The best k is "<<end<<endl;
        }
    }

}
int main(int argc, char *argv[]) {
    int powCount;
    cout<<"please input the number 6/7/8:"<<endl;
    cin>>powCount;
    int begin=20;
    int end=2000;
    int interval=10;
    generateNum(powCount);
    ifstream sortFile(to_string(powCount)+".txt");       
    vector<int> numbers;
    while(!sortFile.eof()){
        string oneNumber;
        getline(sortFile,oneNumber,' ');
        if(oneNumber!="\n")
        numbers.push_back(stoi(oneNumber));
    }
    cout<<numbers.size()<<endl;
    goldenMeanSearch(begin,end,numbers,interval);
}

