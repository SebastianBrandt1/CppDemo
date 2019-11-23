#include "MatrixAlgorithm.h"

MatrixAlgorithm::MatrixAlgorithm() : DemoCase(){

	gCostMatrix = {
		   {5,8,3},
		   {7,4,6},
		   {5,7,9}
	};

	mSize = 3;
	numLoops = 0;
}

std::vector<std::vector<Int64>> MatrixAlgorithm::GenerateMatrix(int size) {
	if (size == 3) {
		return {
					  {5,8,3},
					  {7,4,6},
					  {5,7,9}
		};
	}
	std::vector<std::vector<Int64>> result;
	for (int i = 0; i < size; ++i) {
		auto row = std::vector<Int64>{};
		for (int j = 0; j < size; ++j) {
			row.push_back(5);
		}
		result.push_back(row);
	}
	return result;
}




std::vector<std::vector<Int64>> MatrixAlgorithm::GetPrepreprocessedCostMatrix(const std::vector<std::vector<Int64>>& pCostMatrix) {
	std::vector<Int64> lMinimumNonDiagonalCosts;
	for (int lTo = 0; lTo < mSize; ++lTo) {
		Int64 lMinimumNonDiagonalCost = pCostMatrix[0][lTo];
		for (int lFrom = 1; lFrom < mSize; ++lFrom) {
			if (lTo != lFrom) {
				Int64 lCost = pCostMatrix[lFrom][lTo];
				if (lCost < lMinimumNonDiagonalCost) {
					lMinimumNonDiagonalCost = lCost;
				}
			}
		}
		lMinimumNonDiagonalCosts.push_back(lMinimumNonDiagonalCost);
	}
	std::vector<std::vector<Int64>> lCostMatrix;
	for (size_t i = 0; i < mSize; ++i) {
		std::vector<Int64> lAdjustedCosts = pCostMatrix.at(i) - lMinimumNonDiagonalCosts;
		lCostMatrix.push_back(lAdjustedCosts);
	}
	return lCostMatrix;
}

std::vector<std::vector<Int64>> MatrixAlgorithm::GetPrepreprocessedCostMatrixAlgo(const std::vector<std::vector<Int64>>& pCostMatrix) {
	std::vector<Int64> lMinimumNonDiagonalCosts;
	for (int lTo = 0; lTo < mSize; ++lTo) {
		Int64 lMinimumNonDiagonalCost = pCostMatrix[0][lTo];
		auto beginIterator = ++cbegin(pCostMatrix[lTo]);
		if (lTo == 1) {
			++beginIterator;
		}
		auto minCost = *(std::min_element(beginIterator, cend(pCostMatrix[lTo]), [&](Int64 const& lhs, Int64 const& rhs) {
			return ((lhs < rhs) && (&lhs != &pCostMatrix[lTo][lTo]));
			}));
		lMinimumNonDiagonalCosts.push_back(std::min(lMinimumNonDiagonalCost, minCost));
	}
	std::vector<std::vector<Int64>> lCostMatrix(mSize);
	for (size_t i = 0; i < mSize; ++i) {
		std::vector<Int64> lAdjustedCosts = pCostMatrix.at(i) - lMinimumNonDiagonalCosts;
		lCostMatrix[i] = lAdjustedCosts;
	}
	return lCostMatrix;
}

std::vector<std::vector<Int64>> MatrixAlgorithm::GetPrepreprocessedCostMatrixAlgoV2(const std::vector<std::vector<Int64>>& pCostMatrix) {
	std::vector<std::vector<Int64>> result;
	result.reserve(mSize);

	auto findMinimumColumnValues = [&](auto const& pRowBeginIterator, auto const& pRowEndIterator) {
		std::vector<Int64> minima;
		minima.reserve(mSize);
		for (int pColumn = 0; pColumn < mSize; ++pColumn) {

			auto CompareAndExcludeDiagonal = [&](auto const& lhs, auto const& rhs) {
				return ((lhs[pColumn] < rhs[pColumn]) && (&lhs[pColumn] != &pCostMatrix[pColumn][pColumn]));
			};
			auto minimumElementRow = *(std::min_element(pRowBeginIterator, pRowEndIterator, CompareAndExcludeDiagonal));
			minima.push_back(minimumElementRow[pColumn]);
		}
		return minima;
	};

	auto minimumColumnValues = findMinimumColumnValues(cbegin(pCostMatrix), cend(pCostMatrix));
	auto processRow = [&minimumColumnValues](auto& row) { return row - minimumColumnValues; };

	std::transform(cbegin(pCostMatrix), cend(pCostMatrix), std::back_inserter(result), processRow);

	return result;
}


