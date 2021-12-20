## Pascal Triangle Calculation

The funcion `bc_dp` is a binomial coefficient (pascal triangle) function calculated using dynamic programming techniques (from: Steven S. Skiena - The Algorithm Design Manual-Springer (2020)) 

Basically, to calculate any number we only have to keep in memory two arrays (or a single 2-dimension array) because the value of a number at `[n][k]` is defined as `[n-1][k] + [n-1][k-1]`.

Or, defining Pascal's triangle recursively: 

`pasc(n, k) = pasc(n-1, k) + pasc(n-1, k-1)`

`bc_better` is my optimization on top of it. It optimizes in the following way:
- The first and last numbers in each "row" of Pascal's triangle is 1, so if k = 0 or k = n (the last number), the function returns 1 immediately.
- The second and second-to-last numbers are equal to the row's index (e. g. `[4, 1]` and `[4, 3]` should return `4`), so if `k = 1` or `k = n - k`, the function returns `n` immediately.
- Lastly, and more importantly, Pascal's triangle is symmetric. So we only have to calculate half of it. This is done in the auxiliary function `aux_bc_better`.

To compare both functions, I added a cpu time counter.
- Run the program
- call the function followed by `n` and `k`, e.g.

```
./a.out
function: bc_dp 250 100
result: 1103510280765129870
cpu time: 0.000654
```

- compare to:

```
./a.out 
function: bc_better 250 100
result: 1103510280765129870
cpu time: 0.000130
```