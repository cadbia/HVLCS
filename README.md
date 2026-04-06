# Highest Value Longest Common Subsequence (HVLCS)

## Project Overview

C++ implementation of the Highest Value Longest Common Subsequence problem.

## Build Instructions

Compile with C++17:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic -o hvlcs src/main.cpp src/hvlcs.cpp
```

## Run Instructions

Run the program on the example:

```bash
./hvlcs data/example.in
```

Expected output:

```
8
ACD
```

## Verify Output

To verify the output against the expected result:

```bash
./hvlcs data/example.in > output.txt
diff output.txt data/example.out
```

If no output is printed by `diff`, the output matches exactly.

## Input Format

```
K
c1 v1
c2 v2
...
cK vK
A
B
```

Where:
- K: number of characters with assigned values
- ci: character, vi: integer value
- A, B: strings to find the HVLCS for

## Questions

### Q1

Test cases are stored in /data
```
data/q1test1.txt
data/q1test2.txt
...
data/q1test10.txt
```
![Example Image](/images/HVLCS_Algorithm_Runtime_Graph.png)

### Q2

```
OPT = Maximum total value of a common subsequence between A and B
OPT = dp[i][j] where A[0,...,i-1] and B[0,...,j-1].

Base cases
    dp[0][j] = 0
    dp[i][0] = 0
For i>=1, j>=1:
    if A[i-1] = B[j-1], dp[i][j] = max(dp[i-1][j], dp[i][j-1], dp[i-1][j-1] + val(A[i-1]))
otherwise
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```
At every position [i][j] we either skip A dp[i-1][j], skip B dp[i][j-1], or the characters match. If the characters match, we add the value of the caracter to our OPT. This covers every possible case to increase our subsequence's value.

### Q3

```
compute_hvlcs(A, B, values):
    n = length(A)
    m = length(B)

    CREATE dp[0..n][0..m], initialize all to 0
    CREATE parent[0..n][0..m] // tracks our subsequence to help reconstruct later

    for i = 1; i <= n; i++:
        for j = 1; j <= m; j++:
            valSkipA = dp[i-1][j]
            valSkipB = dp[i][j-1]

            if characters A[i-1] and B[j-1] match (are equal) and A[i-1] exists in values:
                valMatch = dp[i-1][j-1] + values[A[i-1]]
                canMatch = TRUE
            else:
                valMatch = -infinity
                canMatch = FALSE
            
            if canMatch and valMatch >= valSkipA and valMatch >= valSkipB:
                dp[i][j] = valMatch
                parent[i][j] = "case1"   // match
            elif valSkipA >= valSkipB:
                dp[i][j] = valSkipA
                parent[i][j] = "case2"   // skip A
            else:
                dp[i][j] = valSkipB
                parent[i][j] = "case3"   // skip B

    // Reconstruct subsequence
    subseq = empty string
    i = n, j = m

    while i > 0 and j > 0:
        if parent[i][j] = "case1":
            prepend A[i-1] to subseq
            i = i - 1
            j = j - 1
        elif parent[i][j] = "case2":
            i = i - 1
        else:            // "case3"
            j = j - 1

    return (dp[n][m], subsequence)
```
Time complexity: O(n * m)
- Nested loop O(n * m)
    - Constant time operations inside this loop
- Reconstructing sequence/Backtracking takes O(n + m)
- (n * m) + (n + m) = O(n * m) run time