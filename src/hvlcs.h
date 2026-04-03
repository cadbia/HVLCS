#ifndef HVLCS_H
#define HVLCS_H

#include <string>
#include <unordered_map>

struct HVLCSResult
{
	long long bestValue;
	std::string subseq;
};

HVLCSResult compute_hvlcs(
	const std::string& A,
	const std::string& B,
	const std::unordered_map<char, int>& val
);

#endif // HVLCS_H
