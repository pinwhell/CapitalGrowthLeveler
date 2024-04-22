#pragma once

#include <exception>

namespace CGL {

	class InvalidRiskPercentageException : public std::exception {};
	class InvalidNRisksArgException : public std::exception {};

	struct CapitalGrowthLeveler {
		CapitalGrowthLeveler(double riskPerc, int nR = 1);

		double mRiskPerc;
		int mnR; // Numbers of Rs to the next level
		double mLevelStridePerc;
	};

	constexpr auto MAX_SEARCH_LEVEL_ITERATIONS = 10000;

	double PercGrowValue(double value, double perc);
	double Perc2Raw(double perc);

	double PositionSizeGet(double riskAount, double overMovePercentage);
	double NextLevelGet(const CapitalGrowthLeveler& , double currLevel);
	double CurrentLevelFind(const CapitalGrowthLeveler& , double currValue);
	double CurrentLevelPositionSize(const CapitalGrowthLeveler& , double accountSize, double riskPercentageChangeRaw);
}