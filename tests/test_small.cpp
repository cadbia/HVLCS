#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../src/hvlcs.h"

// helper: check if subseq is a valid common subsequ of A and B
bool isValidSubseq(
	const std::string& subseq,
	const std::string& A,
	const std::string& B
) {
	int posA = 0, posB = 0;
	for (char c : subseq) {
		// Find c in A starting from posA
		bool foundA = false;
		while (posA < (int)A.length()) {
			if (A[posA] == c) {
				++posA;
				foundA = true;
				break;
			}
			++posA;
		}
		if (!foundA) {
			return false;
		}

		// Find c in B starting from posB
		bool foundB = false;
		while (posB < (int)B.length()) {
			if (B[posB] == c) {
				++posB;
				foundB = true;
				break;
			}
			++posB;
		}
		if (!foundB) {
			return false;
		}
	}
	return true;
}

// helper: compute the total value of a subsequence
long long computeValue(
	const std::string& subseq,
	const std::unordered_map<char, int>& val
) {
	long long total = 0;
	for (char c : subseq) {
		auto it = val.find(c);
		if (it != val.end()) {
			total += it->second;
		}
	}
	return total;
}

int main() {
	// Test 1: Identical strings -> should return all characters
	{
		std::string A = "ABC";
		std::string B = "ABC";
		std::unordered_map<char, int> val = {
			{'A', 1}, {'B', 2}, {'C', 3}
		};
		HVLCSResult result = compute_hvlcs(A, B, val);
		assert(result.bestValue == 6); // 1 + 2 + 3
		assert(isValidSubseq(result.subseq, A, B));
		assert(computeValue(result.subseq, val) == result.bestValue);
		std::cout << "Test 1 passed\n";
	}

	// Test 2: Partial overlapping subseq
	{
		std::string A = "AGGTAB";
		std::string B = "GXTXAYB";
		std::unordered_map<char, int> val = {
			{'A', 1}, {'G', 2}, {'T', 3}, {'B', 4}, {'X', 10}, {'Y', 5}
		};
		HVLCSResult result = compute_hvlcs(A, B, val);
		// Common subsequences: "GAB" (2+1+4=7), "GTAB" (2+3+1+4=10), etc.
		assert(isValidSubseq(result.subseq, A, B));
		assert(computeValue(result.subseq, val) == result.bestValue);
		std::cout << "Test 2 passed\n";
	}

	// Test 3: No common subseq
	{
		std::string A = "XY";
		std::string B = "AB";
		std::unordered_map<char, int> val = {
			{'X', 1}, {'Y', 2}, {'A', 3}, {'B', 4}
		};
		HVLCSResult result = compute_hvlcs(A, B, val);
		assert(result.bestValue == 0);
		assert(result.subseq == "");
		std::cout << "Test 3 passed\n";
	}

	std::cout << "All tests passed!\n";
	return 0;
}
