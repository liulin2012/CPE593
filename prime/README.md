#HW1b - Optional - Prime Contest

##Algorithm
I have used the [Sieve_of_Eratosthenes ](http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)algorithm to delete the primes from the vector.

##Multi-thread
I have used the multithread technology to speed up the program.I have test some data.

Data|Thread number|Execution time
:----:|:-------------:|:-------------:
1~$$$10^9$$$|1000|0.6 Sec
1~$$$10^{10}$$$|5000|6.8 Sec
1~$$$10^{11}$$$|10000|90 Sec



	input a
	0
	input b
	10000000000
	creat the main,thread number:5000
	Launched from the main
	The sum of the primes:2220822432581729238
	The execution time:6.89083 Sec

![Imgur](http://i.imgur.com/f8dSURel.png)

![Imgur](http://i.imgur.com/0NN7rXal.png)

![Imgur](http://i.imgur.com/oNFQTwTl.png)

##Compiler optimize


	clang++ -std=c++11  -O2 main.cpp
I have use the **-O2** to optimize the compiler and then
	
	./a.out
This trick can [Maximize Speed](https://msdn.microsoft.com/en-us/library/8f8h5cxt.aspx) when compile the C++ code.

