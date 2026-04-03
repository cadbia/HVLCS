#include "hvlcs.h"
#include <vector>

HVLCSResult compute_hvlcs(
	const std::string& A,
	const std::string& B,
	const std::unordered_map<char, int>& val
) {
	int n = A.length();
	int m = B.length();

	// dp[i][j] = max val for A[0..i) and B[0..j)
	std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(m + 1, 0));

	// Track reconstruction dir
	// 0 -> match (diagonal), 1 -> skip A (up), 2 -> skip B (left)
	std::vector<std::vector<int>> parent(n + 1, std::vector<int>(m + 1, 0));

	// Fill DP table
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			long long valSkipA = dp[i - 1][j];
			long long valSkipB = dp[i][j - 1];

			// check if chars match and char has assigned val
			bool canMatch = (A[i - 1] == B[j - 1]) && (val.find(A[i - 1]) != val.end());
			long long valMatch = canMatch ?
				dp[i - 1][j - 1] + val.at(A[i - 1]) :
				-1e18;

			if (canMatch && valMatch >= valSkipA && valMatch >= valSkipB) {
				dp[i][j] = valMatch;
				parent[i][j] = 0; // match
			}
			else if (valSkipA >= valSkipB) {
				dp[i][j] = valSkipA;
				parent[i][j] = 1; // skip A
			}
			else {
				dp[i][j] = valSkipB;
				parent[i][j] = 2; // skip B
			}
		}
	}

	// Reconstruct the subseq by backtracking
	std::string subseq;
	int i = n, j = m;
	while (i > 0 && j > 0) {
		if (parent[i][j] == 0) { // match
			subseq = A[i - 1] + subseq;
			--i;
			--j;
		}
		else if (parent[i][j] == 1) { // skip A
			--i;
		}
		else { // skip B
			--j;
		}
	}

	return {dp[n][m], subseq};
}
