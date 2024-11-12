#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
/**
 * A C program that implements the Sieve of Eratosthenes
 * parallelized with Open MP. The algorithm  has been 
 * improved by storing only the marks for odd numbers >= 3 
 * in the array prime.
 *
 * The benefit from the parallelization can be noticed 
 * when running the program for fairly large N's 
 * (N > 1000000). Here are some test execution results
 * when executed on maximum.cs.abo.fi:
 * 
 * N = 10000000
 * Non-parallelized execution took 16.36 seconds.
 * Parallelized execution took 16.04 seconds.
 * 
 * N = 100000000
 * Non-parallelized execution took 209.44 seconds.
 * Parallelized execution took 206.34 seconds.
 * 
 * Compile the program with 'cc primes.c -o primes -fopenmp'
 * Run the program with './primes'
 *
 * @author Markus Karjalainen (uid markarja, matnr. 29849)
 * @version 2010-10-13
 *  
 **/
int main(int argc, char *argv[]) {
  
  double start = 0, end = 0;

  const char marked = (char)1;
  const char unmarked = (char)0; 

  int N = 0;
  
  printf("Enter a natural number N: ");
  scanf("%d", &N);
  
  if(N < 3) {
    printf("You need to enter a number that is greater than 3");
    exit(0);
  }

  start = omp_get_wtime();
  
  int s = (N - 3) / 2 + 2;

  char* prime = (char*)malloc(sizeof(char) * s);
  
  int i = 0, k = 0;
  
  #pragma omp parallel

    #pragma omp for
    for(i = 0;i < s;i++) {
      prime[i] = unmarked;
    }
  
    #pragma omp for nowait
    for(i = 3;i <= N;i++) {
      if(i % 2 != 0) {
        for(k = i+i;k<=N;k+=i) {
          if(k % 2 != 0) {
            prime[(k - 1) / 2] = marked;
          }
        }
      }
    }
  
    int count = 0;
    int max = 0;

    #pragma omp for nowait
    for(i = 0;i < s;i++) {
      if(i == 0) {
        max = 2;
        count++;
      } else if(prime[i] == unmarked) { 
        max = 2 * i + 1;
        count++;
      }
    }
 
  end = omp_get_wtime();
  
  printf("There are %d primes which are less than or equal to N = %d\n", count, N);
  printf("The largest prime less than or equal to N = %d is %d\n", N, max);

  printf("The execution took: %2.2f seconds.\n", end - start);
  
  free(prime);

  exit(0); 

}

