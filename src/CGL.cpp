#include <CGL.h>
#include <cmath>

using namespace CGL;

CapitalGrowthLeveler::CapitalGrowthLeveler(double riskPerc, int nR)
	: mRiskPerc(riskPerc)
	, mnR(nR)
{
	if (riskPerc < 0.00001)
		throw InvalidRiskPercentageException();

	if (nR < 1)
		throw InvalidNRisksArgException();

	mLevelStridePerc = mRiskPerc * mnR;
}


double CGL::PercGrowValue(double value, double perc)
{
    return value + value * perc;
}

double CGL::Perc2Raw(double perc)
{
    return perc / 100;
}

double CGL::PositionSizeGet(double riskAmmount, double overMovePercentage)
{
	return riskAmmount / overMovePercentage;
}

double CGL::NextLevelGet(const CapitalGrowthLeveler& cgl, double currLevel)
{
	return PercGrowValue(currLevel, cgl.mLevelStridePerc);
}

double CGL::CurrentLevelFind(const CapitalGrowthLeveler& cgl, double currValue)
{
	if (currValue < 1)
		return 1;

	double currLevel = 1;
	double nextLevel = NextLevelGet(cgl, currLevel);
	for (int i = 0; i < MAX_SEARCH_LEVEL_ITERATIONS; i++, currLevel = nextLevel, nextLevel = NextLevelGet(cgl, currLevel))
	{
		if (currValue + 0.001 < currLevel)
			continue;

		if (currValue + 0.001 > nextLevel)
			continue;

		return currLevel;
	}

	return 1;
}

double CGL::CurrentLevelPositionSize(const CapitalGrowthLeveler& cgl, double accountSize, double riskPercentageChangeRaw)
{
	return PositionSizeGet(
		CurrentLevelFind(cgl, accountSize) * cgl.mRiskPerc,
		riskPercentageChangeRaw
	);
}