std::vector<std::vector<Int64>> MatrixAlgorithm::GetPrepreprocessedCostMatrixAlgoV3(const std::vector<std::vector<Int64>>& pCostMatrix) {
	std::vector<std::vector<Int64>> result;
	result.reserve(mSize);

	auto findMinimumColumnValues = [&](auto const& pRowBeginIterator, auto const& pRowEndIterator) {
		std::vector<Int64> minima(mSize, std::numeric_limits<Int64>::max());

		auto EvalMin = [&](auto const& row) {
			auto index = 0;
			for (auto const& value : row) {
				minima[index] = std::min(value, minima[index]);
				++index;
			}
		};
		std::for_each(pRowBeginIterator, pRowEndIterator, EvalMin);
		return minima;
	};

	auto minimumColumnValues = findMinimumColumnValues(cbegin(pCostMatrix), cend(pCostMatrix));
	auto processRow = [&minimumColumnValues](auto& row) { return row - minimumColumnValues; };

	std::transform(cbegin(pCostMatrix), cend(pCostMatrix), std::back_inserter(result), processRow);

	return result;
}

std::vector<std::vector<Int64>> MatrixAlgorithm::GetPrepreprocessedCostMatrixAlgoV4(const std::vector<std::vector<Int64>>& pCostMatrix) {
	std::vector<std::vector<Int64>> result;
	result.reserve(mSize);

	auto findMinimumColumnValues = [&](auto const& pRowBeginIterator, auto const& pRowEndIterator) {
		std::vector<Int64> minima;
		minima.reserve(mSize);
		auto const* compRef = &pCostMatrix[0][0];

		auto CompareAndExcludeDiagonal = [&](auto const& lhs, auto const& rhs) {
			return ((lhs < rhs) && (&lhs != compRef));
		};

		auto numRow = 0;
		for (auto iter = pRowBeginIterator; iter != pRowEndIterator; iter++) {
			compRef = &pCostMatrix[numRow][numRow];
			auto minimumElementRow = *(std::min_element(cbegin(*iter), cend(*iter), CompareAndExcludeDiagonal));
			minima.push_back(minimumElementRow);
			numRow++;
		}


		return minima;
	};

	auto minimumColumnValues = findMinimumColumnValues(cbegin(pCostMatrix), cend(pCostMatrix));
	auto processRow = [&minimumColumnValues](auto& row) { return row - minimumColumnValues; };

	std::transform(cbegin(pCostMatrix), cend(pCostMatrix), std::back_inserter(result), processRow);

	return result;
}



int MatrixAlgorithm::Run() {
	gCostMatrix = GenerateMatrix(mSize);
	auto start = std::chrono::high_resolution_clock::now();
	auto matrix = GetPrepreprocessedCostMatrix(gCostMatrix);
	for (int i = 0; i < numLoops; ++i) {
		matrix = GetPrepreprocessedCostMatrix(gCostMatrix);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Calculation time: " << duration.count() << "ms\n";
	for (auto& row : matrix) {
		for (auto& column : row) {
			//(column < 0) ? (std::cout << " " << column) : (std::cout << "  " << column);
		}
		//std::cout << '\n';
	}


	/*start = std::chrono::high_resolution_clock::now();
	auto matrix2 = GetPrepreprocessedCostMatrixAlgo(gCostMatrix);
	for (int i = 0; i < numLoops; ++i) {
		matrix2 = GetPrepreprocessedCostMatrixAlgo(gCostMatrix);
	}
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Calculation time: " << duration.count() << "ms\n";
	for (auto& row : matrix2) {
		for (auto& column : row) {
			//(column < 0) ? (std::cout << " " << column) : (std::cout << "  " << column);
		}
		//std::cout << '\n';
	}

	start = std::chrono::high_resolution_clock::now();
	auto matrix3 = GetPrepreprocessedCostMatrixAlgoV2(gCostMatrix);
	for (int i = 0; i < numLoops; ++i) {
		matrix3 = GetPrepreprocessedCostMatrixAlgoV2(gCostMatrix);
	}
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Calculation time: " << duration.count() << "ms\n";
	for (auto& row : matrix3) {
		for (auto& column : row) {
			//(column < 0) ? (std::cout << " " << column) : (std::cout << "  " << column);
		}
		//std::cout << '\n';
	}*/

	start = std::chrono::high_resolution_clock::now();
	auto matrix4 = GetPrepreprocessedCostMatrixAlgoV3(gCostMatrix);
	for (int i = 0; i < numLoops; ++i) {
		matrix4 = GetPrepreprocessedCostMatrixAlgoV3(gCostMatrix);
	}
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Calculation time: " << duration.count() << "ms\n";
	for (auto& row : matrix4) {
		for (auto& column : row) {
			(column < 0) ? (std::cout << " " << column) : (std::cout << "  " << column);
		}
		std::cout << '\n';
	}

	/*start = std::chrono::high_resolution_clock::now();
	auto matrix5 = GetPrepreprocessedCostMatrixAlgoV4(gCostMatrix);
	for (int i = 0; i < numLoops; ++i) {
		matrix5 = GetPrepreprocessedCostMatrixAlgoV4(gCostMatrix);
	}
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Calculation time: " << duration.count() << "ms\n";
	for (auto& row : matrix5) {
		for (auto& column : row) {
			//(column < 0) ? (std::cout << " " << column) : (std::cout << "  " << column);
		}
		//std::cout << '\n';
	}*/
	return 0;
}

