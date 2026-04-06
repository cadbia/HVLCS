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

![Example Image](/images/HVLCS_Algorithm_Runtime_Graph.png)

### Q2

TODO: Add question 2 here

### Q3

TODO: Add question 3 here