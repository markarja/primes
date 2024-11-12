# primes.c
  
A C program that implements the *Sieve of Eratosthenes* parallelized with Open MP. The algorithm has been improved by storing only the marks for odd numbers >= 3 in the array prime.
 
The benefit from the parallelization can be noticed when running the program for fairly large N's (N > 1000000). Here are some test execution results when executed on maximum.cs.abo.fi:
  
N = 10000000
Non-parallelized execution took 16.36 seconds.
Parallelized execution took 16.04 seconds.
  
N = 100000000
Non-parallelized execution took 209.44 seconds.
Parallelized execution took 206.34 seconds.
  
Compile the program with `cc primes.c -o primes -fopenmp` Run the program with `./primes`

**Author:** Markus Karjalainen (uid markarja, matnr. 29849)
**Version:** 2010-10-13
