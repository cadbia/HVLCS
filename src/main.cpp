#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <chrono>
#include "hvlcs.h"

using namespace std::chrono;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 1;
	}

	std::ifstream infile(argv[1]);
	if (!infile.is_open()) {
		std::cerr << "Error: Could not open file " << argv[1] << std::endl;
		return 1;
	}

	int K;
	infile >> K;

	std::unordered_map<char, int> val;
	for (int i = 0; i < K; ++i) {
		char c;
		int v;
		infile >> c >> v;
		val[c] = v;
	}

	std::string A, B;
	infile >> A >> B;

	infile.close();

	HVLCSResult result = compute_hvlcs(A, B, val);
	std::cout << result.bestValue << std::endl;
	std::cout << result.subseq << std::endl;
	
	auto start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++) {
		compute_hvlcs(A, B, val);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Algorithm time: " << duration.count() / 1000 << " miseconds" << std::endl;
	return 0;
}
