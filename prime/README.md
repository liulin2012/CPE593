#HW1b - Optional - Prime Contest

##Algorithm
I have used the [Sieve_of_Eratosthenes ](http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)algorithm to delete the primes from the vector.

##Multi-thread
I have used the multithread technology to speed up the program.I have test some data.You can change the thread number to check the answer and find the best thread number in this experiment.

Data|Thread number|Execution time
:----:|:-------------:|:-------------:
1~$$$10^9$$$|1000|0.6 Sec
1~$$$10^{10}$$$|5000|6.8 Sec
1~$$$10^{11}$$$|10000|90 Sec

![Imgur](http://i.imgur.com/f8dSURel.png)

![Imgur](http://i.imgur.com/0NN7rXal.png)

![Imgur](http://i.imgur.com/oNFQTwTl.png)

##Compiler optimize


	clang++ -std=c++11  -O2 main.cpp
I have use the `-O2` to optimize the compiler and then
	
	./a.out
This trick can [Maximize Speed](https://msdn.microsoft.com/en-us/library/8f8h5cxt.aspx) when compile the C++ code.

##Analyze
I have research on on the internet
>The bit complexity of the algorithm is O(n (log n) (log log n)) bit operations with a memory requirement of O(n).

My result show above when I test the data $$$10^{9}$$$,$$$10^{10}$$$,$$$10^{11}$$$.Due to the algorithm complexity,I calculate the $$$10^{12}$$$ need to use 17 minute.

##Final
If you have any question,be free to contact me.Thank you.

* Author:lin
* Email:liulin.jacob@gmail.com



