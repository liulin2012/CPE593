//
//  main.cpp
//  prime
//
//  Created by lin liu on 2/15/15.
//  Copyright (c) 2015 lin. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
using namespace std;

//static const int num_threads = 8;

void call_from_thread(int tid,long begin,long end,vector<bool> bv,long &num) {
    cout << "Launched by thread " << tid <<" begin:"<<begin<<" end:"<<end<<endl;
    long c=sqrt(end);
    long number=end-begin+1;
    bool ifOdd=begin%2;
    for(int i=3;i<=c;i+=2){
        long i2=i<<1;
        long j=begin/i*i-begin;
        if(j<0)j+=i;
        for(;j<number;j+=i2)
        {
            bv[j]=false;
        }
    }
    int i;
    if(ifOdd)i=0;
    else i=1;
    for(;i<number;i+=2){
        if(bv[i]==true)
        {
            num+=(begin+i);
        }
    }
    cout<<"tid"<<tid<<":"<<num<<endl;
    
}
int main(){
    vector<bool>bv(11,true);
    long num=0;
    call_from_thread(0,0,10,bv,ref(num));
    return 0;
}

//int main(int argc, const char * argv[]) {
//    long a=0;
//    long b=1000000000;
////    long a;//input a
////    long b;//input b
////    cout<<"input a"<<endl;
////    cin>>a;
////    cout<<"input b"<<endl;
////    cin>>b;
////    double c=sqrt(b);
//    long n=b-a+1;
//    
//    //inilize the mutilthread
//    const int num_threads = 8;
//    thread t[num_threads];
//    long num[num_threads];
//    long chunk=n/num_threads;
//    vector<vector<bool>>bv;
//    for(int i=0;i<num_threads;i++)
//    {
//        
//        if(num_threads==i+1){
//            long lastchunk=n-chunk*(num_threads-1);
//            bv.push_back(vector<bool>(lastchunk,true));
//        }
//        else{
//            bv.push_back(vector<bool>(chunk,true));
//        }
//    }
//    
////    vector<bool>bv(n,true);
//
//    
//    //Launch a group of threads
//    for (int i = 0; i < num_threads; i++) {
//        long begin=a+chunk*i;
//        long end;
//        if(num_threads==i+1){
//            end=b;
//        }else
//        {
//            end=a+chunk*(i+1)-1;
//        }
//        num[i]=0;
//        t[i] = thread(call_from_thread, i,begin,end,bv[i],ref(num[i]));
//    }
//    
//    std::cout << "Launched from the main\n";
//    
//    //Join the threads with the main thread
//    for (int i = 0; i < num_threads; ++i) {
//        t[i].join();
//    }
//    
//    long totoalNum=0;
//    for(int i=0;i<num_threads;i++)
//    {
//        totoalNum+=num[i];
//    }
//    cout<<totoalNum;
//    
////    long num=0;
////    for(long i=3;i<n;i+=2)
////    {
////        if(bv[i]==true)
////            num+=i;
////    }
////    //output the result
////    num+=2;
////    cout<<"the prime sum is "<<num<<endl;
//    return 0;
//}
