#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXN 250
#define UNKNOWN -1

long long bc_dp(int n, int k);
long long bc_better(int n, int k);
long long aux_bc_better (int n, int k);

/* bc_dp is a binomial coefficient (pascal triangle) function calculated using dynamic programming techniques (from: Steven S. Skiena - The Algorithm Design Manual-Springer (2020)) 

Basically to calculate any number we only have to keep in memory two arrays (or a single 2-dimension array) because the value of a number at [n][k] is defined as [n-1][k] + [n-1][k-1]

Or, defining Pascal's triangle recursively: 

pasc(n, k) = pasc(n-1, k) + pasc(n-1, k-1)
*/

/* 
bc_better is my optimization on top of it. It optimizes in the following way:
- The first and last numbers in each "line" of Pascal's triangle is 1, so if k = 0 or k = n (the last number), the function returns 1 immediately
- The second and second-to-last numbers are equal to the line's index (e. g. [4, 1] and [4, 3] should return 4), so if k = 1 or k = n - k, the function return n immediately
- Lastly, and more importantly, Pascal's triangle is symmetric. So we only have to calculate half of it. This is done in aux_bc_better.
*/

/*
to compare both functions, I added a cpu time counter.
- Run the program
- call the function followed by n and k, e.g.

> ./a.out
function: bc_dp 250 100
result: 1103510280765129870
cpu time: 0.000654

compare to:

> ./a.out 
function: bc_better 250 100
result: 1103510280765129870
cpu time: 0.000130

*/

int main(void) {

  char fname[7];
  int nval, kval;
  printf("function: ");
  scanf("%s %i %i", fname, &nval, &kval);

  char algo1[] = "bc_dp";
  char algo2[] = "bc_better";
  int result1 = strcmp(fname, algo1);
  int result2 = strcmp(fname, algo2);

  if (result1 == 0) { 
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    long long result = bc_dp(nval, kval);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("result: %lld\ncpu time: %lf\n", result, cpu_time_used);
  } else if (result2 == 0) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    long long result = bc_better(nval, kval);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("result: %lld\ncpu time: %lf\n", result, cpu_time_used);
  } else {
    printf("Not a function name\n");
  }

  return 0;
}

long long bc_dp(int n, int k) {
  int i, j;
  long bc[MAXN+1][MAXN+1];

  for(i = 0; i <= n; i++) {
    bc[i][0] = 1;
  }

  for(j = 0; j <= n; j++) {
    bc[j][j] = 1;
  }

  for (i = 2; i <= n; i++) {
    for (j = 1; j < i; j++) {
      bc[i][j] = bc[i-1][j-1] + bc[i-1][j];
    }
  }
  return (bc[n][k]);
}

long long bc_better(int n, int k) {
  if (k == 0 || k == n) {
    return 1;
  } else if (k == 1 || k + 1 == n) {
    return n;
  } else {
    return aux_bc_better (n,k);
  }
}

long long aux_bc_better (int n, int k) {

    /* 
    for me it makes more sense to think in two arrays instead of one bi-dimensional array. So we will create two: a current (curr) one, which we are building based on the values of a previous (prev) array. We will initiate them in the values of n = 4 and k = 1, since all the other previous values are automatically calculated by the conditionals in bc_better
    */

    int i = 4;
    int j = 1;
    long curr[MAXN+1] = {1};
    long prev[MAXN+1] = {1, 3};

    while (i <= n) {
      if (i == n) {
        if ( k * 2 > n ) { return prev[n - k] + prev[n - k - 1]; }
        else if ( k * 2 == n ) { return prev[k - 1] * 2; }
        else { return prev[k] + prev[k - 1]; }
      } else if ( j * 2 > i) {
        memcpy(prev, curr, sizeof(prev));
        curr[0] = 1;
        j = 1;
        i++;
      } else if ( j * 2 == i) {
        curr[j] = prev[j-1] * 2;
        memcpy(prev, curr, sizeof(prev));
        curr[0] = 1;
        j = 1;
        i++;
      } else {
        curr[j] = prev[j] + prev[j-1];
        j++;
      }
    }
    return 0;
  }