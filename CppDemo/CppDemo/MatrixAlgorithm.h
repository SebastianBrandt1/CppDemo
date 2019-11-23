#pragma once
#include "DemoCase.h"

using Int64 = long long;

template <typename T> std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	std::vector<T> result;
	result.reserve(a.size());

	std::transform(a.begin(), a.end(), b.begin(),
		std::back_inserter(result),
		std::minus<T>());
	return result;
}

class MatrixAlgorithm :
	public DemoCase
{
public:
	
	MatrixAlgorithm();
	
	int Run() override;
	std::vector<std::vector<Int64>> GenerateMatrix(int size = 3);
	std::vector<std::vector<Int64>> GetPrepreprocessedCostMatrix(const std::vector<std::vector<Int64>>& pCostMatrix);
	std::vector<std::vector<Int64>> GetPrepreprocessedCostMatrixAlgo(const std::vector<std::vector<Int64>>& pCostMatrix);
	std::vector<std::vector<Int64>> GetPrepreprocessedCostMatrixAlgoV2(const std::vector<std::vector<Int64>>& pCostMatrix);
	std::vector<std::vector<Int64>> GetPrepreprocessedCostMatrixAlgoV3(const std::vector<std::vector<Int64>>& pCostMatrix);
	std::vector<std::vector<Int64>> GetPrepreprocessedCostMatrixAlgoV4(const std::vector<std::vector<Int64>>& pCostMatrix);	

	std::vector<std::vector<Int64>> gCostMatrix;
	int mSize = 3;
	int numLoops = 0;
	
};

