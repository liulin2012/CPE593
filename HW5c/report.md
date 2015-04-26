#CPE593-HW5c

##lin liu 10397798

###1024x1024
Strassen

```
➜  HW5c git:(master) ✗ time ./a.out > result.txt
./a.out > result.txt  6.92s user 0.13s system 99% cpu 7.084 total
```

No Strassen
```
➜  HW5c git:(master) ✗ time ./a.out > result.txt
./a.out > result.txt  17.32s user 0.06s system 99% cpu 17.396 total
```

###2048x2048 

Strassen
```
➜  HW5c git:(master) ✗ time ./a.out > result1.txt  
./a.out > result1.txt  40.92s user 0.82s system 99% cpu 41.912 total
```

No Strassen
```
➜  HW5c git:(master) ✗ time ./a.out > result2.txt
./a.out > result2.txt  141.53s user 0.39s system 99% cpu 2:22.39 total
```