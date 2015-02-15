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

int main(int argc, const char * argv[]) {
    long a=0;//input a
    long b=1000000000;//input b
    double c=sqrt(b);
    long n=b-a+1;
    vector<bool>bv(n,true);
    for(long i=3;i<=c;i+=2){
        if(bv[i]){
            long i2=i<<1;
            for(long j=i*i; j<n;j+=i2)
            {
                bv[j]=false;
            }
        }
    }
    long num=0;
    for(long i=3;i<n;i+=2)
    {
        if(bv[i]==true)
            num+=i;
    }
    //output the result
    num+=2;
    cout<<"the prime sum is "<<num<<endl;
    return 0;
}
