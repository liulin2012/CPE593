//
//  main.cpp
//  prime
//
//  Created by lin liu on 2/15/15.
//  Copyright (c) 2015 lin. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
#include <thread>
using namespace std;

//input the __int128
std::ostream& operator<<( std::ostream& dest, __int128_t value ) {
    std::ostream::sentry s( dest );
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char* d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
            --d;
            *d = '-';
        }
        long len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

//the thread
void call_from_thread(int tid,long begin,long end,vector<bool> bv,__int128 &num,vector<bool> bvf) {
    long c=sqrt(end);
    long number=end-begin+1;
    bool ifOdd=begin%2;
    bool ifFirstNum;
    long i2;
    long theFirst;
    long j;
    for(int i=3;i<=c;i+=2){
        if(bvf[i]){
            i2=i<<1;
            theFirst=begin/i;
            if(theFirst<3)theFirst=3;
            j=theFirst*i-begin;
            if(j<0)j+=i;
            ifFirstNum=j%2;
            if(ifOdd==ifFirstNum) j+=i;
            for(;j<number;j+=i2)
            {
                bv[j]=false;
            }
        }
    
    }
    if(begin==0){bv[0]=bv[1]=false;num=2;}
    else if(begin==1){bv[0]=false;num=2;}
    else if(begin==2){num=2;}
    
    int i;
    if(ifOdd)i=0;
    else i=1;
    for(;i<number;i+=2){
        if(bv[i]==true)
        {
            num+=(begin+i);
        }
    }
}

int main(int argc, const char * argv[]) {
    long a;//input a
    long b;//input b
    cout<<"input a"<<endl;
    cin>>a;
    cout<<"input b"<<endl;
    cin>>b;
    long n=b-a+1;
    auto t_start = std::chrono::high_resolution_clock::now();
    //inilize the mutilthread
    const int num_threads = 1000;
    thread t[num_threads];
    __int128 num[num_threads];
    long chunk=n/num_threads;
    vector<vector<bool>>bv;
    for(int i=0;i<num_threads;i++)
    {
        
        if(num_threads==i+1){
            long lastchunk=n-chunk*(num_threads-1);
            bv.push_back(vector<bool>(lastchunk,true));
        }
        else{
            bv.push_back(vector<bool>(chunk,true));
        }
    }
    
    //ininlize the first array
    long c=sqrt(b);
    vector<bool>bvf(c,true);
    for(int i=3;i<=c;i+=2){
        if(bvf[i]){
            int i2=i<<1;
            for(int j=i*i;j<c;j+=i2)
            {
                bvf[j]=false;
            }
        }
    }
    cout<<"creat the main,thread number:"<<num_threads<<endl;
    
    long begin=a-chunk;
    long end=a-1;
    //Launch a group of threads
    for (int i = 0; i < num_threads; i++) {
        begin+=chunk;
        if(num_threads==i+1){
            end=b;
        }else
        {
            end+=chunk;
        }
        num[i]=0;
        t[i] = thread(call_from_thread, i,begin,end,bv[i],ref(num[i]),bvf);
    }
    
    std::cout << "Launched from the main\n";
    
    //Join the threads with the main thread
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }
    
    __int128 totoalNum=0;
    for(int i=0;i<num_threads;i++)
    {
        totoalNum+=num[i];
    }
    cout<<"The sum of the primes:"<<totoalNum <<endl;
    
    auto t_end = std::chrono::high_resolution_clock::now();
    cout<<"The execution time:"<<(chrono::duration<double, std::milli>(t_end-t_start).count())/1000<<" Sec"<<endl;

    return 0;
}
